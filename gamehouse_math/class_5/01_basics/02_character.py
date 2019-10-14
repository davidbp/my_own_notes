import pygame
import time

pygame.init()

window = pygame.display.set_mode((500,500))
pygame.display.set_caption("String displayed in the window")
#time.sleep(5)

## character atributes
x = 50
y = 430
width    = 40
height   = 70
velocity = 5
color_red = (255,0,0)

## Main loop of the game
run = True
wait_time = 100 #milliseconds

while run:
    pygame.time.delay(wait_time)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run=False

    ### NEW: Function to create rectangle objects
    pygame.draw.rect(window, color_red, (x,y,width, height))
    ### NEW: Function to refresh the pixels on the window
    pygame.display.update()

