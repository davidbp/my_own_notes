#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

typedef size_t vertex;
typedef size_t edge;
typedef size_t degree;
typedef unsigned int component;
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
