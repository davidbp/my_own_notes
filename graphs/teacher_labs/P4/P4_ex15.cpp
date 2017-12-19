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
a successió de vèrtexs a un stream de sortida.


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
    std::cout << "\nExecuting P4_ex15.out\n " << endl;
    ofstream fout;

    // Ex 15
    graph K6_ = graph_complete(6);
    fout.open("./results/K6.out");
    graph_write(K6_, fout);
    fout  << "\nHamiltonianCycle(K6):\n\n"  << HamiltonianCycle(K6_, fout) << endl;
    fout  << "\nHamiltonianCycles(K6):\n\n"  << HamiltonianCycles(K6_, fout) << endl;
    fout.close();


    // ##########################################################    
    //  UNWEIGHTED GRAPHS
    // ##########################################################


    // Ex 16
    wgraph WK6 = wgraph_complete(6, 9);
    fout.open( "./results/WK6.out" );    
    wgraph_write( WK6, fout );
    fout  << "\nTSP(K6):\n\n" << TravellingSalesmanProblem(WK6, fout) << endl;
    fout.close();

    // Ex 19
    graph K6 = graph_complete(6);
    vertex vn = K6.size();
    vector<color> Gc = vector<color>(vn, 0);
    fout.open("./results/vertex_coloring_K6.out");
    graph_write(K6, fout);
    fout  << "\nColoring (K6):\n\n"  <<  MinimalVertexColoring(K6, Gc, fout) << endl;
    fout.close();

    graph G0 = graph_read( "./input/graph0.in" );
    vertex vn0 = G0.size();
    vector<color> G0c = vector<color>(vn0, 0);
    fout.open("./results/vertex_coloring_graph0.out");
    graph_write(G0, fout);
    fout  << "\nColoring (graph0):\n\n"          <<  VertexColoring(G0, G0c, fout)        << endl;
    fout  << "\nMinimal Coloring (graph0):\n\n"  <<  MinimalVertexColoring(G0, G0c, fout) << endl;
    fout.close();

    graph G1 = graph_read( "./input/graph1.in" );
    vertex vn1 = G1.size();
    vector<color> G1c = vector<color>(vn1, 0);
    fout.open("./results/vertex_coloring_graph1.out");
    graph_write(G1, fout);
    fout  << "\nColoring (graph1):\n\n"  <<  MinimalVertexColoring(G1, G1c, fout) << endl;
    fout.close();

}
