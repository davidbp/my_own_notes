//
//    HAMILTONIAN CYCLES AND TSP
//  - Robert and Flores method: backtracking
//  
#include "graph.h"
#include "wgraph.h"
#include <cmath>
#include <ctime>
#include <conio.h>
//
//  Robert and Flores method for hamiltonian cycle
//
// 
index HamiltonianCycle(const graph &G, ofstream &fout )
{
    size_t vn = G.size();
    vector<size_t> HCv( vn );
    vector<bool> HCl( vn, false );
    vector<size_t> ind( vn, 0 );
    size_t HCi = 0;
    size_t v = 0;

    //  Initialize cycle from vertex 0
    HCv[HCi++] = v;
    HCl[v] = true;    
    //cout << "0";
    do{
        //  Forward
        while( ind[v] < G[v].size() ) { // if index == degree no need for backtracking
            if( !HCl[G[v][ind[v]]] ) {
                //  Continue cycle with edge to new vertex, renamed v    
                v = G[v][ind[v]++];
                HCv[HCi++] = v;
                HCl[v] = true;
            }
            else ind[v]++;
        }
        if( HCi==vn ) {
             //  Full vertices vector
             for( index i=0; i<G[v].size(); i++ ) {
                 //
                 // Fill in this space ########################################
                 // check if Hamiltonian cycle completed with edge to 0, 
                 // In that case print the Hamiltonian cycle
                 //     (that is iterate over HCv)
                 // ###########################################################
            }
        }
        HCi--;
        if( HCi==0 ) 
            return 0;  //  Hamiltonian cycle not found


        HCl[v] = false;
        ind[v]= 0;      // If the while is not verified backtrack
        v = HCv[HCi-1];
    }while( 1 );
}

//
//  Robert and Flores method for hamiltonian cycles
//
index HamiltonianCycles( const graph &G, ofstream& fout )
{
    vertex vn = G.size();
    vector<vertex> HCv( vn );
    vector<bool> HCl( vn, false );
    vector<index> ind( vn, 0 );
    vertex v = 0;
    index HCi = 0, HCn = 0;
    HCv[HCi++] = v;
    HCl[v] = true;    
    //cout << "0";
    do{
        while( ind[v] < G[v].size() ){  
            if( HCl[G[v][ind[v]]]== false){
                v = G[v][ind[v]++];
                HCv[HCi++] = v;
                HCl[v] = true;
            //    cout << "-" << v;
            }
            else ind[v]++;
        }
        if( HCi==vn ) {
            for( index i=0;i<G[v].size();i++ ){
             //
             // Fill in this space ########################################
             // Make sure you update HCn every time you find a cycle
             // ###########################################################
            }
        }
        HCi--;
        if(HCi==0){
            fout << "Number of Hamiltonian cycles: " << HCn << endl;
            return HCn;
        }

        HCl[v] = false;
        ind[v] = 0;    
        v = HCv[HCi-1];
    } while( 1 );
}
