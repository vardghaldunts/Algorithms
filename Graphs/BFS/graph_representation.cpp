/**
 * Tasks:
   Implement "inversed()" global function.
 *    >> check that it passes the tests.
 * 
 * Implement global function "convertToMatrix()".
 *    >> check that it passes the tests.
 * 
 * Implement global function "convertToList()".
 *    >> check that it passes the tests.
 * 
 * 
 * 
 * Change one of classes "AdjacencyMatrix" or "AdjacencyList" to
 *         hold weighted graphs.
 */


#include <vector>
#include <list>
#include <iostream>
#include <algorithm>


/// This class represents a simple adjacency matrix of a unweighted graph.
struct AdjacencyMatrix
{
	typedef std::vector< std::vector< bool > > matrix_type;

	/// The adjacency matrix.
	/// There is an edge "(u,v)" only if "_m[u][v]==true".
	matrix_type _m;

	/// Number of vertices in this graph.
	int size() const
		{ return (int)_m.size(); }

	/// Check if edge "(u,v)" is present.
	bool hasEdge( int u, int v ) const
		{ return _m[u][v]; }

	/// Checks if the graph represented by this adjacency matrix is 
	/// directed.
	bool isDirected() const {
		const int N = size();  // Number of vertices
		for ( int u = 0; u < N; ++u )
			for ( int v = u+1; v < N; ++v )
				if ( _m[u][v] ^ _m[v][u] )
					return true;  // Only one of edges (u,v) and (v,u) is present
		return false;
	}

	/// Prints degrees (number of adjacent vertices) of all vertices of 
	/// this graph.
	void printDegrees() const {
		const int N = size();

		for (int u = 0; u < N; u++) {
			int degree = 0;
			for (int v = 0; v < N; v++) {
				if (_m[u][v]) {
					degree++;
					std::cout << degree << std::endl;
				}
			}
		}
	}
	/// Checks if provided 'path' of vertices exists in this graph.
	bool existsPath( const std::vector< int >& path ) const {
		for(int i = 0 ; i < path.size()-1 ; i++ ){
			int u = path[i] ;
			int v = path[i+1] ;
			if(!_m[u][v])
				return false;

		}
		return true ;
	}
};


/// This class represents given unweighted graph as adjacency list.
struct AdjacencyList
{
	typedef std::list< int > list_type;  // How 1 list is represented

	typedef std::vector< list_type > lists_type;

	/// Adjacency list of the entire graph.
	lists_type _adj;

	/// Returns number of vertices in this graph.
	int size() const
		{ return (int)_adj.size(); }

	/// Checks if the graph has edge "(u,v)".
	bool hasEdge( int u, int v ) const
		{ return std::count( _adj[u].cbegin(), _adj[u].cend(), v ) == 1; }

	/// Checks if this graph is directed.
	bool isDirected() const {
		const int N = size();  // Number of vertices
		for ( int i = 0; i < N; ++i ) {
			for ( int j : _adj[ i ] ) {
				if ( ! hasEdge( j, i ) )
					return false;
			}
		}
		return true;
	}

	/// Checks if the 'path' exists in this graph.
	bool existsPath( const std::vector< int >& path ) const {
		for(int i = 0 ; i < path.size()-1 ; i++ ){
			int u = path[i] ;
			int v = path[i+1] ;
			if(!hasEdge(u,v))
				return false;

		}
		return true ;
	}
};


/// Returns adjacency list of inversed graph of 'L'.
/// In the inversed graph, every edge has opposite direction.
AdjacencyList inversed( const AdjacencyList& L )
{
	AdjacencyList result;
	const int N =L.size();
	for (int u = 0; u < N; u++) {
		for (int v : L._adj[u]) {
			result._adj[u].push_back(v);
		}
	}
	return result;
}


/// Converts representation of graph from adjacency list 'L' to
/// adjacency matrix.
AdjacencyMatrix convertToMatrix( const AdjacencyList& L )
{
	const int N = L.size();
	AdjacencyMatrix result;
	for (int u = 0; u < N; u++) {
		for (int v : L._adj[u]) {
			result._m[u][v] = true;
		}
	}
	return result;
}


/// Converts representation of graph from adjacency matrix 'M' to
/// adjacency list.
AdjacencyList convertToList( const AdjacencyMatrix& M )
{
	const int N = M.size();
	AdjacencyList result;
	for (int u = 0; u < N; u++) {
		for (int v = 0; v < N; v++) {
			if (M._m[u][v]) {
				result._adj[u].push_back(v);
			}
		}
	}
	return result;
}

struct AdjacencyListWeighted {
	std::vector< std::list< std::pair<int,int > >> _adj;

	int size() const {
		return (int)_adj.size();
	}
	bool hasEdge( int u, int v ) const {
		for (const std::pair<int,int >& adj : _adj[u]) {
			if ( adj.first == v )
				return true;
		}
		return false;
	}

	bool existsPath( const std::vector< int >& path ) const {
		for(int i = 0 ; i < path.size()-1 ; i++ ) {
			bool fount = false;
			for (const std::pair<int,int >& adj : _adj[ path[i] ] ) {
				if ( adj.first == path[i+1] ) {
					fount = true;
					break;
				}
			}
			if ( !fount )
				return false;
		}
		return true;
	}

	bool isDirected() const {
		const int N = size();
		for (int u = 0; u < N; u++) {
			for ( const std::pair<int,int>& adj : _adj[ u ] ) {
				int v = adj.first;
				bool fount = false;
				for ( const std::pair<int,int >& adj2 : _adj[ v ] ) {
					if ( adj2.first == u ) {
						fount = true;
						break;
					}
				}
				if ( !fount )
					return false;
			}
		}
		return true;
	}
};
int main( int argc, char* argv[] )
{
	using std::cout;
	using std::endl;

	{
		// An undirected graph 'g1' (star like)
		cout << "Undirected star-like graph 'g1' : " << endl;
		AdjacencyMatrix g1;
		const int N = 4;
		g1._m.resize( N, std::vector< bool >( N, false ) );
		g1._m[0][1] = g1._m[1][0] = true;
		g1._m[2][1] = g1._m[1][2] = true;
		g1._m[3][1] = g1._m[1][3] = true;

		cout << "Is directed : " << g1.isDirected() << endl;

		cout << "Degrees : ";
		g1.printDegrees();

		cout << "Has path [0, 1, 3] : " << g1.existsPath( {0, 1, 3} ) << endl;
		cout << "Has path [2, 0, 1] : " << g1.existsPath( {2, 0, 1} ) << endl;
	}

	{
		// A directed graph 'g2' (path like)
		cout << "Directed path-like graph 'g2' : " << endl;
		AdjacencyList g2;
		const int N = 6;
		g2._adj.resize( N );
		g2._adj[0] = { 1 };
		g2._adj[1] = { 2, 3 };
		g2._adj[2] = { 4 };
		g2._adj[3] = { 5 };
		g2._adj[4] = {};
		g2._adj[5] = {};

		cout << "Is directed : " << g2.isDirected() << endl;

		cout << "Has path [0, 1, 2, 4] : " << g2.existsPath( {0, 1, 2, 4} ) << endl;
		cout << "Has path [0, 1, 3, 4] : " << g2.existsPath( {0, 1, 3, 4} ) << endl;
	}

	return 0;
}
