/**
 * Tasks:
 *
 * Implement another BfsRunner class, which will work on adjacency matrix.
 * 
 */


#include <vector>
#include <queue>
#include <iostream>

#include "AdjacencyList.hpp"
#include "AdjacencyMatrix.hpp"


/// This class runs BFS algorithm on provided graph.
struct BfsRunner
{
	/// Representation of the graph.
	AdjacencyList _g;

	/// Start vertex, from which BFS is invoked.
	int _source;

	/// Colors used for labeling the vertices.
	enum Color {
		WHITE = 0,
		GRAY = 1,
		BLACK = 2
	};

	/// Colors of all the vertices.
	std::vector< Color > _colors;
	std::vector<int> _labels;
	std::vector<int> _parents;

	/// Runs BFS on provided graph 'g_', starting from the vertex 'source_'.
	void run( const AdjacencyList& g_, int source_ ) {
		_g = g_;  // Remember the arguments
		_source = source_;
		const int N = _g.size();  // Number of vertices
		_colors = std::vector< Color >( N, WHITE );  // All vertices start from white
		std::queue< int > q;  // Queue of discovered vertices
		q.push( _source );
		_colors[ _source ] = GRAY;
		while ( ! q.empty() ) {
			std::queue< int > qNext;  // The next discovered vertices
			// Process all the discovered (but not yet processed) vertices of 'q'
			while ( ! q.empty() ) {
				int u = q.front();  // 'u' is discovered but not processed yet
				q.pop();
				_colors[ u ] = BLACK;
				for ( int v : _g._adj[ u ] )
					if ( _colors[ v ] == WHITE ) {  // New vertex 'v' is discovered
						qNext.push( v );
						_colors[ v ] = GRAY;
					}
			}
			q.swap( qNext );  // Remember content of 'qNext' in 'q'
		}
	}

	void run_1q( const AdjacencyList& g_ , int source_ ) {
		_g = g_;
		_source = source_;
		const int N = _g.size();
		_colors = std::vector< Color >( N, WHITE );
		_labels = std::vector< int >( N, -1 );
		std::queue< int > q;
		q.push( _source );
		_colors[ _source ] = GRAY;
		_labels[ _source ] = 0;
		while ( ! q.empty() ) {
			int Size = q.size();
			while ( Size -- ) {
				int u = q.front();
				q.pop();
				for ( int v : _g._adj[ u ] ) {
					if ( _colors[ v ] == WHITE ) {
						q.push( v );
						_colors[ v ] = GRAY;
						_labels[ v ] = _labels[ u ] + 1;
					}
				}
				_colors[ u ] = BLACK;
			}
		}

	}
	/// Prints colors of all vertices of provided graph, in 2 rows.
	void printColors() const {
		const int N = _g.size();
		std::cout << " |";
		for ( char ch = 'A'; ch < 'A' + N; ++ch )
			std::cout << ' ' << ch;
		std::cout << " |" << std::endl;
		std::cout << " |";
		for ( int i = 0; i < N; ++i )
			std::cout << ' ' << (int)_colors[ i ];
		std::cout << " |" << std::endl;
	}

	/// Returns number of vertices, which are reachable from '_source'.
	int getNumberOfReachableVertices() const {
		int count = 0;
		for (Color c : _colors)
			if (c != BLACK) ++count;
		return count;
	}

	/// Prints labels of all the vertices.
	/// Label of 'v' shows at which iteration of BFS the vertex 'v' was
	///   discovered.
	void printLabels() const {
		const int N = _g.size();
		std::cout << " |";
		for (char ch = 'A'; ch < 'A' + N; ++ch)
			std::cout << ' ' << ch;
		std::cout << " |" << std::endl;
		std::cout << " |";
		for (int i = 0; i < N; ++i)
			std::cout << ' ' << _labels[i];
		std::cout << " |" << std::endl;
	}

	/// Returns shortedt path from '_source' to 'target'.
	std::vector< int > calculatePathTo( int target ) const {
		if (_colors[target] == WHITE)return {};
		std::vector< int > path;
		for (int v = target ; v != -1; v = _parents[ v ] ) {
			path.push_back( v );
		}
		std::reverse( path.begin(), path.end() );
		return path;
	}
};


/// Adds edge (u,v) to unweighted graph 'g', where both 'u' and 'v' 
/// are uppercase letters.
void addUnweightedEdge( AdjacencyList& g, char u, char v )
{
	g.addEdge( u, v );
	g.addEdge( v, u );
}


