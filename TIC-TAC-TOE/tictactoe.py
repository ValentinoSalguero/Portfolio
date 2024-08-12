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
circle = None  # Imagen de 'O'
x = None  # Imagen de 'X'
background = None  # Imagen de fondo del juego
clock = pygame.time.Clock()  # Reloj para controlar los FPS
game_mode = 0


def menu():
    global background, current_music
    # Cargar y transformar la imagen del menú
    background = pygame.image.load('TIC-TAC-TOE/assets/menu.png')  # Carga la imagen de fondo del menú
    background = pygame.transform.scale(background, (450, 450))  # Redimensiona la imagen
    background_music = pygame.mixer.Sound('TIC-TAC-TOE/assets/0.mp3')  # Carga la música del menú
    background_music.play(loops=-1)  # Reproduce la música en bucle
    current_music = background_music  # Guarda la música actual
    return background, background_music

def default_mode():
    global circle, x, background, current_music
    # Cargar y configurar recursos para el modo predeterminado
    background = pygame.image.load('TIC-TAC-TOE/assets/tictactoe_background.png')  # Carga la imagen de fondo del juego
    background = pygame.transform.scale(background, (450, 450))  # Redimensiona la imagen
    circle = pygame.image.load('TIC-TAC-TOE/assets/circle.png')  # Carga la imagen del círculo
    circle = pygame.transform.scale(circle, (125, 125))  # Redimensiona la imagen del círculo
    x = pygame.image.load('TIC-TAC-TOE/assets/x.png')  # Carga la imagen de la 'X'
    x = pygame.transform.scale(x, (125, 125))  # Redimensiona la imagen de la 'X'
    background_music = pygame.mixer.Sound('TIC-TAC-TOE/assets/1.wav')  # Carga la música para el modo predeterminado
    background_music.play(loops=-1)  # Reproduce la música en bucle
    current_music = background_music  # Guarda la música actual
    return background, circle, x, background_music

def rcg_mode():
    global circle, x, background, current_music
    # Cargar y configurar recursos para el modo rcg
    background = pygame.image.load('TIC-TAC-TOE/assets/rcg_background.png')  # Carga la imagen de fondo del modo rcg
    background = pygame.transform.scale(background, (450, 450))  # Redimensiona la imagen
    circle = pygame.image.load('TIC-TAC-TOE/assets/misako.png')  # Carga la imagen del círculo para el modo rcg
    circle = pygame.transform.scale(circle, (112, 108))  # Redimensiona la imagen del círculo
    x = pygame.image.load('TIC-TAC-TOE/assets/kyoko.png')  # Carga la imagen de la 'X' para el modo rcg
    x = pygame.transform.scale(x, (112, 112))  # Redimensiona la imagen de la 'X'
    background_music = pygame.mixer.Sound('TIC-TAC-TOE/assets/2.mp3')  # Carga la música para el modo rcg
    background_music.play(loops=-1)  # Reproduce la música en bucle
    current_music = background_music  # Guarda la música actual
    return background, circle, x, background_music

def stop_current_music():
    global current_music
    # Detiene la música actual si está reproduciéndose
    if current_music:
        current_music.stop()

def display_board():
    # Rellena la pantalla con color negro y dibuja el fondo del tablero
    screen.fill((0, 0, 0))  
    screen.blit(background, (0, 0))  # Dibuja el fondo del tablero

    # Dibuja X y O en el tablero según el estado del mismo
    for row in range(3):
        for col in range(3):
            if board[row][col] == 'X':
                draw_symbol(screen, 'X', row, col)  # Dibuja una 'X' en la celda correspondiente
            elif board[row][col] == 'O':
                draw_symbol(screen, 'O', row, col)  # Dibuja una 'O' en la celda correspondiente

def draw_symbol(screen, turn, row, col):
    # Dibuja el símbolo (X o O) en la celda correspondiente
    _x, y = coor[row][col]  # Obtiene las coordenadas de la celda
    if turn == 'X':
        image = x  # Selecciona la imagen de 'X'
    elif turn == 'O':
        image = circle  # Selecciona la imagen de 'O'
    _x += cell_size // 2 - image.get_width() // 2 + offset_x  # Calcula la posición X para centrar la imagen
    y += cell_size // 2 - image.get_height() // 2 + offset_y  # Calcula la posición Y para centrar la imagen
    screen.blit(image, (_x, y))  # Dibuja la imagen en la pantalla

def victory_for():
    # Verifica si hay un ganador en el tablero
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
    # Verifica si el tablero está completamente lleno
    for row in board:
        if "" in row:
            return False  # Si hay alguna celda vacía, el tablero no está lleno
    return True

def show_result_image():
    if game_mode == 1:
        # Muestra la imagen del resultado del juego
        result_image = pygame.image.load('TIC-TAC-TOE/assets/default_mode_result_background.png').convert_alpha()  # Carga la imagen del resultado
    else:
        result_image = pygame.image.load('TIC-TAC-TOE/assets/rcg_mode_result_background.png').convert_alpha()  # Carga la imagen del resultado
    result_image = pygame.transform.scale(result_image, (450, 450))  # Redimensiona la imagen
    return result_image

