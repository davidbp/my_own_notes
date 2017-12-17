#include "graph.h"
#include "graphe.h"
#include "wgraph.h"

 int 
	main()
{
    ofstream fout;
    vertex n, n2;
    int mhc;


//  Complete graph Kn
    fout.open( "Kn.out" );    
    for( n=2; n<10; n++ ) {
        cout << "K" << n << endl;
        fout << endl << endl << "n=" << n << endl;
	    graph Kn = graph_complete( n );
        vector<color> Knc( n );
		graph_write( Kn, fout );
	    cout << HamiltonianCycles( Kn, fout ) << " Hamitonian cycles" << endl;
        cout << MinimalVertexColoring( Kn, Knc, fout ) << " colors needed" << endl;
    }
    fout.close();
//  Bipartite complete graph Kn1n2
    fout.open( "Kn1n2.out" );    
    cout << endl << "Kn1n2" << endl;
    for( n=2; n<10; n++ ) {
        for( n2=1; n2<n/2; n2++ )
        cout << "K" << n-n2 <<  "," << n2 << endl;
        fout << endl << endl << "n1=" << n-n2 <<  ", n2=" << n2 << endl;
        graph Kn1n2 = graph_bipartite_complete( n-n2, n2 );
        vector<color> Kn1n2c( n );
		graph_write( Kn1n2, fout );
	    cout << HamiltonianCycles( Kn1n2, fout ) << " Hamitonian cycles" << endl;
        cout << MinimalVertexColoring( Kn1n2, Kn1n2c, fout )<< " colors needed" << endl ;
    }
    fout.close();
//  Cycle graph Cn
    fout.open( "Cn.out" );    
    cout << endl << "Cn" << endl;
    for( n=2; n<10; n++ ) {
        cout << "C" << n << endl;
        fout << endl << endl << "n=" << n << endl;
	    graph Cn = graph_cycle( n );
        vector<color> Cnc( n );
		graph_write( Cn, fout );
	    cout << HamiltonianCycles( Cn, fout ) << " Hamitonian cycles" << endl;
        cout << MinimalVertexColoring( Cn, Cnc, fout )<< " colors needed" << endl ;
    }
    fout.close();


	ifstream fin;
	//  Horse graph Hn1n2
	fout.open("Hn1n2.out");
	cout << endl << "Hn1n2" << endl;
	fin.open("Horse.txt");
	index c, n1;
	fin >> c;
	for (index k = 0; k<c; k++) {
		fin >> n1 >> n2;
		cout << "Kt" << n1 << "," << n2 << endl;
		fout << endl << endl << "n1=" << n1 << ", n2=" << n2 << endl;
		graph Hn1n2 = graph_horse(n1, n2);
		vector<color> Hn1n2c(n1*n2);
		graph_write(Hn1n2, fout);
		cout << HamiltonianCycles(Hn1n2, n2, fout) << " Hamitonian cycles" << endl;
		//cout << MinimalVertexColoring( Hn1n2, Hn1n2c, fout )<< " colors needed" << endl ;
	}
	fin.close();
	fout.close();



/*
//  Horse graph Hn1n2
    fout.open( "Hn1n2.out" );    
    cout << endl << "Hn1n2" << endl;
    for( n=11; n<12; n++ ) {
		for( n2=5; n2<=n/2; n2++ ) {
			cout << "n1=" << n-n2 <<  ", n2=" << n2 << endl;
			fout << endl << endl << "n1=" << n-n2 <<  ", n2=" << n2 << endl;
			graph Hn1n2 = graph_horse( n-n2, n2 );
			vector<color> Hn1n2c( (n-n2)*n2 );
			graph_write( Hn1n2, fout );
			cout << HamiltonianCycles( Hn1n2, n2, fout )  << " Hamitonian cycles" << endl;
			cout << MinimalVertexColoring( Hn1n2, Hn1n2c, fout )<< " colors needed" << endl ;
		}
    }
    fout.close();

*/

//  Dodecahedron
	cout << "Dodecahedron" << endl;
	fout.open("D.out");
	graph D = graph_read("D.in");
	vector<color> Dc(D.size());
	graph_write(D, fout);
	cout << HamiltonianCycles(D, fout) << " Hamiltonian cycles" << endl;
	cout << MinimalVertexColoring(D, Dc, fout) << " colors needed" << endl;
	fout.close();


//  Weighted complete graph WKn
    fout.open( "WKn.out" );    
    cout << endl << "WKn" << endl;
    for( n=2; n<10; n++ ) {
        cout << "WK" << n << endl;
        fout << endl << endl << "n=" << n << endl;
	    wgraph WKn = wgraph_complete( n, 10 );
        wgraph_write( WKn, fout );
	    mhc = TravellingSalesmanProblem( WKn, fout );
        fout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
        cout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
    
    }
    fout.close();

//  Weighted cycle graph WCn
    fout.open( "WCn.out" );    
    cout << endl << "WCn" << endl;
    for( n=2; n<10; n++ ) {
        cout << "WC" << n << endl;
        fout << endl << endl << "n=" << n << endl;
	    wgraph WCn = wgraph_complete( n, 10 );
        wgraph_write( WCn, fout );
	    mhc = TravellingSalesmanProblem( WCn, fout );
        fout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
        cout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
    
    }
    fout.close();
//  Bipartite complete graph Kn1n2
    fout.open( "WKn1n2.out" );    
    cout << endl << "WKn1n2" << endl;
    for( n=2; n<10; n++ ) {
        for( n2=1; n2<n/2; n2++ ) {
            cout << "K" << n-n2 <<  "," << n2 << endl;
            fout << endl << endl << "n1=" << n-n2 <<  ", n2=" << n2 << endl;
            wgraph WKn1n2 = wgraph_bipartite_complete( n-n2, n2, 10 );
            wgraph_write( WKn1n2, fout );
	        mhc = TravellingSalesmanProblem( WKn1n2, fout );
            fout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
            cout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
        }
    }
    fout.close();
//  Cities graph WGc
	wgraph WGc = wgraph_read( "ciutats.in" );
    fout.open( "ciutats.out" );    
	wgraph_write( WGc, fout );
	mhc = TravellingSalesmanProblem( WGc, fout );
    fout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
    cout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
    fout.close();

//  Dodecahedron graph WD
	wgraph WD = wgraph_read( "WD.in" );
    fout.open( "WD.out" );    
	wgraph_write( WD, fout );
	mhc = TravellingSalesmanProblem( WD, fout );
    fout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
    cout << "Hamiltonian cycle " << mhc << " is solution of TSP" << endl;
    fout.close();
//  Províncies
	cout << "Províncies" << endl;
    graph Provincies = graph_read( "provincies.in" );
    fout.open( "provincies.out" );   
	vector<color> Provinciesc( Provincies.size( ));
	graph_write( Provincies, fout );
	cout << MinimalVertexColoring( Provincies, Provinciesc, fout ) << " colors needed" << endl;
    fout.close();
//  Comarques de Catalunya
	cout << "Comarques" << endl;
    graph Comarques = graph_read( "comarques.in" );
    fout.open( "comarques.out" );   
	vector<color> Comarquesc( Comarques.size( ));
	graph_write( Comarques, fout );
	cout << MinimalVertexColoring( Comarques, Comarquesc, fout ) << " colors needed" << endl;
    fout.close();


//  Complete graph Kn
	graph Kn;
	edges KnE;
	fout.open( "KnE.out" );    
	for( vertex n=4; n<16; n+=2 ) {
		graphe_complete( Kn, KnE, n );
		cout << endl << "K" << n << endl;
		graphe_write( Kn, KnE, fout );
		cout << MinimalEdgeColoring( Kn, KnE, fout ) << " colors needed" << endl;
    }
    fout.close();


//  Bipartite complete graph Kn1n2
	graph Kn1n2;
	edges Kn1n2E;
	fout.open( "Kn1n2E.out" );    
	for( vertex n=4; n<10; n+=2 ) {
		for( n2=1; n2<=n/2; n2++ ) {
			graphe_bipartite_complete( Kn1n2, Kn1n2E, n-n2, n2 );
			cout << endl << "K" << n-n2 << "," << n2 << endl;
			graphe_write( Kn1n2, Kn1n2E, fout );
			cout << MinimalEdgeColoring( Kn1n2, Kn1n2E, fout ) << " colors needed" << endl;
		}
    }
    fout.close();

//  Cycle graph Cn
	graph Cn;
	edges CnE;
	fout.open( "CnE.out" );    
	for( vertex n=4; n<10; n+=1 ) {
		graphe_cycle( Cn, CnE, n );
		cout << endl << "C" << n << endl;
		graphe_write( Cn, CnE, fout );
		cout << MinimalEdgeColoring( Cn, CnE, fout ) << " colors needed" << endl;
    }
    fout.close();


//  Star graph Sn
	graph Sn;
	edges SnE;
	fout.open( "SnE.out" );    
	for( vertex n=4; n<10; n+=1 ) {
		graphe_star( Sn, SnE, n );
		cout << endl << "S" << n << endl;
		graphe_write( Sn, SnE, fout );
		cout << MinimalEdgeColoring( Sn, SnE, fout ) << " colors needed" << endl;
    }
    fout.close();


//  Wheel graph Wn
	graph Wn;
	edges WnE;
	fout.open( "WnE.out" );    
	for( vertex n=4; n<10; n+=1 ) {
		graphe_wheel( Wn, WnE, n );
		cout << endl << "W" << n << endl;
		graphe_write( Wn, WnE, fout );
		cout << MinimalEdgeColoring( Wn, WnE, fout ) << " colors needed" << endl;
    }
    fout.close();


//  Read graph GP
	graph GP;
	edges GPE;
	vector<color> GPc;
	graphe_read( GP, GPE, "Provincies.in" );
	cout << endl << "Províncies" << endl;
	fout.open( "Provincies.out" );    
	graphe_write( GP, GPE, fout );
    MinimalVertexColoring( GP, GPc, fout );
	fout.close();



//  Read graph GC
	graph GC;
	vector<color> GCc;
	map<vip,edge> GCm;
	graphe_read( GC, GCm, "Comarques.in" );
	cout << endl << "Comarques" << endl;
	fout.open( "Comarques.out" );    
	graphe_write( GC, GCm, fout );
    MinimalVertexColoring( GC, GCc, fout );
	fout.close();



	
//  Read graph G0
	graph G0;
	vector<color> G0c;
	map<vip,edge> G0E;
	graphe_read( G0, G0E, "graph0.in" );
	cout << endl << "G0" << endl;
	fout.open( "graph0.out" );    
	graphe_write( G0, G0E, fout );
	Hierholzer( G0, G0E, fout );
    fout.close();
    
    graph EG1;
	edges EG1E;
	graphe_read( EG1, EG1E, "Euler1.in" );
	cout << endl << "EG1" << endl;
	fout.open( "Euler1.out" );   
	graphe_write( EG1, EG1E, fout );
	Hierholzer( EG1, EG1E, fout );
    fout.close();

    graph EG2;
	edges EG2E;
	graphe_read( EG2, EG2E, "Euler2.in" );
	cout << endl << "EG2" << endl;
	fout.open( "Euler2.out" );    
	graphe_write( EG2, EG2E, fout );
	Hierholzer( EG2, EG2E, fout );
    fout.close();

    graph EG3;
	edges EG3E;
	graphe_read( EG3, EG3E, "Euler3.in" );
	cout << endl << "EG3" << endl;
	fout.open( "Euler3.out" );    
	graphe_write( EG3, EG3E, fout );
	Hierholzer( EG3, EG3E, fout );
    fout.close();

    graph EG4;
	edges EG4E;
	graphe_read( EG4, EG4E, "Euler4.in" );
	cout << endl << "EG4" << endl;
	fout.open( "Euler4.out" );    
	graphe_write( EG4, EG4E, fout );
	Hierholzer( EG4, EG4E, fout );
    fout.close();

	
    cout << "Press Enter to exit... ";
    cin.get();

}
