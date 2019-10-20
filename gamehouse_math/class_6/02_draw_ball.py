# Code adapted from 
# http://www.petercollingridge.co.uk/tutorials/pygame-physics-simulation/

import pygame

## Window information
background_colour = (255,255,255)
(width, height) = (900, 500)
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Tutorial 1')
screen.fill(background_colour)
pygame.display.flip()

class Particle:
    def __init__(self, x, y, radius, thickness=1):
        self.x = x
        self.y = y
        self.radius = radius
        self.colour = (0, 155, 255)
        self.thickness = thickness

    def display(self):
        pygame.draw.circle(screen, self.colour, (self.x, self.y), self.radius, self.thickness)


## Define what will be in the game
my_first_particle = Particle(x=150, y=50, radius=10)

running = True
while running:

    for event in pygame.event.get():
        my_first_particle.display()

        if event.type == pygame.QUIT:
            running = False

    pygame.display.update()
