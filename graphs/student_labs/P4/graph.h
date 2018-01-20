#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;
typedef size_t vertex;
typedef size_t edge;
typedef size_t degree;
typedef unsigned int color;      // for ex 19
typedef unsigned int component;
typedef unsigned int length;

// For unweighted graphs
typedef vector<vector<vertex> > graph;
graph graph_complete( size_t n );
graph graph_cycle(size_t n);
graph graph_star(size_t n);
graph graph_wheel(size_t n);
graph graph_bipartite_complete( size_t n1, size_t n2 );
graph graph_read( string fname );
void graph_write( graph& G, ofstream& fout );
graph graph_king( size_t n1, size_t n2 );
graph graph_rook( size_t n1, size_t n2 );
graph graph_knight( size_t n1, size_t n2 );
graph graph_bishop(size_t n1, size_t n2);
component BFS( graph &G );
component DFS( graph &G );
component BFS_Trees(graph &G, ofstream &fout);
component DFS_Trees(graph &G, ofstream &fout);
void Dijkstra( graph &G, vertex s, ofstream& fout );
void Dijkstra2(graph &G, size_t n1, size_t n2, size_t s1, size_t s2, ofstream& fout);

// For weighted graphs
typedef unsigned int weight;

typedef vector<vector<pair<vertex,weight>> > wgraph;
wgraph wgraph_complete( size_t n, weight Mw );
wgraph wgraph_bipartite_complete(size_t n1, size_t n2, weight Mw);
wgraph wgraph_cycle(size_t n, weight Mw);
wgraph wgraph_star(size_t n, weight Mw);
wgraph wgraph_wheel(size_t n, weight Mw);
wgraph wgraph_read( string fname );
void wgraph_write( wgraph &G, ofstream& fout );
weight Dijkstra(wgraph &G, vertex sv, vertex tv );
weight Diameter( wgraph &G );
void Dijkstra( wgraph &G, vertex sv, ofstream& fout );
void DijkstraTree( wgraph &G, vertex sv, ofstream& fout );
weight KruskalTrees( wgraph &G, ofstream& fout );
weight PrimTrees( wgraph &G, ofstream& fout );

// Added for P4 ex 15 
bool HamiltonianCycle( graph &G, ofstream& fout );
size_t HamiltonianCycles( graph &G, ofstream& fout );

// Added for P4 ex 19
color VertexColoring(graph &G, vector<color> &Gc, ofstream &fout);
color MinimalVertexColoring(graph &G, vector<color> &Gc, ofstream &fout );

