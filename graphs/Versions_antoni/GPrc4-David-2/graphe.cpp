#include "graphe.h"
// 
//  Complete graph to adjacencies lists and mapped edges
//
 void
    graphe_complete( graph &Kn, edges &KnE, vertex n )
{    
    Kn = graph( n );
	edge e=0;
    for( vertex v=0; v<n; v++) 
        for( vertex u=v+1; u<n; u++ ) {
			 KnE[vip(v,Kn[v].size())] = e;
			 KnE[vip(u,Kn[u].size())] = e++;	
		     Kn[v].push_back( u );
             Kn[u].push_back( v );
       } 
}
// 
//  Bipartite complete graph to adjacencies lists and mapped edges
//
 void
    graphe_bipartite_complete( graph &Kn1n2, edges &Kn1n2E, vertex n1, vertex n2 )
{    
	vertex n = n1+n2;
    Kn1n2 = graph( n );
	edge e=0;
    for( vertex v1=0; v1<n1; v1++) 
        for( vertex v2=n1; v2<n; v2++ ) {
			 Kn1n2E[vip(v1,Kn1n2[v1].size())] = e;
			 Kn1n2E[vip(v2,Kn1n2[v2].size())] = e++;	
		     Kn1n2[v1].push_back( v2 );
             Kn1n2[v2].push_back( v1 );
        } 
}
// 
//  Cycle graph to adjacencies lists and mapped edges
//
 void
    graphe_cycle( graph &Cn, edges &CnE, vertex n )
{    
	Cn = graph( n );
	edge e=0;
	for( vertex v=0; v<n-1; v++) {
		 CnE[vip(v,Cn[v].size())] = e;
		 CnE[vip(v+1,Cn[v+1].size())] = e++;	
         Cn[v].push_back( v+1 );
		 Cn[v+1].push_back( v );
	}
	CnE[vip(n-1,Cn[n-1].size())] = e;
	CnE[vip(0,Cn[0].size())] = e++;	
	Cn[n-1].push_back( 0 );
	Cn[0].push_back( n-1 );
}
// 
//  Star graph to adjacencies lists and mapped edges
//
 void
    graphe_star( graph &Sn, edges &SnE, vertex n )
{    
	Sn = graph( n+1 );
	edge e=0;
	for( vertex v=0; v<n; v++) {
		 SnE[vip(v,Sn[v].size())] = e;
		 SnE[vip(n,Sn[n].size())] = e++;	
         Sn[v].push_back( n );
		 Sn[n].push_back( v );
	}
}

// 
//  Wheel graph to adjacencies lists and mapped edges
//
 void
    graphe_wheel( graph &Wn, edges &WnE, vertex n )
{    
	Wn = graph( n+1 );
	edge e=0;
	for( vertex v=0; v<n; v++) {
		 WnE[vip(v,Wn[v].size())] = e;
		 WnE[vip(n,Wn[n].size())] = e++;	
         Wn[v].push_back( n );
		 Wn[n].push_back( v );
	}
	for( vertex v=0; v<n-1; v++) {
		 WnE[vip(v,Wn[v].size())] = e;
		 WnE[vip(v+1,Wn[v+1].size())] = e++;	
         Wn[v].push_back( v+1 );
		 Wn[v+1].push_back( v );
	}
	WnE[vip(n-1,Wn[n-1].size())] = e;
	WnE[vip(0,Wn[0].size())] = e++;	
	Wn[n-1].push_back( 0 );
	Wn[0].push_back( n-1 );
    
}

