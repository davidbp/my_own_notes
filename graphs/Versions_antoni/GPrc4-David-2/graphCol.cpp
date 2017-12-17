//
//	VERTEX COLORING
//  - by Brélaz method
//  - by backtracking method

#include "graphe.h"
//
//  Vertex-coloring of one vertex
//
 color
	Vertex1Coloring(   graph& G, vector<color>& Gc, color cn, vertex v, color oc  )
{
	vertex n = G.size();
	vector<bool> avc( cn+1, false  );
	for( index i=0; i<G[v].size(); i++ )  
		if ( G[v][i] < v )
		    avc[Gc[G[v][i]]] = true;
//  First color from oc not in previous adjacent vertex
	color c;
    for( c=oc; c<=cn; c++ )
		if ( !avc[c] ) {
			Gc[v] = c;
		    break;
		}
//  Color vertex with new color
	if ( c==cn+1 ) {
        Gc[v] = ++cn;
	}
	return cn;
}

 color
    BrelazColoring(   graph& G, vector<color>& Gc )
{
    color cn;
	vertex n = G.size();
//  Color vertex 0 with color 1
	Gc[0] = cn = 1;
//  Brélaz coloring: color other vertices with colors from 1
	for( vertex v=1; v<n; v++ )
		cn = Vertex1Coloring( G, Gc, cn, v, 1 );
    return cn;
}

//
//  Vertex Coloring of Graph
//
 color
    MinimalVertexColoring(   graph& G, vector<color>& Gc, ofstream& fout )
{
	vertex vn = G.size();
//  Prepare initial Brelaz coloring 
	Gc = vector<color>(vn, 0);
	vector<color> Gpc(vn,0);
	color cn = BrelazColoring( G, Gpc );
		
	do { 
	//  Provisionally accept and write current coloring, saved in Gc
	//  Save it as proving coloring Gpc 
    //  Try successive reduction of color number cn
	    fout  << "Coloració de vèrtexs amb " << cn << " colors\n";
        fout  << "\nColoració amb " << cn << " colors\n";
		cout  << "Coloration with " << cn << " colors\n";
        for( vertex v=0; v<vn; v++ ) {
			Gc[v] = Gpc[v];
            fout << v << "\t" << Gc[v] << endl;
        }
		for( vertex v=0; v<vn; v++ )
			for( index i=0; i<G[v].size(); i++ )
				if( v<G[v][i] && Gc[v]==Gc[G[v][i]] )
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
				//  last coloring Gc was ok
                    fout  << "\nMinimal vertex coloring found\n";
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
} 

 //
//  Edge coloring by vertex coloring line graph
//
 color
    MinimalEdgeColoring(   graph& G, edges& GE, ofstream& fout )
{
	graph LG;
	vector<color> LGc;
	edges LGE;
    line_graphe( G, GE, LG, LGE );
	graphe_write( LG, LGE, fout );
	fout << "Edge coloring\n";
	cout << "Edge coloring\n";
    color ecn = MinimalVertexColoring( LG, LGc, fout );
    vertex n=G.size();
    for( vertex v=0; v<n; v++ )
        for( index i=0; i<G[v].size(); i++ )
            if( v<G[v][i] )
                fout << v << "\t" << G[v][i] << "\t"  << GE[vip(v,i)] <<  "\t"  << LGc[GE[vip(v,i)]] << endl;	
	for( color c=1; c<=ecn; c++ ) {
		fout << "Color " << c << endl;
		for( vertex v=0; v<n; v++ )
			for( index i=0; i<G[v].size(); i++ )
				if( v<G[v][i] && LGc[GE[vip(v,i)]]==c )
					fout << v << "\t" << G[v][i] << "\t"  << GE[vip(v,i)] <<  "\t"  << LGc[GE[vip(v,i)]] << endl;	
	}
	return ecn;
 }

 