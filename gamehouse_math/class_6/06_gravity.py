import pygame
import random
import math

background_colour = (255,255,255)
(width, height)   = (400, 400)
drag              = 0.999
elasticity        = 0.75                    #### elasticity in (0,1)
gravity           = (math.pi, 0.009)

def addVectors(vec1, vec2):
    (angle1, length1) = vec1
    (angle2, length2) = vec2
    x  = math.sin(angle1) * length1 + math.sin(angle2) * length2
    y  = math.cos(angle1) * length1 + math.cos(angle2) * length2
    
    angle = 0.5 * math.pi - math.atan2(y, x)
    length  = math.hypot(x, y)      #### sqrt(x*x + y*y)
    #length  =  math.sqrt(x*x + y*y) #### sqrt(x*x + y*y)
    return (angle, length)

class Particle():
    def __init__(self, x, y, size):
        self.x = x
        self.y = y
        self.size = size
        self.colour = (0, 0, 255)
        self.thickness = 1
        self.speed = 0
        self.angle = 0

    def display(self):
        pygame.draw.circle(screen, self.colour, (int(self.x), int(self.y)), self.size, self.thickness)

    def move(self):
        (self.angle, self.speed) = addVectors((self.angle, self.speed), gravity)
        self.x     += math.sin(self.angle) * self.speed
        self.y     -= math.cos(self.angle) * self.speed
        self.speed *= drag
        particle.bounce()

    def bounce(self):
        if self.x > width - self.size:
            self.x     = 2*(width - self.size) - self.x
            self.angle = - self.angle
            self.speed *= elasticity    

        elif self.x < self.size:
            self.x = 2*self.size - self.x
            self.angle = - self.angle
            self.speed *= elasticity

        if self.y > height - self.size:
            self.y = 2*(height - self.size) - self.y
            self.angle = math.pi - self.angle
            self.speed *= elasticity

        elif self.y < self.size:
            self.y = 2*self.size - self.y
            self.angle = math.pi - self.angle
            self.speed *= elasticity

screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Tutorial 6')

number_of_particles = 1
my_particles = []

for n in range(number_of_particles):
    size = random.randint(10, 20)
    x = random.randint(size, width-size)
    y = random.randint(size, height-size)

    particle = Particle(x, y, size)
    particle.speed = random.random()*10
    particle.angle = random.uniform(0, math.pi*2)

    my_particles.append(particle)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill(background_colour)

    for particle in my_particles:
        particle.move()
        particle.display()

    pygame.display.flip()
