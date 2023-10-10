# -*- coding: utf-8 -*-
"""
Created on Wed Jun 21 21:49:49 2023

@author: angel
"""

print("Hola mundo")

import pygame
import socket
import sys
import json

host = "192.168.4.1"  # Dirección IP del punto de acceso del ESP32
port = 1234  # Puerto en el que está escuchando el servidor UDP del ESP32

"""
try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except:
    print("Hubo un error en el sistema")
    sys.exit()
"""

# Inicializar Pygame
pygame.init()

# Definir dimensiones de la ventana
width = 900
height = 475
size = (width, height)

# Colores
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)

# Crear la ventana del juego
screen = pygame.display.set_mode(size)
pygame.display.set_caption("ARGO | Interfaz de control")


# Dimensiones de los cuadrados de las teclas
key_width = 120
key_height = 120

# Posiciones de las teclas
key_positions = {
    pygame.K_a: (50, 180),
    pygame.K_s: (180, 310),
    pygame.K_d: (310, 180),
    pygame.K_w: (180, 50),
    #pygame.K_SPACE: (130, 400)
}

# Estado de las teclas
key_states = {
    pygame.K_a: False,
    pygame.K_s: False,
    pygame.K_d: False,
    pygame.K_w: False,
    #pygame.K_SPACE: False
}

# Variables para el bucle principal del juego
clock = pygame.time.Clock()
game_over = False

# Función para dibujar las teclas en la pantalla
def draw_keys():
    for key, position in key_positions.items():
        #print("Comienza")
        colchon = 20
        vertices = [(position[0], position[1]),(position[0]+30, position[1]),(position[0]+15, position[1]+15)]
        ### Por si se me olvida, el poligono va -> (incicio, punta, otro lado del inicio) (excepto la tecla A)
        if key == pygame.K_a:
            vertices = [(position[0], position[1]+key_height/2),(position[0]+key_width - colchon, position[1]+key_height),(position[0]+key_width - colchon, position[1])]
        if key == pygame.K_s:
            vertices = [(position[0], position[1] + colchon),(position[0]+key_height/2, position[1]+key_height),(position[0]+key_width, position[1] + colchon)]
        if key == pygame.K_d:
            vertices = [(position[0] + colchon, position[1]),(position[0]+key_width, position[1] + key_height/2),(position[0] + colchon, position[1]+key_height)]
        if key == pygame.K_w:
            vertices = [(position[0], position[1]+key_height - colchon),(position[0]+key_width/2, position[1]),(position[0]+key_width, position[1]+key_height - colchon)]
        color = RED if key_states[key] else WHITE
        pygame.draw.polygon(screen, color, vertices)
        #print("Termina")
        

def send_command():
    states = dict(filter(lambda item: item[1], key_states.items()))
    teclas = list(states.keys())
    mensaje="n"
    if teclas == [pygame.K_a]:
        mensaje = "a"
    if teclas == [pygame.K_s]:
        mensaje = "s"
    if teclas == [pygame.K_d]:
        mensaje = "d"
    if teclas == [pygame.K_w]:
        mensaje = "w"
    if teclas == [pygame.K_SPACE]:
        mensaje = "S"
    
    mensaje_json = {
        "destino":"llantas",
        "comando":mensaje
    }
    mensaje_json = json.dumps(mensaje_json)
    print(mensaje_json)
    #sock.sendto(mensaje.encode(), (host, port))
    

# Bucle principal del juego
while not game_over:
    try:
        # Manejo de eventos
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            if event.type == pygame.KEYDOWN:
                if event.key in key_positions:
                    key_states[event.key] = True
            if event.type == pygame.KEYUP:
                if event.key in key_positions:
                    key_states[event.key] = False
        
        # Lógica del juego
        
        # Actualizar la pantalla
        screen.fill((0, 0, 0))  # Rellenar la pantalla con color negro
        
        draw_keys()  # Dibujar las teclas
        send_command()

        ### PARTE DE BRAZO ###
        # Dibujar el triángulo en rojo
        rect_brazo_control = pygame.Rect(480, 40, 395, 395)
        pygame.draw.rect(screen, (60,20,60), rect_brazo_control)

        font = pygame.font.Font(None, 60)
        text = font.render("Control de Brazo", True, (255, 255, 255))

        font2 = pygame.font.Font(None, 60)
        text2 = font2.render("(Pendiente)", True, (255, 255, 255))

        # create a rectangular object for the
        # text surface object
        textRect = text.get_rect()
        textRect2 = text2.get_rect()
        
        # set the center of the rectangular object.
        textRect.center = (675, 220)
        textRect2.center = (675, 260)

        screen.blit(text, textRect)
        screen.blit(text2, textRect2)

        # Dibujar objetos
        pygame.display.flip()  # Actualizar toda la pantalla
        
        # Controlar la velocidad de fotogramas
        clock.tick(10)  # 60 FPS

    except:
        game_over = True

# Salir del juego
pygame.quit()
#sock.close()