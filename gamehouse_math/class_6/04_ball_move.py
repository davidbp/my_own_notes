"""
The simplest way to represent movement is to create two attributes: dx and dy.
Then during each pass through the loop, add dx to x and dy to y. So, for example,
if a particle has dx=2 and dy=1, it will follow a shallow diagonal, 
from left to right and top to bottom. 
This is the method I used for a long time - it is simple and fine for many situations.

(EDIT: I have since returned to this method - it is a lot simpler and more efficient.
 But it's good learn both ways.)

My preferred method now is to create attributes to represent speed and direction 
(i.e. velocity). This requires a bit more work to start with but makes life a lot 
easier later one. This method is also good for creating objects that have a constant 
speed, but varying direction. I actually first started using this method when trying 
to create an ant simulation. The ants have a creepily realistic movement when given 
a constant speed and randomly changing their a direction every few seconds.

So let's give our particle object a speed and a direction.

self.speed = 0.01
self.angle = 0
"""
import pygame
import random
import math

background_colour = (255,255,255)
(width, height) = (800, 800)

class Particle():
    def __init__(self, x, y, size):
        self.x = x
        self.y = y
        self.size = size
        self.colour = (0, 0, 255)
        self.thickness = 1

        # here we give the velocity vector as magnitude + angle
        self.speed = 0
        self.angle = 0

    def display(self):
        pygame.draw.circle(screen, self.colour, (int(self.x), int(self.y)), self.size, self.thickness)

    def move(self):
        # Polar form
        #self.x = self.x + math.sin(self.angle) * self.speed
        #self.y = self.y - math.cos(self.angle) * self.speed
        self.x = self.x + self.speed
        self.y = self.y - self.speed # the - is because of the downward pointing y-axis. 


screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Tutorial 4')

number_of_particles = 10
my_particles = []

for n in range(number_of_particles):
    size = random.randint(10, 20)
    x = random.randint(size, width-size)
    y = random.randint(size, height-size)
    particle       = Particle(x, y, size)
    particle.speed = random.random()
    particle.angle = random.uniform(0, math.pi*2)
    my_particles.append(particle)
    #print(particle.speed, particle.angle)

running = True
while running:
    screen.fill(background_colour)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False


    for particle in my_particles:
        particle.move()
        particle.display()
    pygame.display.flip()
