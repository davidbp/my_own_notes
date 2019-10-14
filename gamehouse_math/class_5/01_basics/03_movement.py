"""
Notice pygame takes (0,0) to be the top left position of a window

    TL = (0,0)
    TR = (0,500)
    BL = (500,0)
    BR = (500,500)
    TL --------------TR
    |                |
    |                |
    |                |
    |                |
    |                |
    |                |
    |                |
    BL ------------- BR

"""
import pygame
import time

pygame.init()

window = pygame.display.set_mode((500,500))
pygame.display.set_caption("String displayed in the window")
#time.sleep(5)

## character atributes
x = 50
y = 50
width    = 40
height   = 70
velocity = 5
color_red = (255,0,0)

## Main loop of the game
run = True
wait_time = 400 #milliseconds

while run:
    pygame.time.delay(wait_time)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run=False

    ### NEW: Function to generate a tuple containing the keys
    ###      that are pressed in that time instance
    keys = pygame.key.get_pressed()

    if keys[pygame.K_LEFT]:
        x -= velocity

    if keys[pygame.K_RIGHT]:
        x += velocity

    if keys[pygame.K_UP]:
        y -= velocity

    if keys[pygame.K_DOWN]:
        y += velocity
    
    ### NEW: window.fill allows us to paint (fill) the whole screen
    window.fill((0,255,0))
    pygame.draw.rect(window, color_red, (x,y,width, height))
    pygame.display.update()