// 
//  Line graph  
//
 void
    line_graphe( const graph &G, edges &GE, graph &LG, edges &LGE )
{    
	vertex vn = G.size();
//  Compute edges number en
	edge en=0;
	for( vertex v=0; v<vn; v++) 
        for( index i=0; i<G[v].size(); i++ ) 
			if( v<G[v][i] )
				en++;
//  Construct adjacencies lists LG of graph line
//  Edge ei of G:  v - G[v][i]  
//  adjacent 'edges' ek of ei: in adjacent lists of v and G[v][i]
//  line edges le: ei-ek
	LG = graph( en );
	edge ei, ek=0, le=0;
    for( vertex v=0; v<vn; v++) {
        for( index i=0; i<G[v].size(); i++ ) 
			if( v<G[v][i] ) {
			ei = GE[vip(v,i)];
			//  Line vertex: edge ei
                for( index k=0; k<G[v].size(); k++ ) {
				//  Line adjacents: incidencies to v bigger than ei
                    edge ek = GE[vip(v,k)];
					if( ek > ei ) {
						LGE[vip(ei,LG[ei].size())] = le;
                        LGE[vip(ek,LG[ek].size())] = le++;
						LG[ei].push_back( ek );
                        LG[ek].push_back( ei );
					}
                }
                for( index k=0; k<G[G[v][i]].size(); k++ ) {
                //  Line adjacents: incidencies to G[v][i] bigger than e
                    edge ek = GE[vip(G[v][i],k)];
					if( ek > ei ) {
						LGE[vip(ei,LG[ei].size())] = le;
                        LGE[vip(ek,LG[ek].size())] = le++;
				  	    LG[ei].push_back( ek );
                        LG[ek].push_back( ei );
					}
                }
			}						
    }
}
// 
//  Read from file fname of edges to adjacencies lists
//
 void
	graphe_read( graph &G, edges &GE, string fname )
 {    
	ifstream fin;
    fin.open(fname.c_str());    
    if (fin.fail()) {
        cerr << "unable to open file " << fname.c_str() << " for reading" << endl;
        exit(1);
    }
 	vertex vn;
	edge en;
	fin >> vn >> en;
	G = graph( vn );
    for( edge e=0; e<en; e++ ) {
         vertex u, v;
         fin >> v >> u; 
		 GE[vip(v,G[v].size())]=e;
         G[v].push_back(u);
		 if( u != v ) {
			 GE[vip(u,G[u].size())]=e;
			 G[u].push_back(v);
		 }
	}    
}
// 
//  Write from adjacencies lists to stream
//  - vertices and vips numbers
//  - vips
//  - degrees and sorted degrees
  void 
	graphe_write( graph& G, edges &GE, ofstream& fout )
 {    
//  Vertices number 
	vertex vn = G.size();
//  Count vips number from adjacencies lists
    edge en = 0; 
    for ( vertex v = 0; v < vn; v++) 
        en =en + G[v].size();
    en /= 2;
//  Write vips         
    fout << "Graph with " << vn << " vertices and " << en << " edges " << endl;
    fout << "Adjacencies lists" << endl;
    for( vertex v=0; v<vn; v++ )  {
		fout << v << "\t:";
        for( index i=0; i<G[v].size(); i++) 
            fout << "\t" << G[v][i] << " (" << GE[vip(v,i)] <<  ") " ;
        fout << endl;
    }
    fout << "Edges" << endl;
    for( vertex v = 0; v < vn; v++) 
        for( index i = 0; i < G[v].size(); i++) 
            if( v <= G[v][i] )
                fout << v << " " << G[v][i] << endl;
//  Count degrees
    vector<index> deg(vn);
    for( vertex v = 0; v < vn; v++ ) {
         deg[v] = G[v].size();
    }
//  Write sorted degrees sequence
    fout << "Degrees sequence" << endl;
    for( vertex v = 0; v < vn; v++) {
        fout << deg[v] << " ";
    }
    fout << endl;
//  Sort degrees sequence
    sort(deg.begin(), deg.end());
//  Write sorted degrees sequence
    fout << "Sorted degrees sequence" << endl;
    for( vertex v = 0; v < vn; v++ ) {
        fout << deg[v] << " ";
    }
    fout << endl;
 }
