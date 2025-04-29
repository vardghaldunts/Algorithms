
/**
 * Tasks:
 * 
 * Look at how the class "DijkstraSP" is written.
 * 
 * Implement method "DijkstraSP::printReachableVertices()".
 *     >> check that it answers the tests correctly.
 * 
 * Add another subgraph with 3-4 vertices, not connected to 
 *         the existing graph.
 *     >> check that number of reachable vertices doesn't change.
 * 
 * Implement method "DijkstraSP::getShortestPathTo()".
 *     >> check that it passes the tests.
 * 
 * Imagine that we have no "_prev[]" array. Write alternative 
 *         "get_shortest_path_to()" method, which will do the same, 
 *         but without using "_prev[]" array.
 *     >> check that results are the same.
 * 
 * Alter the algorithm in such way, that if several shortest paths 
 *         are available, it will report:
 *     1) One of them in a random way
 *     2) [*] All of them
 *                 Hint: For that purpose, "_prev[u]" must store 
 *                 all possible previous vertices of 'u'.
 *     >> alter provided graph slightly, and make the checks.
 * 
 * Change "DijkstraSP::run()" method so it will use 'std::priority_queue<>'
 *         for faster search of temporary vertices with minimal distance.
 *         For that, push 'u' to the queue once its distance is updated, 
 *         and top of the queue will be the vertex with minimal distance.
 * 
 * Change the class "DijkstraSP" (or write a new class), which will work 
 *         on graphs, provided by WeightedAdjacencyList.
 */


#include <vector>
#include <limits>
#include <iostream>
#include <iomanip>

#include "WeightedAdjacencyMatrix.hpp"


/// This class runs Dijkstra's shortest algorithm, and remembers all 
/// the results.
struct DijkstraSP
{
	/// The graph, on which the algorithm is being run.
	WeightedAdjacencyMatrix _g;

	/// The source vertex, from which the algorithm starts.
	int _source;

	/// "_dist[v]" equals to current distance from "_source" to "v".
	std::vector< double > _dist;

	/// Flags for marking distances of all the vertices as 
	/// temporary or final.
	/// If "_is_final[u] == true", then distance of vertex "u" is final.
	std::vector< bool > _is_final;

	/// "prev[v]" equals to previous vertex in the shortest path from 
	/// "_source" to "v".
	std::vector< int > _prev;

public:
	/// Runs Dijkstra's shortest path algorithm on provided graph 'g', 
	/// from given vertex 'source'.
	void run( const WeightedAdjacencyMatrix& g, int source )
	{
		static const double INF = WEIGHTED_ADJ_MATRIX_INF;
		// Prepare
		_g = g;
		_source = source;
		const int N = _g.size();  // Number of vertices
		_dist = std::vector< double >( N, INF );
		_is_final = std::vector< bool >( N, false );
		_prev = std::vector< int >( N, -1 );
		// Start from vertex '_source'
		_dist[ _source ] = 0;
		// Continuously discover new vertices with final distance
		while ( true ) {
			// Search for temporary vertex with minimal distance
			int min_vertex;    // The temporary vertex with minimal distance
			double min_dist = INF;  // Distance of 'min_vertex'
			for ( int u = 0; u < N; ++u )
				if ( _is_final[ u ] == false && _dist[ u ] < min_dist )
					min_dist = _dist[ min_vertex = u ];
			// If not found, the algorithm is completed
			if ( min_dist == INF )
				break;
			// Otherwise, dustance of that vertex becomes final, and continuations 
			// from it are examined
			_is_final[ min_vertex ] = true;
			for ( int v = 0; v < N; ++v )
				if ( _g._m[ min_vertex ][ v ] && _is_final[ v ] == false )
					if ( _dist[min_vertex] + _g._m[min_vertex][v] < _dist[v] ) {
						_dist[v] = _dist[min_vertex] + _g._m[min_vertex][v];
						_prev[v] = min_vertex;
					}
		}
	}

