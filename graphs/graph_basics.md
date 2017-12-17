##  P4: Hamiltonian and Eulerian paths and coloration.

A Hamiltonian path is a path that goes over all vertices of a graph without repeating any. A Hamiltonian cycle is a Hamiltonian path with an added edge that generates the cycle. This edge goes from the last vertex to the first one of the Hamiltonian path. 

#### Robert and Flores algorithm: Hamiltonian paths and cycles

The method starts in a vertex, selecting a new vertex that is not in the path as the next vertex. If there is an iteration where there is no vertex to go the algorithm performs backtracking.

Backtracking in this situation refers to unselecting the current vertex  $v$  , go to the previous one, and from there select another vertex $w$ if it is available. In case there is none available do the backtracking again. This process is repeated until there is a possible solution.

Notice that in the case of weighted graphs, the Travelling Salesman Problem (TSP) corresponds to finding a Hamiltonian cycle of minimum total weight.



#### Ex 15) graphHC.cpp with `HamiltonianCycle` and `HamiltonianCycles`

In order to code the functions  `HamiltonianCycle` and `HamiltonianCycles` we will use the following:

- **`HCv`** of type **`vector<size_t>`** : Used to push and pop vertices of the cycle beeing constructed.
- **`HCl`** of type **`vector<bool>`**:  Used to keep track of the vertices that have been used durint the construction of the path (or cycle). It is initialized containing all vertices as `false`.
- **`ind`** of type  **`vector<size_t>`**: Used to indicate in the adjacency list the graph, the index that we need to take into account in the next visit. It is initialized at  0 for all of its components. This vector will allow us to keep track of all the possible vertices without forgetting any durint the path creation.

An important detail about the code `y = x++` operator means, first make the asignment (put `x` into `y`) then increment `x` one unit.

```c++
//Example 1	
x = 3;
y = ++x;  // x contains 4, y contains 4

// Example 2
x = 3;
y = x++;  // x contains 4, y contains 3
```

Let us see the function that implements the hamiltonian cycle.

```c++
index HamiltonianCycle(const graph &G, std::ofstream &fout )
{
  	size_t vn = G.size();
    size_t HCi = 0;
    size_t v = 0;
    vector<size_t> HCv(vn);
    vector<size_t> ind(vn, 0);
    vector<bool> HCl(vn, false);
    HCv[HCi++] = v;
    HCl[v] = true;    
    do{
        while( ind[v] < G[v].size() ) { 
            if( !HCl[G[v][ind[v]]] ) {
                //  Continue cycle with edge to new vertex, renamed v    
                v = G[v][ind[v]++]; 
                // ind[v] = ind[v] + 1;
                // v = G[v][ind[v]-1];
                HCv[HCi++] = v;     // add v in the cycle
                HCl[v] = true;      // mark v in HCl (v marked as taken)
            }
            else ind[v]++;
        }
        if( HCi==vn ) {
             for( index i=0; i<G[v].size(); i++ ) {
                if( G[v][i]==0 ) { // es ultim vertex adj a 0 ?
                    //  Hamiltonian cycle completed with edge to 0
                    fout << "Hamiltonian cycle found: ";
                    for( index HCj=0; HCj<vn; HCj++ )
                        fout  << HCv[HCj] << "-" ;
                    fout << "0" <<endl;
                    return true ;
                }
            }
        }
        HCi--;
        if( HCi==0 ) 
            return 0;  //  Hamiltonian cycle not found
        HCl[v] = false;
        ind[v]= 0;
        v = HCv[HCi-1];
    }while( 1 );
}
```









