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
WINDOW_X = 500
WINDOW_Y = 500

window = pygame.display.set_mode((WINDOW_X,WINDOW_Y))
pygame.display.set_caption("String displayed in the window")
#time.sleep(5)

## character atributes
x = 50
y = 400
width    = 40
height   = 70
velocity = 5
color_red = (255,0,0)
isJump = False
jumpCount = 10

## Main loop of the game
run = True
wait_time = 10 #milliseconds

while run:
    pygame.time.delay(wait_time)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run=False

    keys = pygame.key.get_pressed()

    if keys[pygame.K_LEFT] and x>0:
        x -= velocity

    if keys[pygame.K_RIGHT] and x<WINDOW_X-width:
        x += velocity

    if not (isJump):
        if keys[pygame.K_UP] and y>0:
            y -= velocity

        if keys[pygame.K_DOWN] and y<WINDOW_Y-height:
            y += velocity

        if keys[pygame.K_SPACE]:
            isJump = True
    else:
        if jumpCount >= -10:
            neg=1
            if jumpCount <0:
                neg = -1
            y -= (jumpCount ** 2) *0.5 *neg
            jumpCount -=1
        else:
            isJump = False
            jumpCount = 10
    
    window.fill((0,0,0))
    pygame.draw.rect(window, color_red, (x,y,width, height))
    pygame.display.update()