	/// Prints distnaces from source to all reachable vertices.
	/// If vertex is not reachable, prints '-' there.
	void printDistances() const
	{
		const int N = _g.size();
		// Print labels
		std::cout << " |";
		for ( int v = 0; v < N; ++v )
			std::cout << std::setw(3) << (char)('A' + v);
		std::cout << " |" << std::endl;
		// Print distances
		std::cout << " |";
		for ( int v = 0; v < N; ++v )
			if ( _dist[v] == WEIGHTED_ADJ_MATRIX_INF )
				std::cout << "  -";
			else
				std::cout << std::setw(3) << _dist[v];
		std::cout << " |" << std::endl;
	}

	/// Prints on one line all vertices which are reachable from "_source".
	void printReachableVertices() const
	{
		std::cout << " {";
		//
		// Implement
		//
		std::cout << " }" << std::endl;
	}

	/// Calculates and returns shortest path from '_source' to 't'.
	std::vector< int > getShortestPathTo( int t ) const
	{
		//
		// Implement
		//
		return std::vector< int >();
	}

};


/// Prints provided path of vertices on one line.
void printPath( const std::vector< int >& path )
{
	std::cout << " [";
	for ( int u : path )
		std::cout << " " << char('A'+u);
	std::cout << " ]" << std::endl;
}


using std::cout;
using std::endl;


int main( int argc, char* argv[] )
{
	/**
	 *      u--(6)--p---(7)---q
	 *              |         |
	 *             (4)       (19)
	 *              |         |
	 *      a--(8)--b---(1)---h
	 *      |                 |
	 *     (2)               (8)
	 *      |                 |
	 *      c-(1)-e-(9)-f-(2)-k
	 *      |     |           |
	 *    (14)   (3)         (22)
	 *      |     |           |
	 *      r-(8)-s----(6)----t
	 */
	WeightedAdjacencyMatrix g;
	g.setSize( 'U' - 'A' + 1 );  // Maximal vertex is 'u'
	g.addUndirectedEdge( 'U', 'P', 6 );
	g.addUndirectedEdge( 'P', 'Q', 7 );
	g.addUndirectedEdge( 'P', 'B', 4 );
	g.addUndirectedEdge( 'Q', 'H', 19 );
	g.addUndirectedEdge( 'A', 'B', 8 );
	g.addUndirectedEdge( 'B', 'H', 1 );
	g.addUndirectedEdge( 'A', 'C', 2 );
	g.addUndirectedEdge( 'K', 'H', 8 );
	g.addUndirectedEdge( 'C', 'E', 1 );
	g.addUndirectedEdge( 'E', 'F', 9 );
	g.addUndirectedEdge( 'F', 'K', 2 );
	g.addUndirectedEdge( 'R', 'C', 14 );
	g.addUndirectedEdge( 'E', 'S', 3 );
	g.addUndirectedEdge( 'K', 'T', 22 );
	g.addUndirectedEdge( 'R', 'S', 8 );
	g.addUndirectedEdge( 'S', 'T', 6 );

	cout << "\t Running Dijkstra's SP from vertex 'A' ..." << endl;
	{
		DijkstraSP runner;
		runner.run( g, 0 );  // '0' corresponds to 'A'.
		runner.printDistances();

		std::cout << "Reachable vertices: ";
		runner.printReachableVertices();

		std::cout << "Shortest path to 'K': ";
		printPath( runner.getShortestPathTo( 'K'-'A' ) );
	}

	cout << "\t Running Dijkstra's SP from vertex 'T' ..." << endl;
	{
		DijkstraSP runner;
		runner.run( g, 'T'-'A' );
		runner.printDistances();

		std::cout << "Reachable vertices: ";
		runner.printReachableVertices();

		std::cout << "Shortest path to 'K': ";
		printPath( runner.getShortestPathTo( 'K'-'A' ) );

		std::cout << "Shortest path to 'A': ";
		printPath( runner.getShortestPathTo( 0 ) );
	}

	return 0;
}
