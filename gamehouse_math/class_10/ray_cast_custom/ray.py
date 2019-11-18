from particle import Particle
import pygame as pg

drawline = pg.draw.line


class Ray:
    def __init__(self, p: Particle, heading: float = 0):
        self.start = p.pos
        self.heading = heading
        self.end: pg.math.Vector2 = pg.math.Vector2()
        self.image = None

    def update(self, screen: pg.display, p: Particle, boundaries: list):
        self.start = p.pos
        self.end.from_polar((10000, self.heading))

        closest = float("inf")
        new_end = pg.Vector2()

        x3 = self.start.x
        x4 = self.end.x
        y3 = self.start.y
        y4 = self.end.y


        if closest == float("inf"):
            self.end = self.start
            self.image = None
        else:
            self.end = new_end
            self.image = drawline(screen, (100, 100, 100), self.start, self.end, 1)
