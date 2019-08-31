/*
If you want to compile from the terinal:
c++ -std=c++14 graphm.cpp -o graphm.out
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
 
using namespace std;
// 
//  Complete graph to adjacency matrix
//
vector<vector<int>> graphM_complete( int n )
{
    //  Initialize adjacency matrix	to 1
    vector<vector<int>> KnM( n, vector<int>( n, 1 ) );
    //  Fill diagonal with 0
    for( int i=0; i<n; i++ ) 
         KnM[i][i] = 0;
    return KnM;
}

// 
//  Read SIMPLE graph from file fname of edges to adjacency matrix
//
vector<vector<int>> graphM_read( string fname )
 {    
	ifstream fin;
    fin.open( fname.c_str() );    
    if( fin.fail() ) {
        cerr << "unable to open file " << fname.c_str() << " for reading" << endl;
        exit( 1 );
    }
     // Read vertices and edges numbers
	int n, m;
	fin >> n >> m;
     // Initialize adjacency matrix	to 0
    vector<vector<int>> M( n, vector<int> (n, 0) );
     // Fill adjacency matrix
    for( int j=0; j<m; j++ ) {
         int u, v;
         fin >> u >> v;
         M[u][v] = M[v][u] = 1;
    }    
    return M;
}

// 
//  Write SIMPLE graph from adjacency matrix to file stream
//  - vertices and edges numbers
//  - adjacency matrix
//  - edges
//  - sorted degrees
//  IMPORTANT: This function has a bug that must be corrected
  void 
	graphM_write( vector<vector<int>>& M, ofstream& fout )
 {    
    //  Vertices number 
	int n = M.size();
    //  Count edges number from adajacency matrix
    int m = 0; 
    for( int i = 0; i < n; i++ ) 
        for( int k = 0; k <= i; k++ ) 
            m = m + M[i][k];
    //  Write vertices and edges numbers
    fout << "\nGraph with " << n << " vertices and " << m << " edges " << endl;
    //  Write adjacency matrix
    fout << "\nAdjacency matrix" << endl;
    for( int i=0; i<n; i++ )  {
        for( int k=0; k<n; k++ ) 
            fout << "\t" << M[i][k];
        fout << endl;
    }
    //  Write edges         
	fout << "\nEdges" << endl;
    for( int i = 0; i < n; i++ ) 
        for( int k = i+1; k < n; k++ ) 
             fout << i << " " << k << endl;
             
    //  Count degrees
    vector<int> deg( n );
    for( int i = 0; i < n; i++ ) {
         deg[i] = 0;
         for (int k = 0; k < n; k++) 
             deg[i] += M[i][k];
    }
    //  Write sorted degrees sequence
    fout << "\nDegrees sequence" << endl;
    for( int i = 0; i < n; i++ ) {
        fout << deg[i] << " ";
    }
    fout << endl;
    //  Sort degrees sequence
    sort( deg.begin(), deg.end() );
    //  Write sorted degrees sequence
    fout << "\nSorted degrees sequence" << endl;
    for( int i = 0; i < n; i++ ) 
        fout << deg[i] << " ";
    fout << endl;
}


//
//	Main program:
//  - read graph in file graph0.in and construct graph K7
//  - write to graph0.out and K7.out
 int 
	main()
{
    ofstream fout;

    //  graph0.in
    vector<vector<int>> M0 = graphM_read( "./input_data/graph0.in" );
    fout.open( "./results/graph0.out" );   
    graphM_write( M0, fout );
	fout.close();

    //  K
    vector<vector<int>> MK6 = graphM_complete( 6 );
    fout.open( "./results/K6.out" );   
    graphM_write( MK6, fout );
    fout.close();

    //  Finish
	cout << endl << "Press enter to finish... ";
    cin.get();
}
