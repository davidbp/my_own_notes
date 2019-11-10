

def clamp(x:float, a: float, b: float):
    """             
    # inside
    In [3]: clamp2(3,2,5)
    Out[3]: 3

    # outside left
    In [5]: clamp2(3,4,5)
    Out[5]: 4

    # outside right
    In [7]: clamp2(8,4,5)
    Out[7]: 5
    """
    if x <= a:
       return a
    if x >= b:
        return b
    return x

def clamp2(input:float, minval: float, maxval: float):
    """
    # inside
    In [3]: clamp(3,2,5)
    Out[3]: 3

    # outside left
    In [5]: clamp(3,4,5)
    Out[5]: 4

    # outside right
    In [7]: clamp(8,4,5)
    Out[7]: 5
    """
    return max(minval, min(maxval, input))




def distance_circle_to_AABB(circle: Circle, rectangle: AABB): -> float

    p_x = clamp(circle.x, rectangle.x, rectangle.x + rectangle.w)
    p_y = clamp(circle.y, rectangle.y, rectangle.y + rectangle.h)

    d_x = p_x - circle.x
    d_y = p_y - circle.y 

    d_norm = np.linalg.norm((d_x,d_y))
    
    if d_norm <= circle.radius:
        return True
    else: 
        return False

