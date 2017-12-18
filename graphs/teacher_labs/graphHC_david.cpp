//
//	HAMILTONIAN CYCLES AND TSP
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
 bool
    HamiltonianCycle( graph &G, ofstream& fout )
{
	vertex vn = G.size();
	vector<vertex> HCv( vn );
	vector<bool> HCl( vn, false );
	vector<index> ind( vn, 0 );
    index HCi = 0;
    vertex v = 0;
//  Initialize cycle from vertex 0
	HCv[HCi++] = v;
	HCl[v] = true;	
	//cout << "0";
    do{
	//  Forward
        while( ind[v] < G[v].size() ) { 
			if( !HCl[G[v][ind[v]]] ) {
			//  Continue cycle with edge to new vertex, renamed v	
				v = G[v][ind[v]++];
			//	cout << "-" << v;
				HCv[HCi++] = v;
				HCl[v] = true;
			}
			else ind[v]++;
		}
		if( HCi==vn ) {
		//  Full vertices vector
 			for( index i=0; i<G[v].size(); i++ ) {
				if( G[v][i]==0 ) {
				//  Hamiltonian cycle completed with edge to 0
					fout << "Hamiltonian cycle found: ";
					for( index HCj=0; HCj<vn; HCj++ )
						fout  << HCv[HCj] << "-" ;
					fout << "0" <<endl;
				}
			}
		}
    	HCi--;
		if( HCi==0 ) 
		//  Hamiltonian cycle not found
            return 0;  
	//  Backtracking
    HCl[v] = false;
		ind[v]= 0;
		v = HCv[HCi-1];
	} while( 1 );
}
//
//  Robert and Flores method for hamiltonian cycles
//
 index
    HamiltonianCycles( graph &G, ofstream& fout )
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
			//	cout << "-" << v;
		    }
		    else ind[v]++;
		}
		if( HCi==vn ) {
			for( index i=0;i<G[v].size();i++ ){
				if( G[v][i]==0 ){
					fout << "Hamiltonian cycle found: " ;
					for( index HCj=0; HCj<vn; HCj++ ) 
						fout  << HCv[HCj] << "-" ;
					fout << "0" <<endl;
					HCn++;
					break;
				}
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



 weight
    TravellingSalesmanProblem( wgraph &G, ofstream &fout )
{
	vertex vn = G.size();
    index HCi = 0, HCn = 0;
    vector<vertex> HCv( vn );
	vector<bool> HCl( vn, false );
	vector<index> ind( vn, 0 );
//  Index of minimal Hamiltonian cycle found 	
    index mHCn;
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
				
				if( HCw > mHCw ) {
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
			for( index i=0;i<G[v].size(); i++ ){
				if( G[v][i].first==0 ){
					HCw += G[v][i].second; 
				//  Cycle completed with edge to 0
                    HCn++;
					fout << "Hamiltonian cycle " << HCn << " with weight [" << HCw << "]: ";
					for( index HCj=0; HCj<vn; HCj++ )
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
				for( index HCj=0; HCj<vn; HCj++ )
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


 