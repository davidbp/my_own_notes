import pygame
import random
import math
import numpy as np

background_color = (255,255,255)
(width, height) = (800, 1000)
drag = 0.999
elasticity = 0.75
gravity = (math.pi, 0.002)


def addVectors(angle1, length1, angle2, length2):
    x  = math.sin(angle1) * length1 + math.sin(angle2) * length2
    y  = math.cos(angle1) * length1 + math.cos(angle2) * length2
    
    angle = 0.5 * math.pi - math.atan2(y, x)
    length  = math.hypot(x, y)

    return (angle, length)


def find_polygon(polygons, x, y):
    for p in polygons:
        if math.hypot(p.x-x, p.y-y) <= p.size:
            return p
    return None


def inside_convex_polygon(point, vertices):
    previous_side = None
    n_vertices = len(vertices)
    for n in range(n_vertices):
        a, b = vertices[n], vertices[(n+1)%n_vertices]
        affine_segment = vector_substraction(b, a)
        affine_point   = vector_substraction(point, a)
        current_side   = get_side_from_scalar_product_sign(affine_segment, affine_point)
        if current_side is None:
            return False #outside or over an edge
        elif previous_side is None: #first segment
            previous_side = current_side
        elif previous_side != current_side:
            return False
    return True

def get_side_from_scalar_product_sign(a, b):
    x = x_product(a, b)
    if x < 0:
        return -1
    elif x > 0: 
        return 1
    else:
        return None

def vector_substraction(a, b):
    return (a[0]-b[0], a[1]-b[1])

def x_product(a, b):
    return a[0]*b[1]-a[1]*b[0]


class Polygon():
    def __init__(self, x, y, vertices):
        self.x = x
        self.y = y
        self.vertices = vertices
        self.color = (0, 0, 255)
        self.thickness = 2
        self.speed = 0
        self.angle = 0
        self.center_of_mass = self.compute_center_of_mass()

    def display(self):
        #pygame.draw.circle(screen, self.color, (int(self.x), int(self.y)), self.size, self.thickness)
        pygame.draw.polygon(screen, self.color, self.vertices,  self.thickness)
        pygame.draw.circle(screen, self.color, (self.center_of_mass[0], self.center_of_mass[1]) , 2)
        # pygame.draw.circle(screen, self.color, (int(self.x), int(self.y)), self.size, self.thickness)

        
    def compute_center_of_mass(self):
        """
        Return center of mass
        """
        return np.mean(self.vertices,axis=0, dtype=int)

    def update_center_of_mass(self):
        """
        update center of mass
        """
        self.center_of_mass = self.compute_center_of_mass()

    def move(self, translation_vec):
        """
        update vertices
        """
        self.vertices += translation_vec


def find_polygon(poligons, mouseX, mouseY):
    point = (mouseX, mouseY)
    for k, poligon in enumerate(poligons):

        is_inside = inside_convex_polygon(point, poligon.vertices)
        if is_inside:
            #import pdb;pdb.set_trace()
            print(f"inside k={k}, center of mass {poligon.center_of_mass}")
            #import pdb;pdb.set_trace()
            return True, poligon
    
    return False, None


def edges_of(poligon_vertices):
    """
    Return the vector edges of the input poligon p.
    """
    edges = []
    N = len(poligon_vertices)

    for i in range(N):
        #print(i)
        edge = poligon_vertices[(i + 1)%N] - poligon_vertices[i]
        edges.append(edge)

    return edges


def orthogonal(v):
    """
    Return a 90 degree clockwise rotation of v.
    """
    return np.array([-v[1], v[0]])


def is_separating_axis(o, poly_a, poly_b, epsilon=1e-6):
    """
    Return True (and the push vector) if o is a separating axis of poly_a and poly_b.
    Otherwise, return False and None.
    
    How do we know if an axis defined by "o" is a separating hyperplane?
    We check if the projections of poly_a and poly_b overlap.
    
    If they do overlap then "o" is not a separating axis.
    If they do not overlap then "o" is a separating axis.
    """
    min_a, max_a = float('+inf'), float('-inf')
    min_b, max_b = float('+inf'), float('-inf')
    o = o/np.linalg.norm(o)
    
    ### Complete


def centers_displacement(p1, p2):
    """
    Return the displacement between the geometric center of p1 and p2.
    """
    # geometric center
    c1 = p1.center_of_mass
    c2 = p2.center_of_mass
    return c2 - c1

def collide(p1, p2):
    '''
    Return True and the MPV if the shapes collide. Otherwise, return False and
    None.

    p1 and p2 are lists of ordered pairs, the vertices of the polygons in the
    counterclockwise direction.
    '''

    p1_vertices = [np.array(v, 'float64') for v in p1.vertices]
    p2_vertices = [np.array(v, 'float64') for v in p2.vertices]

    edges = edges_of(p1_vertices)
    edges += edges_of(p2_vertices)
    orthogonals = [orthogonal(e) for e in edges]

    push_vectors = []

    ### COMPLETE
    
    mpv=None
    return True, mpv

screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Tutorial 8')

p1 = Polygon(x=10,y=10, vertices= np.array([[400,100],[300,300],[400,500]]) )
p2 = Polygon(x=10,y=10, vertices= 110+np.array([[400,100],[300,300],[400,500]]) )
#p2 = Polygon(x=10,y=10, vertices=np.array([[600,200],[100,500],[200,300]]) )
polygons = [p1,p2]

bool_selected_polygon = False
running = True
fps = 60
clock = pygame.time.Clock()
selected_polygon = None
mouseXprev = 0
mouseYprev = 0

while running:
    print('tick={}, fps={}'.format(clock.tick(), clock.get_fps()), end='\r', flush=True)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            (mouseX, mouseY) = pygame.mouse.get_pos()
            bool_selected_polygon, selected_polygon = find_polygon(polygons, mouseX, mouseY)
             
            if bool_selected_polygon ==True:
                selected_polygon.color = (255,0,0)

        elif event.type == pygame.MOUSEBUTTONUP:
            selected_polygon = None

    if selected_polygon !=None:
        (mouseX, mouseY) = pygame.mouse.get_pos()
        dx = None
        dy = None 
        #### COMPLETE

    screen.fill(background_color)
    p1.display()
    p2.display()


    #### UPDATE GAME STATE
    bool_colission, mpv = collide(p1, p2)

    if selected_polygon is None:

        for polygon in polygons: 
            polygon.color = (0,0,255)    

    if bool_colission is True:
        for polygon in polygons: 
            polygon.color = (0,255,0)


    pygame.display.flip()



