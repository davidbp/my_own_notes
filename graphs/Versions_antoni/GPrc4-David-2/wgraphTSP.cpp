//
//	HAMILTONIAN CYCLES
//  - Robert and Flores method
//
#include "graph.h"
//
//  Robert and Flores method for hamiltonian cycle
//
 int 
    HamiltonianCycle( const graph &G, ofstream &fout  )
{
    int n=G.size();
//  
//  hc indicates if vertex is in hamiltonian cycle in construction
//  ind indicates next adjacent vertex to be considered 
//  CV contains the vertices in hamiltonian cycle in construction
//  
    vector<bool> hc( n, false );
    vector<int> ind( n, 0 );
	vector<int> CV( n );
	int k=0, v=0;
	hc[v] = true;		
    CV[k++] = v;
	do {
	//  Find adjacent vertex G[v][i] not in 'hamiltonian cycle' in construction	
		int found = 0;
		for( int i=ind[v]; i<int(G[v].size()); i++ ) 
			if( !hc[G[v][i]] ) {
			//  Consider adjacent vertex as in 'hamiltonian cycle' and append to it
				hc[G[v][i]] = true;		
				CV[k++] = G[v][i];
			//  Actualize indicator and take adjacent vertex as v
				ind[v] = i+1;
				v = G[v][i];
				found = 1;
				break;
			}
		if( !found ) {
		//  Backtrack: remove vertex from hamiltonian cycle, take previous one as v
			ind[v] = 0;
			hc[v] = false;
			--k;
			if( k )
				v = CV[k-1];
		}		
		if( k==n ) {
		//  Test if completed hamiltonian path is hamiltonian cycle
			for( int i=0; i<int(G[v].size()); i++ )
				if( G[v][i] == 0 ) {
				//  Hamiltonian cycle found: write it
					fout << "Hamiltonian cycle " << endl;
					for( int r=0; r<int(G.size()); r++ )
						fout << CV[r] << "-";
					fout << 0 << endl;
					return 1;
				}
		//  Backtrack: remove vertex from hamiltonian cycle, take previous one as v
			ind[v] = 0;
			hc[v] = false;
			--k;
			if( k ) 
				v = CV[k-1];
			}
    } while( k );
//  Exploration completed (k=0)
	fout << "None hamiltonian cycle" << endl;
	return 0;
}
//
//  Robert and Flores method for hamiltonian cycles
//
 int 
    HamiltonianCycles( const graph &G, ofstream &fout  )
{
	int n=G.size(), hcn=0;
//  
//  hc indicates if vertex is in hamiltonian cycle in construction
//  ind indicates next adjacent vertex to be considered 
//  CV contains the vertices in hamiltonian cycle in construction
//  
    vector<bool> hc( n, false );
    vector<int> ind( n, 0 );
	vector<int> CV( n );
	int k=0, v=0;
	hc[v] = true;		
    CV[k++] = v;
	do {
	//  Find adjacent vertex G[v][i] not in 'hamiltonian cycle' in construction	
		int found = 0;
		for( int i=ind[v]; i<int(G[v].size()); i++ ) 
			if( !hc[G[v][i]] ) {
			//  Consider adjacent vertex as in 'hamiltonian cycle' and append to it
				hc[G[v][i]] = true;		
				CV[k++] = G[v][i];
			//  Actualize indicator and take adjacent vertex as v
				ind[v] = i+1;
				v = G[v][i];
				found = 1;
				break;
			}
		if( !found ) {
		//  Backtrack: remove vertex from hamiltonian cycle, take previous one as v
			ind[v] = 0;
			hc[v] = false;
			--k;
			if( k )
				v = CV[k-1];
		}		
		if( k==n ) {
		//  Test if completed hamiltonian path is hamiltonian cycle
			for( int i=0; i<int(G[v].size()); i++ )
				if( G[v][i] == 0 ) {
				//  Hamiltonian cycle found: write it
					hcn++;
					cout << "Hamiltonian cycle " << hcn << endl;
					fout << "Hamiltonian cycle " << hcn << endl;
					for( int r=0; r<int(G.size()); r++ )
						fout << CV[r] << "-";
					fout << 0 << endl;
				}
		//  Backtrack: remove vertex from hamiltonian cycle, take previous one as v
			ind[v] = 0;
			hc[v] = false;
			--k;
			if( k ) 
				v = CV[k-1];
			}
    } while( k );
//  Exploration completed (k=0)
	fout << hcn << " hamiltonian cycles found!" << endl;
	return hcn;
}

/*
 //
 void
    Dijkstra( wgraph &g )
 {
    int n = g.size();
    vector<double> d(n,numeric_limits<double>::max());
    vector<int> pred(n, -1);
    vector<bool> visit(n, false);
    priority_queue<pair<double,int> > queue;
    int start_node = 0;
	d[start_node] = 0;
	queue.push(pair<double,int>(d[start_node], start_node));
    pred[start_node] = start_node;
	while(!queue.empty()) {
		pair<double,int> cur = queue.top(); queue.pop();
		int i = cur.second;
		if (!visit[i]) {
			visit[i] = true;
			for ( unsigned int j=0; j<g[i].size(); j++) {
				int to = g[i][j].first;
				if (!visit[to] && d[i] + g[i][j].second < d[to]) {
					d[to] = d[i] + g[i][j].second;
					queue.push(pair <double,int>(-d[to], to));
                    pred[to] = i;
				}
			}
		}
	}
    cout << "Dijkstra tree: <- predecessor [distance]" << endl;
    for (int i=0; i<n; i++)     
        fprintf_s( stdout, "%d <- %d [%g]\n", i, pred[i], d[i] );
        //cout << i << " <- " << pred[i] << " [" << d[i] << "]" << endl;
    cout << endl;
    cout << "Dijkstra paths" << endl;
    for (int i=0; i<n; i++) {    
        cout << i;
        int j = i;
        while( j>0 ) {
            cout << " <- " << pred[j];
            j = pred[j];    
        }
        cout << endl;
    }
    cout << endl << endl;
 }
 */