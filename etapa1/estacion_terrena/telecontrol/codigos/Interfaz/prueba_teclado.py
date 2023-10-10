import pygame
import sys

pygame.init()

# Configurar la pantalla
screen = pygame.display.set_mode((400, 300))

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            key_name = pygame.key.name(event.key)
            print(f"Tecla presionada: pygame.KEYDOWN - {key_name}")
            if event.key == pygame.K_q:
                pygame.quit()
                sys.exit()
