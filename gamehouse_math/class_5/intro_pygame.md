

# Main game Loop

```
while run_game==True
	1) Draw screen
	2) Update game state
	3) Handle events
```


#### Collision of rectangles

Given $a= [a_l, a_r]$ and  $b=[b_l,b_r]$ we want to know if they intersect.


```
    a_l--------------.
    |                |
    |                |
    '-------------- a_r

				    b_l--------------.
				    |                |
				    |                |
				    |                |
				    |                | 
				    |                |
				    '-------------- b_r

```

Now let's write a method that checks collissions between rectangles

```

def intersection(a,b):
    a_l_x, a_l_y = a.l   # top left corner
    a_r_x, a_r_y = a.r   # bottom right corner
    
    b_l_x, b_l_y = b.l   # top left corner
    b_r_x, b_r_y = b.r   # bottom right corner
    
    # one rectange is on the left side of the other
    if b_l_x > a_r_x or   a_l_x > b_r_x:
        return False
        
    # one rectange is on the left side of the other
    if a_r_y > b_l_y or   b_r_y > a_r_y:
        return False
        
    return True
```

#### Overlapping are of rectangles



#### Jumping

```
p(t) = 0.5 * acc * t^2 + vel * t + p_0
```