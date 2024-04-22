import pygame
import random

# Inicializa pygame y el sonido
pygame.init()
pygame.mixer.init()

# Carga la imagen de fondo y efectos de sonido
inicio = pygame.image.load("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/imagenes/inicio.png")
fin = pygame.image.load("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/imagenes/GameOver.png")
fondo = pygame.image.load("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/imagenes/fondo.png")
laserSonido = pygame.mixer.Sound("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/laser.wav")
explosionSonido = pygame.mixer.Sound("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/explosion.wav")
golpeSonido = pygame.mixer.Sound("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/golpe.wav")

# Lista de imagenes de explosiones
explosionList = []
for i in range(1, 13):
    explosion = pygame.image.load(f"TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/explosion/{i}.png")
    explosionList.append(explosion)

# Configura la ventana del juego
width = 600
height = 600
window = pygame.display.set_mode((width, height))
pygame.display.set_caption("Python invaders")

#Escalo pantalla de carga
inicio = pygame.transform.scale(inicio,(width, height))
fin = pygame.transform.scale(fin,(width,height))

# Inicializa variables del juego
intro = True
run = False
final = True
fps = 60
clock = pygame.time.Clock()
score = 0
vida = 100
blanco = (255, 255, 255)
negro = (0, 0, 0)

# Funcion para mostrar la puntuación del jugador
def mostrarPuntuacion(frame, texto, tamaño, x, y):
    fuente = pygame.font.SysFont("Small fonts", tamaño, bold = True) # Crea la fuente
    textoFrame = fuente.render(texto, True, blanco, negro) # Renderiza el texto
    rectTexto = textoFrame.get_rect() # Obtiene el rectangulo que rodea el texto
    rectTexto.midtop = (x, y) # Alinea el centro superior del rectangulo de texto
    frame.blit(textoFrame, rectTexto) # Dibuja el texto renderizado

# Funcion para mostrar la barra de vida del jugador
def barraVida(frame, x, y, nivel):
    # Dimensiones de la barra de vida
    longitud = 100
    alto = 20
    fill = int((nivel / 100) * longitud) # Calcula la longitud de la barra de relleno
    # Crea rectangulos para la barra de relleno y el borde
    borde = pygame.Rect(x, y, longitud, alto)
    fill = pygame.Rect(x, y, fill, alto)
    pygame.draw.rect(frame, (204, 169, 221), fill)  # Dibuja el relleno de la barra de vida
    pygame.draw.rect(frame, negro, borde, 4) # Dibuja el borde de la barra de vida

#-------------------------------------------------------------------------------------------

