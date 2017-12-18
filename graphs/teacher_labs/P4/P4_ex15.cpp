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

    // ##########################################################    
    //  UNWEIGHTED GRAPHS
    // ##########################################################

    /*
    //  Complete graph to adjacencies lists K6
    graph K6 = graph_complete(6);
    fout.open("./results/K6.out");
    graph_write(K6, fout);
    fout  << "\nHamiltonianCycle(K6):\n\n"  << HamiltonianCycle(K6,fout) << endl;
    fout.close();
	*/

    wgraph WK6 = wgraph_complete(6, 9);
	fout.open( "./results/WK6.out" );    
	wgraph_write( WK6, fout );
	fout  << "\nTSP(K6):\n\n" << TravellingSalesmanProblem(WK6, fout) << endl;
    fout.close();

}
