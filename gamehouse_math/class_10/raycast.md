# Raycasting in 2D



The equation of a line is given in vector form by 
$$
(x,y) = (a,b) + \lambda(v_x,v_y)
$$


The line segment between $p$ and $q$ is
$$
\{\lambda p + (1-\lambda)q \vert \lambda \in [0,1]    \}
$$






## Intersecting line and segment



Given a ray $r$
$$
(x^r,y^r) = (p^r_x, p^r_y) + \lambda^r(v^r_x,v^r_y)
$$
Given line segment $s$ where $\lambda^s \in [0,1]$
$$
(x^s,y^s) = (p^s_x, p^s_y) + \lambda^s (v^s_x,v^s_y)
$$


If there is an intersection between the ray and the segment then


$$
(p^r_x, p^r_y) + \lambda^r(v^r_x,v^r_y) = (p^s_x, p^s_y) + \lambda^s (v^s_x,v^s_y)
$$


If we writhe the previous equation in coordinate terms we have:


$$
\begin{matrix}
p^r_x + \lambda^r v^r_x = p^s_x  + \lambda^s v^s_x \\
p^r_y  + \lambda^r v^r_y  =  p^s_y + \lambda^s v^s_y
\end{matrix}
$$

We can now isolate $\lambda^s$ and $\lambda^r$  from both equations



##### First let us isolate $ \lambda^r $ from both equations


$$
\begin{matrix}
 \lambda^r  = (p^s_x  + \lambda^s v^s_x - p^r_x) / v^r_x  \\
 \lambda^r  =  (p^s_y + \lambda^s v^s_y - p^r_y) / v^r_y  
\end{matrix}
$$

We can join the previous values into a single equation
$$
\begin{matrix}
 (p^s_x  + \lambda^s v^s_x - p^r_x) / v^r_x =  (p^s_y + \lambda^s v^s_y - p^r_y) / v^r_y  \\
\end{matrix}
$$
If we now multiply both sides of the previous equation by $ v^r_x v^r_y  $
$$
\begin{matrix}
 (p^s_x  + \lambda^s v^s_x - p^r_x)  v^r_y =  (p^s_y + \lambda^s v^s_y - p^r_y)  v^r_x  \\
 p^s_x v^r_y + \lambda^s v^s_x v^r_y - p^r_x v^r_y =  p^s_y v^r_x   + \lambda^s v^s_y v^r_x  - p^r_y  v^r_x  \\


\end{matrix}
$$

##### Isolate $\lambda^s$ from que previous equality


$$
\begin{matrix}
 p^s_x v^r_y + \lambda^s v^s_x v^r_y - p^r_x v^r_y =  p^s_y v^r_x   + \lambda^s v^s_y v^r_x  - p^r_y  v^r_x  \\
   \lambda^s v^s_x v^r_y   -  \lambda^s v^s_y v^r_x =  p^s_y v^r_x    - p^r_y  v^r_x  +  p^r_x v^r_y - p^s_x v^r_y\\
    \lambda^s ( v^s_x v^r_y   - v^s_y v^r_x) =   v^r_x (p^s_y    - p^r_y)  + v^r_y ( p^r_x  - p^s_x)\\
    \end{matrix}
$$
We end up with
$$
\begin{matrix}
    \lambda^s  =  \frac{v^r_x (p^s_y    - p^r_y)  - v^r_y ( p^r_x  - p^s_x)}{( v^s_x v^r_y   - v^s_y v^r_x)}\\   
\end{matrix}
$$


Once $\lambda^s$ is found we can substitute this value in equation (7) where we have $\lambda^r$ isolated
$$
\begin{matrix}
 \lambda^r  = (p^s_x  + \lambda^s v^s_x - p^r_x) / v^r_x  \\
\end{matrix}
$$

- If $\lambda^r>0$ and $0<\lambda^s<1$ there is intersection and the intersection point is given by substituting in (4) the value of $\lambda^s$

- If $\lambda^r>0$ and $0<\lambda^s<1$ is false: There is no intersection



Now we need to loop over all the line segments and find the closest intersection. That is the one with lowest $\lambda^r$ value.





## Raycasting many rays

We want to do the previous process for many rays we can do two solutions:

- Set a fixed number of rays (for example 360)

- Cast a number of rays that depends on the number of line segments vertices. We can cast a ray directly towars the begining and end of all segments and two more rays in the vicinity +- epsilon. 

  - With this trick we can use the rays from the true segment boundaries to the exterior as "light shadows"
  - This blog illustrates this effect: https://ncase.me/sight-and-light/

  

