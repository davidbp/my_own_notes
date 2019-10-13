import pygame
import time

pygame.init()

window = pygame.display.set_mode((500,500))
pygame.display.set_caption("String displayed in the window")
#time.sleep(5)

## Main loop of the game
run = True

wait_time = 100 #milliseconds

while run:
    pygame.time.delay(wait_time)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run=False