# Definicion de la clase Jugador
class Jugador(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__() # Inicializa la clase base (Sprite) para el jugador
        self.image = pygame.image.load("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/imagenes/Nave.png").convert_alpha() # Carga la imagen de la nave del jugador
        pygame.display.set_icon(self.image) 
        self.rect = self.image.get_rect() # Obtiene el rectangulo asociado a la imagen
        # Configurar la posición inicial del jugador
        self.rect.centerx = width // 2
        self.rect.centery = height - 50
        # Inicializa la velocidad horizontal del jugador y la cantidad de vida
        self.velocidadX = 0
        self.vida = 100

    def update(self):
        # Actualizar la posicion del jugador segun las teclas presionadas
        self.velocidadX = 0
        teclasPresionadas = pygame.key.get_pressed()
        if teclasPresionadas[pygame.K_LEFT]:
            self.velocidadX = -5
        elif teclasPresionadas[pygame.K_RIGHT]:
            self.velocidadX = 5

        self.rect.x += self.velocidadX
        # Asegurarse de que el jugador permanezca dentro de los límites de la ventana
        if self.rect.right > width:
            self.rect.right = width
        elif self.rect.left < 0:
            self.rect.left = 0

    def disparar(self):
        # Crear una bala y agregarla a los grupos de jugador y balas del jugador
        bala = Balas(self.rect.centerx, self.rect.top)
        grupoJugador.add(bala)
        grupoBalasJugador.add(bala)
        laserSonido.play()

#-------------------------------------------------------------------------------------------

# Definicion de la clase Enemigos
class Enemigos(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()  # Inicializa la clase base (Sprite) para el enemigo
        self.image = pygame.image.load("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/imagenes/Rosa.png").convert_alpha() # Carga la imagen del enemigo
        self.rect = self.image.get_rect() # Obtiene el rectangulo asociado a la imagen
        # Configura la posicion inicial del enemigo y lo coloca en una posicion aleatoria 
        self.rect.x = random.randrange(1, width - 50)
        self.rect.y = 10
        self.velocidadY = random.randrange(-5, 20) # Inicializa la velocidad vertical del enemigo con una variación aleatoria

    def update(self):
        # Mueve al enemigo horizontalmente y hacia abajo, y reiniciar si llega al ancho de la ventana
        self.tiempo = random.randrange(-1, pygame.time.get_ticks() // 5000)
        self.rect.x += self.tiempo
        if self.rect.x >= width:
            self.rect.x = 0
            self.rect.y += 50

    def dispararEnemigos(self):
        # Crea una bala para el enemigo y agregarla a los grupos de jugador y balas de enemigos
        bala = BalasEnemigos(self.rect.centerx, self.rect.bottom)
        grupoJugador.add(bala)
        grupoBalasEnemigos.add(bala)
        laserSonido.play()

#-------------------------------------------------------------------------------------------

# Definicion de la clase Balas
class Balas(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__() # Inicializa la clase base (Sprite) para la bala
        self.image = pygame.image.load("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/imagenes/punto y coma.png").convert_alpha() # Carga la imagen de la bala
        self.rect = self.image.get_rect()  # Obtiene el rectangulo asociado a la imagen
        # Configura la posicion inicial
        self.rect.centerx = x
        self.rect.y = y
        # Configura la velocidad de la bala (hacia arriba en el eje y)
        self.velocidad = -10 

    def update(self):
        # Mover la bala hacia arriba y eliminarla si sale de la pantalla
        self.rect.y += self.velocidad
        if self.rect.bottom < 0:
            self.kill()

#-------------------------------------------------------------------------------------------

# Definicion de la clase BalasEnemigos
class BalasEnemigos(pygame.sprite.Sprite):
        def __init__(self, x, y):
            super().__init__() # Inicializa la clase base (Sprite) para la bala del enemigo
            self.image = pygame.image.load("TP_LABO_II/TP PYTHON REEVES_RIOS_SALGUERO_NAVARRO/Python Invaders/imagenes/tab.png").convert_alpha()  # Carga la imagen de la bala del enemigo
            self.image = pygame.transform.rotate(self.image, 90) # Modifica la imagen y la coloca en 90º
            self.rect = self.image.get_rect() # Obtiene el rectangulo asociado a la imagen
            # Configura la posicion inicial de la bala
            self.rect.centerx = x
            self.rect.y = random.randrange(10, width)
            # Configura la velocidad de la bala del enemigo (hacia abajo en el eje y)
            self.velocidadY = 4

        def update(self): 
            # Mover la bala del enemigo hacia abajo y eliminarla si sale de la pantalla
            self.rect.y += self.velocidadY
            if self.rect.bottom > height:
                self.kill()

#-------------------------------------------------------------------------------------------

# Definicion de la clase explosion
class explosion(pygame.sprite.Sprite):
    def __init__(self, posicion):
        super().__init__()  # Inicializa la clase base (Sprite) para la explosion
        self.image = explosionList[0]  # Configurar la imagen inicial
        img_escalada = pygame.transform.scale(self.image, (20, 20)) # Escala la imagen de la explosión
        self.rect = img_escalada.get_rect() # Obtiene el rectangulo asociado a la imagen
        self.rect.center = posicion  # Establece la posición inicial
        self.tiempo = pygame.time.get_ticks() # Registra el tiempo en que se inicio la explosion
        # Configura la velocidad de la animacion de explosion y el indice de fotogramas
        self.velocidadExplo = 30
        self.frames = 0

    def update(self):
        # Actualizar los fotogramas de la animacion de explosion
        tiempoAct = pygame.time.get_ticks()
        if tiempoAct - self.tiempo > self.velocidadExplo:
            self.frames += 1
            if self.frames == len(explosionList):
                # Elimina la explosión cuando se alcanza el ultimo fotograma
                self.kill()
            else: 
                # Actualiza la imagen de la explosion y su rectangulo
                posicion = self.rect.center
                self.image = explosionList[self.frames]
                self.rect = self.image.get_rect()
                self.rect.center = posicion

#-------------------------------------------------------------------------------------------

# Crear grupos de sprites para el jugador, enemigos y balas
grupoJugador = pygame.sprite.Group()
grupoEnemigos = pygame.sprite.Group()
grupoBalasJugador = pygame.sprite.Group()
grupoBalasEnemigos = pygame.sprite.Group()

# Crear una instancia del jugador y agregarla a los grupos de jugador y balas del jugador
player = Jugador()
grupoJugador.add(player)
grupoBalasJugador.add(player)

# Crear 10 instancias de enemigos y agregarlas a los grupos de enemigos y jugador
for x in range(5):
    enemigo = Enemigos(5, 5)
    grupoEnemigos.add(enemigo)
    grupoJugador.add(enemigo)

#Bucle principal
runPrinc = True
while runPrinc:
    #Bucle para la pantalla de inicio
    while intro:
        clock.tick(fps)
        window.blit(inicio, (0, 0))
        
        # Manejo de eventos
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit()

        tecla = pygame.key.get_pressed()
        #Verifica la tecla, si es espacio continúa al juego
        if tecla[pygame.K_SPACE]:
            intro = False
            run = True
            
        pygame.display.flip()

    # Bucle principal del juego
    while run:
        clock.tick(fps)
        window.blit(fondo, (0, 0))

        # Manejo de eventos
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    player.disparar()

        # Actualizar y dibujar sprites
        grupoJugador.update()
        grupoEnemigos.update()
        grupoBalasEnemigos.update()
        grupoBalasJugador.update()
        grupoJugador.draw(window)

        # Comprobar colisiones entre balas del jugador y enemigos
        colision1 = pygame.sprite.groupcollide(grupoEnemigos, grupoBalasJugador, True, True)
        for i in colision1:
            score += 10
            enemigo.dispararEnemigos()
            enemigo = Enemigos(300, 10)
            grupoEnemigos.add(enemigo)
            grupoJugador.add(enemigo)

            explo = explosion(i.rect.center)
            grupoJugador.add(explo)
            explosionSonido.set_volume(0.3)
            explosionSonido.play()

        # Comprobar colisiones entre balas del enemigo y el jugador
        colision2 = pygame.sprite.spritecollide(player, grupoBalasEnemigos, True)
        for j in colision2:
            player.vida -= 10
            if player.vida <= 0:
                run = False
                final = True
            explo1 = explosion(j.rect.center)
            grupoJugador.add(explo1)
            golpeSonido.play()

        # Comprobar colisiones entre el jugador y los enemigos
        hits = pygame.sprite.spritecollide(player, grupoEnemigos, False)
        for hit in hits:
            player.vida -= 100
            enemigos = enemigos(10, 10)
            grupoJugador.add(enemigos)
            grupoEnemigos.add(enemigos)
            if player.vida <= 0:
                run = False
                final = True

        # Mostrar la puntuación y la salud del jugador
        mostrarPuntuacion(window, ("   PUNTUACIÓN:   " + str(score) + "    "), 30, width - 95, 575)
        barraVida(window, width - 100, 0, player.vida)

        pygame.display.flip()

    while final:

        clock.tick(fps)
        window.blit(fin, (0, 0))
        
        # Manejo de eventos
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                final = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    #Reiniciar el juego
                    final = False
                    run = True
                    # Restablecer variables del juego
                    score = 0
                    player.vida = 100
                elif event.key == pygame.K_ESCAPE:
                    #Salir del juego
                    runPrinc = False
                    final = False


        pygame.display.flip()

# Salir de pygame cuando se sale del bucle del juego
pygame.quit()