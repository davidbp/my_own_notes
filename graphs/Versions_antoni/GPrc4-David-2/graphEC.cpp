//
//	EULERIAN CIRCUITS
//  - by Hierholzer metho
//
#include "graphe.h"

//
//  Breadth First Search: returns components number
//
 index
    BFS( const graph &G ) 
{
    vertex vn = G.size();
    index cn = 0;
    vector<bool> BFSl( vn, false );
	vector<int> BFSv( vn );
	index BFSn = 0;
    vertex rv;
	do {
	//  Find non labeled vertex as root vertex rv of new component
		for( rv=0; rv<vn; rv++ ) 
			if( !BFSl[rv] ) {
			//  New root r found for new component
				cn++;
			//  Label and list v
				vertex v = rv;
				BFSl[v] = true;
				BFSv[BFSn++] = v;
				index k = BFSn;
				if( G[v].size() )
				do {
					for( index i=0; i<G[v].size(); i++ ) 
						if( !BFSl[G[v][i]] ) {
						//  Label and list adjacent G[v][i]
							BFSl[G[v][i]] = true;
							BFSv[BFSn++] = G[v][i];
						}
				//  New vertex v 
					v = BFSv[k++]; 				
 				} while( k < BFSn );
			}
    } while( rv != vn );
    return cn;
}


 bool 
	Hierholzer( const graph &G, edges &GE, ofstream &fout )
{
	vertex vn = G.size();
	vector<index> rdeg( vn );
//  Test if it is connected
	if( BFS( G )!=1 ){
		fout << "El graf no és eulerià\n" << endl;
		return false;
	}
	edge en = 0;
//	Initialize rdeg, fill degrees vector and test degrees parity: count edges number
	for( vertex v=0; v<vn; v++){
		rdeg[v] = G[v].size();
		if( rdeg[v]%2 ) {
			fout << "El graf no és eulerià\n" << endl;
			return false;
		}
		en += rdeg[v];
	}
	en/=2;
	fout << en << " arestes" << endl;
//  Construct eulerian circuit vertices vector ECV
//  Initialitze label of each edge to false
	vector <vertex> ECV( en );
	vector<bool> Gl( en, false );
	index ECn = 0;
	vertex v0 = 0;
//  First cycle from initial vertex v0=0
	vertex v = v0;
	do{
		ECV[ECn++] = v;
		for( index i=0; i<G[v].size(); i++ ){
			edge e = GE[vip(v,i)];
			if( !Gl[e] ){
				Gl[e] = true;
				rdeg[v]--;
				v = G[v][i];
				rdeg[v]--;
				break;
			}
		}
	} while( v!=v0 );
//  Find and concatenate new cycles to rotated current circuit
	while( ECn < en-1 ) {
	//  Find new initial vertex v0 for cycle with positive residual degree and in current circuit
		for( v0=0; v0<vn; v0++ )
			if( rdeg[v0]>0 && rdeg[v0]!=G[v0].size() )
				break;
	//  Rotate cicle: v0 at begining
		while( ECV[0] != v0 ) { 
			vertex ECV0 = ECV[0];
			for( index ECj=1; ECj<ECn; ECj++)
				ECV[ECj-1] = ECV[ECj];
			ECV[ECn-1] = ECV0;
		}
		v = v0;
	//  Concatenate cycle at the end of current rotated circuit
		do {
			ECV[ECn++] = v;
			for( index i=0; i<G[v].size(); i++ ){
				edge e = GE[vip(v,i)];
				if( !Gl[e] ){
					Gl[e] = true;
					rdeg[v]--;
					v = G[v][i];
					rdeg[v]--;
					break;
				}
			}
		} while( v!=v0 );
	}
	fout << "Circuit eulerià:" << endl << "   ";
	for( edge ECj=0; ECj<en; ECj++ )
		fout << ECV[ECj];
	return true;
}

