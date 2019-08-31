#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef size_t vertex;
typedef size_t edge;
typedef size_t ind;
typedef size_t degree;
typedef unsigned int component;
typedef unsigned int length;
typedef vector<vector<vertex> > graph;
graph graph_complete(ind n);
graph graph_cycle(ind n);
graph graph_star(ind n);
graph graph_wheel(ind n);
graph graph_bipartite_complete( ind n1, ind n2 );
graph graph_read(string fname );
void graph_write(graph& G, ofstream& fout );
void graph_write2(graph& G, ind n1, ind n2, ofstream& fout);
graph graph_king(ind n1, ind n2 );
graph graph_rook(ind n1, ind n2 );
graph graph_knight(ind n1, ind n2 );
graph graph_bishop(ind n1, ind n2);
component BFS(graph &G );
component DFS(graph &G );
component BFS_Trees(graph &G, ofstream &fout);
component DFS_Trees(graph &G, ofstream &fout);
void Dijkstra(graph &G, vertex s, ofstream& fout );
void Dijkstra2(graph &G, ind n1, ind n2, ind s1, ind s2, ofstream& fout);
