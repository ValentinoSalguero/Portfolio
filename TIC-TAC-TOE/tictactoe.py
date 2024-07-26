import pygame
import sys

# Inicialización de Pygame y el módulo de música
pygame.init()  # Inicializa todos los módulos de Pygame
pygame.mixer.init()  # Inicializa el módulo de mezcla de sonido

# Configuración de la pantalla
screen = pygame.display.set_mode((450, 450))  # Configura la pantalla con tamaño 450x450 píxeles
pygame.display.set_caption("Tic Tac Toe")  # Establece el título de la ventana

cell_size = 150  # Tamaño de cada celda en el tablero

offset_x, offset_y = 0, 0  # Desplazamiento para centrar las imágenes

# Coordenadas de las celdas en el tablero
coor = [[(0, 0), (150, 0), (300, 0)],
        [(0, 150), (150, 150), (300, 150)],
        [(0, 300), (150, 300), (300, 300)]]

# Inicialización del tablero vacío
board = [["" for _ in range(3)] for _ in range(3)]  # Crea una matriz 3x3 para el tablero

# Variables de estado
turn = 'X'  # Jugador actual, comienza con 'X'
game_over = False  # Estado del juego
menu_displayed = True  # Estado del menú (si se está mostrando)
mode_selected = False  # Estado del modo de juego
current_music = None  # Música actual reproducida
clock = pygame.time.Clock()  # Reloj para controlar los FPS

def menu():
    # Cargar y transformar la imagen del menú
    background = pygame.image.load('TIC-TAC-TOE/assets/kyoko.png')  # Carga la imagen de fondo del menú
    background = pygame.transform.scale(background, (450, 450))  # Redimensiona la imagen
    background_music = pygame.mixer.Sound('TIC-TAC-TOE/assets/0.mp3')  # Carga la música del menú
    background_music.play(loops=-1)  # Reproduce la música en bucle

    return background, background_music

def default_mode():
    # Cargar y configurar recursos para el modo predeterminado
    background = pygame.image.load('TIC-TAC-TOE/assets/tictactoe_background.png')  # Carga la imagen de fondo del juego
    background = pygame.transform.scale(background, (450, 450))  # Redimensiona la imagen
    circle = pygame.image.load('TIC-TAC-TOE/assets/circle.png')  # Carga la imagen del círculo
    circle = pygame.transform.scale(circle, (125, 125))  # Redimensiona la imagen del círculo
    x = pygame.image.load('TIC-TAC-TOE/assets/x.png')  # Carga la imagen de la 'X'
    x = pygame.transform.scale(x, (125, 125))  # Redimensiona la imagen de la 'X'
    background_music = pygame.mixer.Sound('TIC-TAC-TOE/assets/1.wav')  # Carga la música para el modo predeterminado
    background_music.play(loops=-1)  # Reproduce la música en bucle
    return background, circle, x, background_music

def rcg_mode():
    # Cargar y configurar recursos para el modo rcg
    background = pygame.image.load('TIC-TAC-TOE/assets/rcg_background.png')  # Carga la imagen de fondo del modo rcg
    background = pygame.transform.scale(background, (450, 450))  # Redimensiona la imagen
    circle = pygame.image.load('TIC-TAC-TOE/assets/misako.png')  # Carga la imagen del círculo para el modo rcg
    circle = pygame.transform.scale(circle, (112, 108))  # Redimensiona la imagen del círculo
    x = pygame.image.load('TIC-TAC-TOE/assets/kyoko.png')  # Carga la imagen de la 'X' para el modo rcg
    x = pygame.transform.scale(x, (112, 112))  # Redimensiona la imagen de la 'X'
    background_music = pygame.mixer.Sound('TIC-TAC-TOE/assets/2.mp3')  # Carga la música para el modo rcg
    background_music.play(loops=-1)  # Reproduce la música en bucle
    return background, circle, x, background_music

def stop_current_music():
    global current_music
    if current_music:
        current_music.stop()  # Detiene la música actual si está reproduciéndose

def display_board():
    screen.fill((0, 0, 0))  # Rellena la pantalla con color negro
    # Dibujar el tablero de juego
    screen.blit(background, (0, 0))  # Dibuja el fondo del tablero

    # Dibujar X y O en el tablero
    for row in range(3):
        for col in range(3):
            if board[row][col] == 'X':
                draw_symbol(screen, 'X', row, col)  # Dibuja una 'X' en la celda correspondiente
            elif board[row][col] == 'O':
                draw_symbol(screen, 'O', row, col)  # Dibuja una 'O' en la celda correspondiente

def draw_symbol(screen, turn, row, col):
    _x, y = coor[row][col]  # Obtiene las coordenadas de la celda

    if turn == 'X':
        image = x  # Selecciona la imagen de 'X'
    elif turn == 'O':
        image = circle  # Selecciona la imagen de 'O'
    _x += cell_size // 2 - image.get_width() // 2 + offset_x  # Calcula la posición X para centrar la imagen
    y += cell_size // 2 - image.get_height() // 2 + offset_y  # Calcula la posición Y para centrar la imagen

    screen.blit(image, (_x, y))  # Dibuja la imagen en la pantalla

