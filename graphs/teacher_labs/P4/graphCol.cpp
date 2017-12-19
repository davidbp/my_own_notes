//
//    VERTEX COLORING
//  - by Brélaz method
//  - by backtracking method

#include "graph.h"
//
//  Vertex-coloring of one vertex
//
color Vertex1Coloring(graph &G, vector<color> &graph_coloring, color n_colors, vertex v, color initial_color)
{
    // color_used : vector of booleans
    vertex n = G.size();
    vector<bool> color_used(n_colors + 1, false);
    for( size_t i=0; i<G[v].size(); i++)  
        if ( G[v][i] < v )
            color_used[graph_coloring[G[v][i]]] = true;
    
    //  First color from initial_color not in previous adjacent vertex
    color color_ind;
    for( color_ind=initial_color; color_ind<=n_colors; color_ind++ )
        if ( !color_used[color_ind] ) {
            graph_coloring[v] = color_ind;
            break;
        }
    //  Color vertex with new color
    if ( color_ind==n_colors+1 ) {
        graph_coloring[v] = ++n_colors;
    }
    return n_colors;
}

color BrelazColoring(graph &G, vector<color> &graph_coloring)
{
    color cn;
    vertex n = G.size();
    //  Color vertex 0 with color 1
    graph_coloring[0] = cn = 1;
    //  Brélaz coloring: color other vertices with colors from 1
    for( vertex v=1; v<n; v++ )
        cn = Vertex1Coloring( G, graph_coloring, cn, v, 1 );
    return cn;
}


color VertexColoring(graph &G, vector<color> &graph_coloring, ofstream &fout)
{
    vertex vn = G.size();
    //  Prepare initial Brelaz coloring 
    graph_coloring = vector<color>(vn, 0);
    vector<color> Gpc(vn,0);
    color cn = BrelazColoring( G, Gpc );
    fout  << "\nVertex Coloring with " << cn << " colors\n";

    // print Vertex Coloring
     for(vertex v=0; v<vn; v++){
        graph_coloring[v] = Gpc[v];
        fout << v << "\t" << graph_coloring[v] << endl;
    }
}

//
//  Vertex Coloring of Graph
//
color MinimalVertexColoring(graph &G, vector<color> &graph_coloring, ofstream &fout)
{
    vertex vn = G.size();
    //  Prepare initial Brelaz coloring 
    graph_coloring = vector<color>(vn, 0);
    vector<color> Gpc(vn,0);
    color cn = BrelazColoring( G, Gpc );
        
    do { 
        //  Provisionally accept and write current coloring, saved in graph_coloring
        //  Save it as proving coloring Gpc 
        //  Try successive reduction of color number cn
        //fout  << "Coloraci de vèrtexs amb " << cn << " colors\n";
        fout  << "\nColoring with " << cn << " colors\n";
        //cout  << "Coloration with " << cn << " colors\n";
        for( vertex v=0; v<vn; v++ ) {
            graph_coloring[v] = Gpc[v];
            fout << v << "\t" << graph_coloring[v] << endl;
        }
        for( vertex v=0; v<vn; v++ )
            for( size_t i=0; i<G[v].size(); i++ )
                if( v<G[v][i] && graph_coloring[v]==graph_coloring[G[v][i]] )
                    cout << "Coloring error : Same color " << v << "-" << G[v][i] ;
        
        //  Search first vertex cnv with current maximum color cn
        vertex cnv;
        for( cnv=0; cnv<vn; cnv++ )    
            if( Gpc[cnv] == cn )
                break;
        do { 
        //  Try possible reduction of cn to cn-1
        //  Backtrack vertex from cnv:
        //  - find cnv to be colored with first color bigger than its color
            do {
               //  Take previous bcnv if possible
                cnv--;                                            
                   if ( cnv == 0 ) {
                 //  When backtracking reachs original vertex all possibilities exhausted:
                //  last coloring graph_coloring was ok
                    //fout  << "\nMinimal vertex coloring found\n";
                    return cn;
                }
                   Vertex1Coloring( G, Gpc, cn, cnv, Gpc[cnv]+1 );
            } while( Gpc[cnv]>=cn );
        //  Try to color posterior vertices to bcnv without color cn
        //  until a vertex cnv cannot be colored with cn-1 colors
        //  new vertex to backtrack
            for( ++cnv; cnv<vn; cnv++ ) {
                Vertex1Coloring( G, Gpc, cn, cnv, 1 );
                if ( Gpc[cnv]>= cn ) {
                    break;
                }
            }
        } while( cnv<vn );
        cn--;
    } while( cn > 0 );  
    return 0 ; // added by me
} 


/*
 //
//  Edge coloring by vertex coloring line graph
//
 color
    MinimalEdgeColoring(   graph& G, edges& GE, ofstream& fout )
{
    graph LG;
    vector<color> Lgraph_coloring;
    edges LGE;
    line_graphe( G, GE, LG, LGE );
    graphe_write( LG, LGE, fout );
    fout << "Edge coloring\n";
    cout << "Edge coloring\n";
    color ecn = MinimalVertexColoring( LG, Lgraph_coloring, fout );
    vertex n=G.size();
    for( vertex v=0; v<n; v++ )
        for( size_t i=0; i<G[v].size(); i++ )
            if( v<G[v][i] )
                fout << v << "\t" << G[v][i] << "\t"  << GE[vip(v,i)] <<  "\t"  << Lgraph_coloring[GE[vip(v,i)]] << endl;    
    for( color c=1; c<=ecn; c++ ) {
        fout << "Color " << c << endl;
        for( vertex v=0; v<n; v++ )
            for( size_t i=0; i<G[v].size(); i++ )
                if( v<G[v][i] && Lgraph_coloring[GE[vip(v,i)]]==c )
                    fout << v << "\t" << G[v][i] << "\t"  << GE[vip(v,i)] <<  "\t"  << Lgraph_coloring[GE[vip(v,i)]] << endl;    
    }
    return ecn;
 }

 */