#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "graph.h"
using namespace std;
 typedef pair<vertex,index> vip;
 typedef map<vip,edge> edges;
 void graphe_complete( graph &Kn, edges &KnE, index n );
 void graphe_cycle( graph &Cn, edges &CnE, index n );
 void graphe_bipartite_complete( graph &Kn1n2, edges &Kn1n2E, index n1, index n2 );
 void graphe_star( graph &Sn, edges &SnE, index n );
 void graphe_wheel( graph &Wn, edges &WnE, index n );
 void line_graphe( const graph &G, edges &GE, graph &LG, edges &LGE );
 void graphe_read( graph &G, edges &GE, string fname );
 void graphe_write( graph &G, edges &GE, ofstream& fout );
 color MinimalVertexColoring( const graph& G, vector<color>& Gc, ofstream& fout );
 color MinimalEdgeColoring( const graph& G, edges &GE, ofstream& fout );
 bool Hierholzer( const graph &G, edges &GE, ofstream &fout );
