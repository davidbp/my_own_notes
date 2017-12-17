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
    HamiltonianCycle( const graph &G, ofstream& fout )
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
					return true;
				}
			}
		}
    	HCi--;
		if( HCi==0 ) 
		//  Hamiltonian cycle not found
            return false;  
	//  Backtracking
    //  for(int i=0; i<1+log(v+1.)/log(10.); i++ ) 
	//		cout<<"\b";
    //   
	    HCl[v] = false;
		ind[v]= 0;
		v = HCv[HCi-1];
	} while( 1 );
}
//
//  Robert and Flores method for hamiltonian cycles
//
 index
    HamiltonianCycles( const graph &G, ofstream& fout )
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
    //  backtracking
	//  for(int i=0; i<1+log((double)(v+1))/log(10.); i++ ) {
	//		cout<<"\b";
	//		cout<<" ";
	//		cout<<"\b";
	//	}
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



 index
    HamiltonianCycles( const graph &G, index n2, ofstream& fout )
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
					HCn++;
					fout << "Hamiltonian cycle " << HCn << endl ;
					for( index HCj=0; HCj<vn; HCj++ ) { 
						fout  << HCv[HCj] << "\t" ;
						if( HCj % n2 == n2-1 ) 
							fout << endl;
					}
					// fout << "0" <<endl;
					
                    cout << HCn <<endl;
					break;
				}
			}
		}
    //  backtracking
	//  for(int i=0; i<1+log((double)(v+1))/log(10.); i++ ) {
	//		cout<<"\b";
	//		cout<<" ";
	//		cout<<"\b";
	//	}
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
    TravellingSalesmanProblem( const wgraph &G, ofstream &fout )
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


 

weight TravellingSalesmanProblem0(const wgraph&G, ofstream& fout) {
    vertex vn=G.size();
    vector<vertex> HCv(vn);
    vector<bool> HCl(vn,false);
    vector<index> ind(vn,0);
    index HCi=0;
    vertex v=0;
    HCv[HCi++]=v;   // CORRECCIÓ
    HCl[v]=true;
    index HCn=0;
    index mHC=0;
    weight HCw=0;
    weight mHCw=UINT_MAX;
    vector<vertex> mHCv(vn); //guardar el cicle de menor pes
    do{ //forward, endavant
        while(ind[v]<G[v].size()) {//poguem tirar endavant=mentre tinguem adj
            //busquem un vertex adj a v que no sigui visitat
            if(!HCl[G[v][ind[v]].first]){ //si no te etiqueta, serà el nou vertex
                HCw+=G[v][ind[v]].second; //sumem el pes de l'aresta abans d'assignar el vertex nou
                v=G[v][ind[v]++].first; //l'anomenem v
                HCv[HCi++]=v;    //posicio que toca
                HCl[v]=true;    //per no tronar-lo a agafar
            }
            else ind[v]++; //si el vertex ja està visitat, mirem el seguent
        }
        if(HCi==vn){ //ja hem trobat un cami, però hem trobat un cicle?
            for(index i=0;i<G[v].size();i++) //si algun dels adjacents
                if(G[v][i].first==0){//victoria: caldrà escriure el cicle hamiltonia en fout
                    HCn++;
                    HCw+=G[v][i].second;
                    fout<<" Cycle with less weight: ";
                    for(vertex j=0;j<vn;j++) {fout<<HCv[j]<<"-";}
                    fout<<HCv[0]<<endl<<endl;
                    HCw-=G[v][i].second;//aqui
                    if(mHCw>HCw){
                        //mHC=HCn;
                        mHCw=HCw;
                        mHCv=HCv;
                    }
                    
                    HCw-=G[v][i].second;//CORRECCIÓ
                }
        }
        //backward
        HCi--;
        if(HCi==0) {   // CORRECCIÓ
            fout<<" The cycle with the minimum weight: ";
            for(vertex j=0;j<vn;j++){ fout<<mHCv[j]<<"-";}
            return HCw;   // CORRECCIÓ
        }    
          
        HCl[v]=false;
        ind[v]=0; //v es el vertex vell
        v=HCv[HCi-1]; //es el nou nou vertex, el que vull considerar ara
        HCw-=G[v][ind[v]-1].second;
    }while(true);
}
