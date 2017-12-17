#include "graph.h"
// 
//  Complete graph to adjacencies lists
//
 graph
    graph_complete( const vertex n )
{    
    graph Kn( n );
    for( vertex v=0; v<n; v++) 
        for( vertex u=v+1; u<n; u++ ) {
             Kn[v].push_back( u );
             Kn[u].push_back( v );
        } 
    return Kn;
}
// 
//  Cycle graph to adjacencies lists
//
 graph
    graph_cycle( const vertex n )
 {    
    graph Cn( n );
    for( vertex v=0; v<n-1; v++ ) {
          Cn[v].push_back(v+1);
          Cn[v+1].push_back(v);
    }    
    Cn[n-1].push_back(0);
    Cn[0].push_back(n-1);
    return Cn;
}
// 
//  Bipartite complete graph to adjacencies lists
//
  graph
    graph_bipartite_complete( const vertex n1, const vertex n2 )
 {    
    graph Kn1n2( n1+n2 );
    for( vertex v1=0; v1<n1; v1++ ) {
        for( vertex v2=n1; v2<n1+n2; v2++ ) {
             Kn1n2[v1].push_back(v2);
             Kn1n2[v2].push_back(v1);
        }    
	}    
    return Kn1n2;
}


// 
//  Bipartite complete graph to adjacencies lists
//
  graph
    graph_horse( const vertex n, const vertex m )
{
	graph Hn( n*m );
	vertex v1, v2;
	for( index j=0; j<n; j++ ) 
		for( index i=0; i<m; i++ ) {
			if ( i>=2 && j+1<n )
				if ( (v1=i+j*m) < (v2=(i-2)+(j+1)*m) )  {
					Hn[v1].push_back(v2);
					Hn[v2].push_back(v1);
				}    
			if ( i>=1 && j+2<n )
			    if ( (v1=i+j*m) < (v2=(i-1)+(j+2)*m) )  {
					Hn[v1].push_back(v2);
					Hn[v2].push_back(v1);
				}    
			if ( i+1<m && j+2<n )
			    if ( (v1=i+j*m) < (v2=(i+1)+(j+2)*m) )  {
					Hn[v1].push_back(v2);
					Hn[v2].push_back(v1);
				}    
			if ( i+2<m && j+1<n )
				if ( (v1=i+j*m) < (v2=(i+2)+(j+1)*m) ) {
					Hn[v1].push_back(v2);
					Hn[v2].push_back(v1);
				}    
		}
		return Hn;
}	

// 
//  Read from file fname of edges to adjacencies lists
//
 graph 
	graph_read( string fname )
 {    
	ifstream fin;
    fin.open(fname.c_str());    
    if (fin.fail()) {
        cerr << "unable to open file " << fname.c_str() << " for reading" << endl;
        exit(1);
    }
 	int n, m;
	fin >> n >> m;
	graph G(n);
    for( int j=0; j<m; j++ ) {
         int u, v;
         fin >> u >> v; 
         G[u].push_back(v);
         if( u != v ) 
             G[v].push_back(u);
	}    
    return G;
}
// 
//  Write from adjacencies lists to stream
//  - vertices and edges numbers
//  - edges
//  - degrees and sorted degrees
  void 
	graph_write( graph& G, ofstream& fout )
 {    
//  Vertices number 
	vertex n = G.size();
//  Count edges number from adjacencies lists
//  int m = 0; 
//  for (int v = 0; v < n; v++) 
//       m = m + G[v].size();
//   m /= 2;
//  Write edges         
//    fout << "Graph with " << n << " vertices and " << m << " edges " << endl;
    fout << "Adjacencies lists" << endl;
    for( vertex v=0; v<n; v++ )  {
		fout << v << "\t:";
        for( index i=0; i<G[v].size(); i++) 
            fout << "\t" << G[v][i];
        fout << endl;
    }
    fout << "Edges" << endl;
    edge m = 0;
    for (vertex v = 0; v < n; v++) 
        for (index i = 0; i < G[v].size(); i++) 
            if( v <= G[v][i] ) {
                fout << v << " " << G[v][i] << endl;
                m++;
            }
     fout << "Graph with " << n << " vertices and " << m << " edges " << endl;
//  Count degrees
    vector<index> deg(n);
    for (vertex v = 0; v < n; v++) {
         deg[v] = G[v].size();
    }
//  Write sorted degrees sequence
    fout << "Degrees sequence" << endl;
    for (vertex v = 0; v < n; v++) {
        fout << deg[v] << " ";
    }
    fout << endl;
//  Sort degrees sequence
    sort(deg.begin(), deg.end());
//  Write sorted degrees sequence
    fout << "Sorted degrees sequence" << endl;
    for (vertex v = 0; v < n; v++) {
        fout << deg[v] << " ";
    }
    fout << endl;
 }