/// Prints provided path of a graph, in one line.
void printPath( const std::vector< int >& path )
{
	std::cout << "[";
	for ( int i : path )
		std::cout << ' ' << ('A'+i);
	std::cout << " ]" << std::endl;
}



using std::cout;
using std::endl;

struct BfsRunnerMatrix
{
	AdjacencyList _g;
	int _source;
	enum Color {
		WHITE = 0,
		GRAY = 1,
		BLACK = 2
	};
	std::vector< Color > _colors;
	std::vector<int> _labels;

	void run( const AdjacencyList& g_, int source_ ) {
		_g = g_;
		_source = source_;
		const int N = _g.size();
		_colors = std::vector< Color >( N, WHITE );
		_labels = std::vector< int >( N, -1 );
		std::queue< int > q;
		q.push( _source );
		_colors[ _source ] = GRAY;
		_labels[ _source ] = 0;
		while ( ! q.empty() ) {
			int u = q.front();
			q.pop();
			for ( int v = 0 ; v < N;++v) {
				if ( _g.hasEdge(u,v) && _colors[ v ] == WHITE ) {
					q.push( v );
					_colors[ v ] = GRAY;
					_labels[ v ] = _labels[ u ] + 1;
				}
			}
			_colors[ u ] = BLACK;

		}
	}

	int getNumberOfReachableVertices() const {
		int count = 0;
		for (Color c : _colors)
			if (c != BLACK) ++count;
		return count;
	}

	void printLabels() const {
		std::cout << " |";
		for (char ch = 'A'; ch < 'A' + _g.size(); ++ch)
			std::cout << ' ' << ch;
		std::cout << " |\n |";
		for (int lbl : _labels) {
			if (lbl == -1)
				std::cout << " -";
			else
				std::cout << ' ' << lbl;
		}
		std::cout << " |\n";
	}


};
int main()
{
	/*
	 *      A
	 *      |
	 *   C--B-----E    O--M--P
	 *   |  |     |       |  |
	 *   D  G-L---J--K    N  Q
	 *   |  |     |
	 *   H--F     I
	 */
	AdjacencyList g;
	g._adj.resize( 12 + 5 );
	addUnweightedEdge( g, 'A', 'B' );
	addUnweightedEdge( g, 'C', 'B' );
	addUnweightedEdge( g, 'B', 'E' );
	addUnweightedEdge( g, 'C', 'D' );
	addUnweightedEdge( g, 'B', 'G' );
	addUnweightedEdge( g, 'E', 'J' );
	addUnweightedEdge( g, 'G', 'L' );
	addUnweightedEdge( g, 'L', 'J' );
	addUnweightedEdge( g, 'K', 'J' );
	addUnweightedEdge( g, 'D', 'H' );
	addUnweightedEdge( g, 'G', 'F' );
	addUnweightedEdge( g, 'I', 'J' );
	addUnweightedEdge( g, 'H', 'F' );
	//
	addUnweightedEdge( g, 'O', 'M' );
	addUnweightedEdge( g, 'M', 'P' );
	addUnweightedEdge( g, 'M', 'N' );
	addUnweightedEdge( g, 'Q', 'P' );

	cout << "\t Running BFS from vertex 'A' ..." << endl;
	{
		BfsRunner runner;
		runner.run( g, 0 );    // Corresponds to 'A'
		runner.printColors();

		cout << "Number of reachable vertices : "
				<< runner.getNumberOfReachableVertices() << endl;

		cout << "Labels of vertices : " << endl;
		runner.printLabels();

		cout << "Path to 'I' : ";
		printPath( runner.calculatePathTo( 'I'-'A' ) );
		cout << "Path to 'H' : ";
		printPath( runner.calculatePathTo( 'H'-'A' ) );
	}

	cout << "\t Running BFS from vertex 'M' ..." << endl;
	{
		BfsRunner runner;
		runner.run( g, 'M'-'A' );    // Corresponds to 'M'
		runner.printColors();

		cout << "Number of reachable vertices : "
				<< runner.getNumberOfReachableVertices() << endl;

		cout << "Labels of vertices : " << endl;
		runner.printLabels();

		cout << "Path to 'Q' : ";
		printPath( runner.calculatePathTo( 'Q'-'A' ) );
	}

	return 0;
}
