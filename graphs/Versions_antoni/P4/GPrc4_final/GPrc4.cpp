
/*
To compile this use the following:
c++ -std=c++11 -c *.cpp
c++ -std=c++11 *.o -o a.out
*/

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "graph.h"
#include "wgraph.h"

/*

### What needs to be done

Exercici 15 Modifica el programa amb un altre modul graphHC.cpp que
contingui funcions

- HamiltonianCycle 
- HamiltonianCycles

que implementin el metode de backtracking de Robert i Flores per a la 
cerca de cicles hamiltonians, un o tots. Aquestes funcions haurien de
retornar el nombre de cicles hamiltonians trobats i escriure’ls com
a successi ́o de v`ertexs a un stream de sortida.


### Where to test the code

Implementa de nou un programa principal per tal que escrigui aquesta 
informacio dels cicles hamiltonians trobats en els grafs 
     Kn, Kn1,n2 , Cn, Sn, Wn 
en els fitxers 
    Kn.out, Kn1 n2.out, Cn.out, Sn.out, Wn.out,
per a diferents valors de n, n1, n2 permesos per un temps d’execució
raonable.

Continua el programa principal per tal que trobi el nombre de 
cicles hamiltonians en els grafs Ktn1,n2 del moviment del 
cavall en taulers de diferents mides n1xn2 i els escrigui 
en el fitxer Ktn1 n2.out.


*/
int main()
{
    std::cout << "\nExecuting GPrc23.out\n " << endl;
    ofstream fout;

    // ##########################################################    
    //  UNWEIGHTED GRAPHS
    // ##########################################################

    //  Complete graph to adjacencies lists K6
    graph K6 = graph_complete(6);
    fout.open("./results/K6.out");
    graph_write(K6, fout);
    fout  << "\nNumber of DFS components: "  << DFS_Trees(K6, fout)  << endl;
    DFS_Trees(K6, fout);
    fout  << "\nNumber of BFS components: "  << BFS_Trees(K6, fout)  << endl;
    BFS_Trees(K6, fout);
    Dijkstra(K6, 0, fout);
    fout.close();

    //  Bipartite complete graph to adjacencies lists K42
    graph K4_2 = graph_bipartite_complete(4, 2);
    fout.open("./results/K4_2.out");
    graph_write(K4_2, fout);
    fout  << "\nNumber of DFS components: "  << DFS_Trees(K4_2, fout)  << endl;
    fout  << "\nNumber of BFS components: "  << BFS_Trees(K4_2, fout)  << endl;
    Dijkstra(K4_2, 0, fout);
    fout.close();
    
    //  Cycle graph to adjacencies lists C6
    graph C6 = graph_cycle(6);
    fout.open("./results/C6.out");
    graph_write(C6, fout);
    fout  << "\nNumber of DFS components: "  << DFS_Trees(C6, fout)  << endl;
    fout  << "\nNumber of BFS components: "  << BFS_Trees(C6, fout)  << endl;
    Dijkstra(C6, 0, fout);
    BFS_Trees(C6, fout);
    fout.close();
    
    //  Star graph to adjacencies lists S6
    graph S6 = graph_star(6);
    fout.open("./results/S6.out");
    graph_write(S6, fout);
    fout  << "\nNumber of DFS components: "  << DFS_Trees(S6, fout)  << endl;
    fout  << "\nNumber of BFS components: "  << BFS_Trees(S6, fout)  << endl;
    Dijkstra(S6, 0, fout);
    BFS_Trees(S6, fout);
    fout.close();
    
}
