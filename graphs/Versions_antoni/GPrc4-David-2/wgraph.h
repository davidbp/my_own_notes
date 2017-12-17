#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
 using namespace std;
 typedef unsigned int vertex;
 typedef unsigned int index;
 typedef unsigned int wedge;
 typedef unsigned int weight;
 typedef vector<vector<pair<vertex,weight>> > wgraph;
 wgraph wgraph_complete( const vertex n, const weight Mw );
 wgraph wgraph_cycle( const vertex vn, const weight Mw );
 wgraph wgraph_bipartite_complete( const vertex n1, const vertex n2, const weight Mw );
 wgraph wgraph_read( string fname );
 void wgraph_write( const wgraph& G, ofstream& fout );
 weight TravellingSalesmanProblem( const wgraph &G, ofstream &fout  );