def victory_for():
    # Verificar si hay un ganador en el tablero
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] and board[i][0] != "":
            return True  # Verifica las filas
        if board[0][i] == board[1][i] == board[2][i] and board[0][i] != "":
            return True  # Verifica las columnas
    if board[0][0] == board[1][1] == board[2][2] and board[0][0] != "":
        return True  # Verifica la diagonal principal
    if board[0][2] == board[1][1] == board[2][0] and board[0][2] != "":
        return True  # Verifica la diagonal secundaria
    return False

def is_board_full():
    # Verificar si el tablero está completamente lleno
    for row in board:
        if "" in row:
            return False  # Si hay alguna celda vacía, el tablero no está lleno
    return True

def load_result_image():
    # Cargar la imagen de resultado
    result_image = pygame.image.load('TIC-TAC-TOE/assets/kyoko.png')  # Carga la imagen de resultado
    result_image = pygame.transform.scale(result_image, (450, 450))  # Redimensiona la imagen
    return result_image

background, background_music = menu()  # Inicializa el menú y la música

while not game_over:
    clock.tick(30)  # Limita el bucle a 30 fotogramas por segundo

    if menu_displayed:
        # Mostrar el menú principal y esperar una tecla
        screen.blit(background, (0, 0))  # Dibuja el fondo del menú
        pygame.display.update()  # Actualiza la pantalla
        waiting_for_key = True
        while waiting_for_key:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game_over = True
                    waiting_for_key = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_1:
                        stop_current_music()  # Detiene la música del menú
                        background, circle, x, current_music = default_mode()  # Carga el modo predeterminado
                        menu_displayed = False
                        mode_selected = True
                        waiting_for_key = False
                    elif event.key == pygame.K_2:
                        stop_current_music()  # Detiene la música del menú
                        background, circle, x, current_music = rcg_mode()  # Carga el modo rcg
                        menu_displayed = False
                        mode_selected = True
                        waiting_for_key = False
                    elif event.key == pygame.K_ESCAPE:
                        pygame.quit()  # Cierra la aplicación si se presiona ESC
                        sys.exit()
    else:
        # Detener la música del menú si el menú no se está mostrando
        if background_music:
            background_music.stop()

    if mode_selected:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            elif event.type == pygame.MOUSEBUTTONDOWN:
                # Manejar los clics del ratón para jugar
                mouseX, mouseY = event.pos
                if (mouseX >= 0 and mouseX < 450) and (mouseY >= 0 and mouseY < 450):
                    row = mouseY // 150
                    col = mouseX // 150
                    if board[row][col] == "":
                        board[row][col] = turn
                        game_is_over = victory_for()
                        if game_is_over:
                            print(f"¡¡El jugador {turn} ha ganado!!")
                            game_over = True
                        elif is_board_full():
                            print("¡¡Es un empate!!")
                            game_over = True
                        turn = 'O' if turn == 'X' else 'X'  # Cambia de turno
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()  # Cierra la aplicación si se presiona ESC
                    sys.exit()

    display_board()  # Actualiza la pantalla con el tablero actual
    pygame.display.update()

pygame.quit()  # Finaliza Pygame al salir del bucle

"""
def enter_move(board):
    # La función acepta el estado actual del tablero y pregunta al usuario acerca de su movimiento,  
    # verifica la entrada y actualiza el tablero acorde a la decisión del usuario.
    while True:
        try:
            cell_number = int(input("Ingresa tu movimiento (1-9): "))
            if cell_number < 1 or cell_number > 9:
                print("Número fuera del rango permitido\nInténtalo de nuevo")
                continue
        except ValueError:
            print("Entrada inválida")
            continue

        free_fields = make_list_of_free_fields(board)
        if not any(cell_number == board[row][col] for row, col in free_fields):
            print("Número de celda no encontrado o ya está ocupado\nInténtalo de nuevo")
            continue

        for row in range(3):
            for col in range(3):
                if board[row][col] == cell_number:
                    if board[row][col] not in ('X', 'O'):
                        board[row][col] = 'O'
                        display_board(board)
                        if victory_for(board, 'O'):
                            print("Has ganado\n¡Felicidades!")
                        elif is_board_full(board):
                            print("El tablero está lleno\nEs un empate.")
                        else:
                            draw_move(board)
                        return  # Salir de la función después de un movimiento válido

def make_list_of_free_fields(board):
    # La función examina el tablero y construye una lista de todos los cuadros vacíos. 
    # La lista está compuesta por tuplas, cada tupla es un par de números que indican la fila y columna.
    free_fields = []
    for row in range(3):
        for col in range(3):
            if board[row][col] not in ('X', 'O'):
                free_fields.append((row, col))
    return free_fields
"""
