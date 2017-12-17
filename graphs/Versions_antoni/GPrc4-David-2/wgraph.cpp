#include "wgraph.h"
// 
//  Weighted complete graph to weighted adjacencies lists
//
 wgraph
    wgraph_complete( const vertex n, const weight Mw )
 {    
    wgraph WKn( n );
    for( vertex v = 0; v < n; v++ ) 
        for( vertex i = v+1; i<n; i++ ) {
			int w = rand()%Mw+1;
			WKn[v].push_back(pair<vertex,weight>(i,w));
			WKn[i].push_back(pair<vertex,weight>(v,w));
        }
    return WKn;
}
// 
//  Cycle graph to adjacencies lists
//
 wgraph
    wgraph_cycle( const vertex n, const weight Mw )
 {    
    wgraph WCn( n );
	weight w;
    for( vertex v=0; v<n-1; v++ ) {
		  w = rand()%Mw+1;
          WCn[v].push_back(pair<vertex,weight>(v+1,w));
          WCn[v+1].push_back(pair<vertex,weight>(v,w));
    }    
	w = rand()%Mw+1;
    WCn[n-1].push_back(pair<vertex,weight>(0,w));
    WCn[0].push_back(pair<vertex,weight>(n-1,w));
    return WCn;
}
// 
//  Bipartite complete graph to adjacencies lists
//
  wgraph
    wgraph_bipartite_complete( const vertex n1, const vertex n2, const weight Mw )
 {    
    wgraph WKn1n2( n1+n2 );
	vertex w;
    for( vertex v1=0; v1<n1; v1++ ) {
        for( vertex v2=n1; v2<n1+n2; v2++ ) {
			w = rand()%Mw+1;
            WKn1n2[v1].push_back(pair<vertex,weight>(v2,w));
            WKn1n2[v2].push_back(pair<vertex,weight>(v1,w));
        }   
	}    
    return WKn1n2;
}

// 
//  Read from file fname of weighted edges to adjacencies lists
//
 wgraph
	wgraph_read( string fname )
 {    
	ifstream fin;
    fin.open(fname.c_str());    
    if (fin.fail()) {
        cerr << "unable to open file " << fname.c_str() << " for reading" << endl;
        exit(1);
    }
 	vertex n;
	wedge m;
	fin >> n >> m;
	wgraph G(n);
    for( wedge j=0; j<m; j++ ) {
        vertex u, v; 
		weight w;
        fin >> u >> v >> w; 
        G[u].push_back(pair<vertex,weight>(v,w));
        if( u != v ) 
            G[v].push_back(pair<vertex,weight>(u,w));
    }    
    return G;
}
// 
//  Write from weighted adjacencies lists to stream
//  - vertices and edges numbers
//  - weighted edges
//  - degrees and sorted degrees
  void 
	wgraph_write( const wgraph& G, ofstream& fout )
 {    
//  Vertices number 
	vertex n = G.size();
//  Count edges number from adajacency matrix
    wedge m = 0; 
    for (vertex v = 0; v < n; v++) 
         m = m + G[v].size();
    m /= 2;
//  Write edges         
    fout << "WGraph with " << n << " vertices and " << m << " edges " << endl;
    fout << "Weighted adjacency lists" << endl;
//  Allocate/read weighted adjacent pairs
    for (vertex v = 0; v < n; v++) {
        fout << v << ":";
        for (index i = 0; i < G[v].size(); i++)  {
            fout << " " << G[v][i].first << "[" << G[v][i].second << "] ";
        }
        fout << endl;
    }
    fout << endl;
    fout << "Edges" << endl;
    for (vertex v = 0; v < n; v++) 
        for (index i = 0; i < G[v].size(); i++) 
            if( v <= G[v][i].first )
                fout << v << " " << G[v][i].first <<  "[" << G[v][i].second << "] " << endl;
             
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
