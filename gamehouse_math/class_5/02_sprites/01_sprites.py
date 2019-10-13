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
WINDOW_Y = 480
FRAME_RATE = 81

window = pygame.display.set_mode((WINDOW_X,WINDOW_Y))
pygame.display.set_caption("String displayed in the window")
#time.sleep(5)

## Add images
walkRight = [pygame.image.load('images/R1.png'), 
             pygame.image.load('images/R2.png'), 
             pygame.image.load('images/R3.png'), 
             pygame.image.load('images/R4.png'), 
             pygame.image.load('images/R5.png'), 
             pygame.image.load('images/R6.png'), 
             pygame.image.load('images/R7.png'), 
             pygame.image.load('images/R8.png'),
             pygame.image.load('images/R9.png')]

walkLeft = [pygame.image.load('images/L1.png'), 
            pygame.image.load('images/L2.png'), 
            pygame.image.load('images/L3.png'), 
            pygame.image.load('images/L4.png'), 
            pygame.image.load('images/L5.png'), 
            pygame.image.load('images/L6.png'), 
            pygame.image.load('images/L7.png'),
            pygame.image.load('images/L8.png'),
            pygame.image.load('images/L9.png')]
            
bg = pygame.image.load('images/bg.jpg')
char = pygame.image.load('images/standing.png')

## character atributes
x = 50
y = 400
width    = 64
height   = 64
velocity = 5
color_red = (255,0,0)
isJump = False
jumpCount = 10
left = False
right = False
walkCount = 0

## make plot
def redrawGameWindow():
    global walkCount
    #window.fill((0,0,0))
    window.blit(bg, (0,0))
    if walkCount +1 > FRAME_RATE:
        walkCount = 0

    if left:
        window.blit(walkLeft[walkCount//9], (x,y))
        walkCount +=1
    elif right:
        window.blit(walkRight[walkCount//9], (x,y))
        walkCount +=1
    else:
        window.blit(char, (x,y))

    #pygame.draw.rect(window, color_red, (x,y,width, height))
    pygame.display.update()



## Main loop of the game
clock = pygame.time.Clock()
run = True

while run:
    #pygame.time.delay(frame_rate)
    clock.tick(FRAME_RATE)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run=False

    keys = pygame.key.get_pressed()

    if keys[pygame.K_LEFT] and x>0:
        x -= velocity
        right = False
        left = True
        
    elif keys[pygame.K_RIGHT] and x<WINDOW_X-width:
        x += velocity
        right = True
        left = False
    else:
        right = False
        left  = False
        walkCount = 0

    
    if not (isJump):
        if keys[pygame.K_SPACE]:
            isJump = True
            right = False
            left = False
            walkCount = 0
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

    redrawGameWindow()


pygame.quit()