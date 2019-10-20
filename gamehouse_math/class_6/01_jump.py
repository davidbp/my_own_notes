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
import numpy as np

pygame.init()
WINDOW_X = 500
WINDOW_Y = 500

window = pygame.display.set_mode((WINDOW_X,WINDOW_Y))
pygame.display.set_caption("String displayed in the window")
#time.sleep(5)

class player(object):
    def __init__(self,x,y,width,height):
        self.x = x
        self.y = y
        self.width  = width
        self.height = height
        self.position = np.array([x,y])
        self.gravity = np.array([0,-2])
        self.vel = 5
        self.isJump = False
        self.left = False
        self.right = False
        self.walkCount = 0
        self.jumpCount = 10

    def draw(self, window):
        if self.walkCount + 1 >= 27:
            self.walkCount = 0

        if self.left:
            pygame.draw.rect(window, color_red, (x, y, width, height))
            self.walkCount += 1
        elif self.right:
            pygame.draw.rect(window, color_red, (x, y, width, height))
            self.walkCount += 1
        else:
            window.blit(char, (self.x,self.y))

    def move(self, window):

        if keys[pygame.K_LEFT] and x>0:
            self.x -= velocity

        if keys[pygame.K_RIGHT] and x<WINDOW_X-width:
            self.x += velocity

        self.isJump = isJump

def update(dt: float):
    man.position = man.position + man.velocity * dt
    man.velocity = man.velocity + man.gravity * dt
    keep_in_screen()

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

man = player(100, 410, 64,64)

f1_cur_time = time.time()

while run:

    f1_pre_time = f1_cur_time
    f1_cur_time = time.time()
    dt = f1_cur_time - f1_pre_time

    # we don't want the time too big.
    if dt > 0.15:
        dt = 0.15

    #update(dt)
    pygame.time.delay(wait_time)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run=False

    keys = pygame.key.get_pressed()
    man.move(keys) 

    window.fill((0,0,0))
    pygame.draw.rect(window, color_red, (x, y, width, height))
    pygame.display.update()

