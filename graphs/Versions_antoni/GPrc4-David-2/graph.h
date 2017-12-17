#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

 using namespace std;
 typedef unsigned int color;
 typedef unsigned int vertex;
 typedef unsigned int index;
 typedef unsigned int edge;
 typedef vector<vector<vertex> > graph;
 graph graph_complete( const vertex n );
 graph graph_cycle( const vertex n );
 graph graph_bipartite_complete( const vertex n1, const vertex n2 );
 graph graph_horse( const vertex n, const vertex m );
 graph graph_read( string fname );
 void graph_write( graph& G, ofstream& fout );
 index HamiltonianCycle( const graph &G, ofstream &fout  );	
 index HamiltonianCycles( const graph &G, ofstream &fout  );
 index HamiltonianCycles( const graph &G, const vertex n2, ofstream &fout  );
 color BrelazColoring( const graph& G, vector<color>& Gc );
 color MinimalVertexColoring( const graph& G, vector<color>& Gc, ofstream& fout );
 