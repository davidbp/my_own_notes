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
         // assign color_used

    //  First color from initial_color not in previous adjacent vertex
    color color_ind;
    for( color_ind=initial_color; color_ind<=n_colors; color_ind++)
        // assign graph_coloring[v]
    
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
    vector<color> graph_current_coloring(vn,0);
    color cn = BrelazColoring( G, graph_current_coloring );
    fout  << "\nVertex Coloring with " << cn << " colors\n";

    // print Vertex Coloring
     for(vertex v=0; v<vn; v++){
        graph_coloring[v] = graph_current_coloring[v];
        fout << v << "\t" << graph_coloring[v] << endl;
    }
    
    return cn;
}

//
//  Vertex Coloring of Graph
//
color MinimalVertexColoring(graph &G, vector<color> &graph_coloring, ofstream &fout)
{
    vertex vn = G.size();
    graph_coloring = vector<color>(vn, 0);
    vector<color> graph_current_coloring(vn,0);
    color cn = BrelazColoring( G, graph_current_coloring );
        
    do { 
        //  Provisionally accept and write current coloring graph_current_coloring to graph_coloring
        fout  << "\nColoring with " << cn << " colors\n";
        for( vertex v=0; v<vn; v++ ) {
            graph_coloring[v] = graph_current_coloring[v];
        }
        for( vertex v=0; v<vn; v++ )
            for( size_t i=0; i<G[v].size(); i++ )
                if( v<G[v][i] && graph_coloring[v]==graph_coloring[G[v][i]] )
                    cout << "Coloring error : Same color " << v << "-" << G[v][i] ;

        //  Search first vertex cnv with current maximum color cn
        //  Try successive reduction of color number cn
        vertex cnv;
        for( cnv=0; cnv<vn; cnv++ )    
            if( graph_current_coloring[cnv] == cn )
                break;
        do { 
            //  Try possible reduction of cn to cn-1
            //  Backtrack vertex from cnv:
            //  - find cnv to be colored with first color bigger than its color
            do{
                cnv--;                                            
                if ( cnv == 0 ) {
                //  When backtracking reachs original vertex all possibilities exhausted:
                //  last coloring graph_coloring was ok
                    for( vertex v=0; v<vn; v++ ) 
                        fout << v << "\t" << graph_coloring[v] << endl;

                    return cn;
                }
                Vertex1Coloring( G, graph_current_coloring, cn, cnv, graph_current_coloring[cnv]+1 );
            } while( graph_current_coloring[cnv]>=cn );

            //  Try to color posterior vertices to bcnv without color cn
            //  until a vertex cnv cannot be colored with cn-1 colors
            //  new vertex to backtrack
            for( ++cnv; cnv<vn; cnv++ ){
                Vertex1Coloring( G, graph_current_coloring, cn, cnv, 1 );
                if ( graph_current_coloring[cnv]>= cn ) 
                    break;
            }
        } while( cnv<vn );
        cn--;
    } while( true );  
    
    return 0;
} 

