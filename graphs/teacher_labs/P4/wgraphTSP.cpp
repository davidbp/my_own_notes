//
//    HAMILTONIAN CYCLES AND TSP
//  - Robert and Flores method: backtracking
//  
#include "wgraph.h"
#include <cmath>
#include <ctime>

weight TravellingSalesmanProblem( wgraph &G, ofstream &fout )
{
    vertex vn = G.size();
    size_t HCi = 0, HCn = 0;
    vector<vertex> HCv( vn );
    vector<bool> HCl( vn, false );
    vector<size_t> ind( vn, 0 );
//  size_t of minimal Hamiltonian cycle found     
    size_t mHCn;
//  Minimal Hamiltonian cycle weight (minimum)
     weight mHCw = UINT_MAX;
//  Minimal Hamiltonian cycle vertices
    vector<vertex> mHCv( vn );
//  Current hamiltonian cycle weight
    weight HCw = 0; 
//  Initialize vertices vector with vertex 0
    vertex v = 0;
    HCv[HCi++] = v;
    HCl[v] = true;    
    do{
    //  Forward BRANCH
        while( ind[v] < G[v].size() ){   
            if( !HCl[G[v][ind[v]].first] ){
            //  Continue cycle with edge to new vertex
                HCw += G[v][ind[v]].second;
                
                if( HCw > mHCw ){
                //  BOUND
                    HCw -= G[v][ind[v]].second;
                    break;
                }
                
                v = G[v][ind[v]++].first;
                HCv[HCi++] = v;
                HCl[v] = true;
                
            }
            else ind[v]++;
        }   
        if( HCi==vn ) {
        //  Vector full
            for( size_t i=0;i<G[v].size(); i++ ){
                if( G[v][i].first==0 ){
                    HCw += G[v][i].second; 
                //  Cycle completed with edge to 0
                    HCn++;
                    fout << "Hamiltonian cycle " << HCn << " with weight [" << HCw << "]: ";
                    for( size_t HCj=0; HCj<vn; HCj++ )
                        fout << HCv[HCj] << "-" ;
                    fout << "0" << endl; 
                //  Test minimum weight
                    if( mHCw > HCw ){
                        mHCn = HCn;
                        mHCw = HCw;
                        mHCv = HCv;
                    }
                    HCw -= G[v][i].second;
                    break;
                }
            }
        } 
        HCi--;
        if( HCi==0 ){
            if( HCn ){
                fout << "Hamiltonian cycle " << mHCn << " with minimum weight [" << mHCw << "]: ";
                for( size_t HCj=0; HCj<vn; HCj++ )
                    fout << mHCv[HCj] << "-" ;
                fout << "0" << endl; 
                return mHCw;
            }
            else return 0;
        }
        
    //  Backtracking:      
        HCl[v] = false;
        ind[v] = 0;
        v = HCv[HCi-1];
        HCw -= G[v][ind[v]-1].second;
    } while( 1 );
  
}




 