def handle_result_screen(result_text, turns):
    display_board()  # Dibuja el estado final del tablero

    bg = show_result_image()
    screen.blit(bg, (0, 0))

    pygame.display.update()  # Actualiza la pantalla

    # Configurar la fuente y el color del texto
    font = pygame.font.Font(None, 74)
    text_surface = font.render(result_text, True, (255, 255, 255))

    # Determinar la imagen a mostrar
    if turns:  # Si hay un turno ganador, selecciona la imagen
        image = x if turns == 'X' else circle
        # Redimensionar la imagen
        scaled_width = image.get_width() * 0.5  # Por ejemplo, escala al 80% del tamaño original
        scaled_height = image.get_height() * 0.5
        image = pygame.transform.scale(image, (int(scaled_width), int(scaled_height)))
    else:  # Si es empate, no mostramos imagen
        image = None

    # Crear superficie combinada de texto e imagen
    if image:
        combined_width = text_surface.get_width() + image.get_width() + 10
        combined_height = max(text_surface.get_height(), image.get_height())
        combined_surface = pygame.Surface((combined_width, combined_height), pygame.SRCALPHA)
        combined_surface.blit(text_surface, (0, (combined_height - text_surface.get_height()) // 2))
        combined_surface.blit(image, (text_surface.get_width() + 10, (combined_height - image.get_height()) // 2))
    else:
        combined_surface = text_surface

    # Centramos la superficie combinada en la parte superior de la pantalla
    text_rect = combined_surface.get_rect(midtop=(screen.get_width() / 2, 20))
    screen.blit(combined_surface, text_rect)

    pygame.display.update()  # Actualiza la pantalla

    # Manejo de eventos
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    reset_game()
                    return
                elif event.key == pygame.K_m:
                    return_to_menu()
                    return
                elif event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    sys.exit()

def reset_game():
    global board, turn, game_over
    # Reinicia el estado del juego
    board = [["" for _ in range(3)] for _ in range(3)]  # Reinicia el tablero
    game_over = False  # Marca el juego como no terminado
    turn = 'X'
    display_board()  # Muestra el tablero reiniciado

def return_to_menu():
    global menu_displayed, mode_selected, current_music, background, board, turn, game_over
    # Vuelve al menú principal
    stop_current_music()  # Detiene la música actual
    background, background_music = menu()  # Muestra el menú
    menu_displayed = True  # Marca que el menú se está mostrando
    mode_selected = False  # Marca que no se ha seleccionado un modo
    current_music = background_music  # Guarda la música del menú
    board = [["" for _ in range(3)] for _ in range(3)]  # Reinicia el tablero
    game_over = False  # Marca el juego como no terminado
    turn = 'X'

background, background_music = menu()  # Inicializa la pantalla del menú

while not game_over:
    clock.tick(30)  # Controla la velocidad de actualización de la pantalla (30 FPS)
    
    if menu_displayed:
        screen.blit(background, (0, 0))  # Dibuja el fondo del menú
        pygame.display.update()  # Actualiza la pantalla
        waiting_for_key = True
        while waiting_for_key:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game_over = True  # Termina el juego si se recibe el evento de cierre
                    waiting_for_key = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_1:
                        stop_current_music()  # Detiene la música actual
                        background, circle, x, current_music = default_mode()  # Configura el modo predeterminado
                        menu_displayed = False  # Oculta el menú
                        mode_selected = True  # Marca que se ha seleccionado un modo
                        game_mode = 1
                        waiting_for_key = False
                    elif event.key == pygame.K_2:
                        stop_current_music()  # Detiene la música actual
                        background, circle, x, current_music = rcg_mode()  # Configura el modo rcg
                        menu_displayed = False  # Oculta el menú
                        mode_selected = True  # Marca que se ha seleccionado un modo
                        waiting_for_key = False
                    elif event.key == pygame.K_ESCAPE:
                        pygame.quit()
                        sys.exit()  # Termina el juego si se presiona la tecla 'ESC'

    else:
        if background_music:
            background_music.stop()  # Detiene la música si se está reproduciendo

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True  # Termina el juego si se recibe el evento de cierre
            elif event.type == pygame.MOUSEBUTTONDOWN:
                mouseX, mouseY = event.pos  # Obtiene la posición del ratón
                if (mouseX >= 0 and mouseX < 450) and (mouseY >= 0 and mouseY < 450):
                    row = mouseY // 150  # Calcula la fila
                    col = mouseX // 150  # Calcula la columna
                    if board[row][col] == "":
                        board[row][col] = turn  # Marca la celda con el símbolo del turno actual
                        display_board()  # Muestra el tablero actualizado
                        pygame.display.update()  # Actualiza la pantalla
                        game_is_over = victory_for()  # Verifica si el juego ha terminado
                        if game_is_over:
                            handle_result_screen(f'¡GANÓ!', turn)  # Muestra la pantalla de resultado de victoria
                        elif is_board_full():
                            handle_result_screen('¡EMPATE!', None)  # Muestra la pantalla de resultado de empate
                        else:
                            turn = 'O' if turn == 'X' else 'X'  # Cambia el turno
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    sys.exit()  # Termina el juego si se presiona la tecla 'ESC'

    if not menu_displayed:
        display_board()  # Muestra el tablero si no se está mostrando el menú
        pygame.display.update()  # Actualiza la pantalla

pygame.quit()  # Cierra Pygame al finalizar el juego