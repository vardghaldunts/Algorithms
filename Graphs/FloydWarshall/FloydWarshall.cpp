/**
 * Tasks:
 *
 * Look at how the function 'discardVertex()' is implemented for         v
 *         WeightedAdjacencyMatrix graph representation.
 *     >> check that it discards properly.
 *
 * Finish implementation of 'floydWarshallShortestPaths()' function      v
 *         for WeightedAdjacencyMatrix graph representation.
 *     >> check that it works properly.
 *
 * Print desnsity percent of the adjacency matrix, each time after       v
 *         discarding a new vertex. Check that the percents tends
 *         to "100%", in case of a connected graph.
 *
 * Implement 'discardVertex()' function for graphs represented by        v
 *         adjacency list.
 *     >> check that it discards properly.
 *
 * Implement 'floydWarshallShortestPaths()' function for graphs          v
 *         represented by adjacency list.
 *     >> check that it works properly.
 *
 * Implement function 'floydWarshallShortestPathsWithGlues()'.           v
 *     >> check that glues matrix is filled properly.
 *
 * Look at how the function 'printPathExclusive()' is implemented.       v
 *     >> call 'printPathInclusive()' to check that glues matrix is
 *        filled properly.
 *
 * Implement 'printPathExclusive()' in an iterative way.                 v
 *     >> call it instead, and make sure that results are the same.
 */


#include "WeightedAdjacencyMatrix.hpp"
#include "WeightedAdjacencyList.hpp"


/// Alters provided graph 'g', so the vertex 'k' can no longer be 
/// on any shortest path between some other vertices 's' and 't'.
void discardVertex( WeightedAdjacencyMatrix& g, int k )
{
	const int N = g.size();  // Number of vertices
	for ( int i = 0; i < N; ++i )  // Consider all incoming edges
		if ( g.hasEdge( i, k ) )
			for ( int j = 0; j < N; ++j )  // And all outgoing edges
				if ( g.hasEdge( k, j ) )
					if ( g._m[i][k] + g._m[k][j] < g._m[i][j] )
						g._m[i][j] = g._m[i][k] + g._m[k][j];  // Discard
}


/// Runs Floyd-Warshall all-pair shortest paths algorithm on the 
/// provided graph 'g'.
void floydWarshallShortestPaths( WeightedAdjacencyMatrix& g )
{
	const int N = g.size();  // Number of vertices
	// Prepare selft-edges
	for ( int i = 0; i < N; ++i )
		g._m[i][i] = 0;  // No cost to travel 'i'-->'i'
	// Discard all the edges
	for ( int k = 0 ; k < N ; ++k) {
		discardVertex( g, k );
	}
}

/// Alters provided graph 'g', so the vertex 'k' can no longer be
/// on any shortest path between some other vertices 's' and 't'.
void discardVertex( WeightedAdjacencyList& g, int k )
{
	const int N = g.size();
	for (int i = 0; i < N; ++i) {
		if (!g.hasEdge(i, k)) continue;

		int w_ik = -1;
		for (const auto& e : g._adj[i]) {
			if (e.first == k) {
				w_ik = e.second;
				break;
			}
		}

		for (int j = 0; j < N; ++j) {
			if (!g.hasEdge(k, j)) continue;

			int w_kj = -1;
			for (const auto& e : g._adj[k]) {
				if (e.first == j) {
					w_kj = e.second;
					break;
				}
			}

			int total = w_ik + w_kj;
			bool has_ij = false;
			int w_ij = -1;
			for (const auto& e : g._adj[i]) {
				if (e.first == j) {
					has_ij = true;
					w_ij = e.second;
					break;
				}
			}

			if (!has_ij || total < w_ij)
				g.addEdge(i, j, total);
		}
	}
}



/// Runs Floyd-Warshall all-pair shortedt paths algorithm on 
/// provided graph 'g', represented as adjacency list.
void floydWarshallShortestPaths(WeightedAdjacencyList& g)
{
	const int N = g.size();
	for (int i = 0; i < N; ++i) {
		bool hasLoop = false;
		for (const auto& e : g._adj[i]) {
			if (e.first == i) {
				hasLoop = true;
				break;
			}
		}
		if (!hasLoop)
			g.addEdge(i, i, 0);
	}
	for (int k = 0; k < N; ++k) {
		discardVertex(g, k);
	}
}



/// How the glues-matrix is represented.
/// If "glues[i][j] == -1", it means that 'i' is directly connected to 'j'.
typedef std::vector< std::vector< int > > glues_matrix_type;


/// Prints provided glues matrix to the console.
void printGluesMatrix( const glues_matrix_type& glues )
{
	using namespace std;
	const int N = glues.size();
	// Print the header
	cout << "   ";
	for ( int j = 0; j < N; ++j )
		cout << "  " << char('A'+j);
	cout << endl;
	cout << "   ";
	for ( int j = 0; j < N; ++j )
		cout << " --";
	cout << endl;
	// Print the table
	for ( int i = 0; i < N; ++i ) {
		cout << " " << char('A'+i) << "|";
		for ( int j = 0; j < N; ++j )
			cout << "  " << (glues[i][j] != -1 ? char('A'+glues[i][j]) : '-');
		cout << endl;
	}
}


/// Runs Floyd-Warshall all-pair shortest paths algorithm on the 
/// provided graph 'g', and remembers the glue vertices in 'glues' matrix.
void floydWarshallShortestPathsWithGlues( 
		WeightedAdjacencyMatrix& g, glues_matrix_type& glues )
{  int N = g.size();
	for (int i = 0; i < N; ++i){
		g._m[i][i] = 0;
		glues[i][i] = -1;
	}
	for (int k = 0; k < N; ++k)
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (g._m[i][k] != WEIGHTED_ADJ_MATRIX_INF && g._m[k][j] != WEIGHTED_ADJ_MATRIX_INF)
					if (g._m[i][k] + g._m[k][j] < g._m[i][j]) {
						g._m[i][j] = g._m[i][k] + g._m[k][j];
						glues[i][j] = k;
					}
}


/// Prints all the vertices of shortest path from 's' to 't', 
/// in exclusive way: (s..t).
void printPathExclusive( const glues_matrix_type& glues, int s, int t )
{
	int glue = glues[s][t];
	if ( glue == -1 )
		return;  // Nothing to print, as "s-->t" itself is on the shortest path.
	printPathExclusive( glues, s, glue );
	std::cout << " " << char(glue+'A');
	printPathExclusive( glues, glue, t );
}


void printPathExclusive_(const glues_matrix_type& glues, int s, int t) {
	std::vector<std::pair<int, int>> stack;
	stack.push_back({s, t});

	while (!stack.empty()) {
		auto [from, to] = stack.back();
		stack.pop_back();

		int glue = glues[from][to];
		if (glue == -1) continue;

		stack.push_back({from, to});
		stack.push_back({glue, to});
		stack.push_back({from, glue});

		std::cout << " " << char(glue + 'A');
	}
}



/// Prints all the vertices of shortest path from 's' to 't', 
/// in inclusive way: [s..t].
void printPathInclusive( const glues_matrix_type& glues, int s, int t )
{
	std::cout << " [ " << char(s+'A');
	printPathExclusive( glues, s, t );
	std::cout << " " << char(t+'A') << " ]" << std::endl;
}

void printDensityPercent(const WeightedAdjacencyMatrix& g) {
	const int N = g.size();
	int edgeCount = 0;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (i != j && g.hasEdge(i, j))
				++edgeCount;

	int totalPossible = N * (N - 1);
	double raw = 100.0 * edgeCount / totalPossible;
	int whole = (int)raw;
	int decimal = (int)((raw - whole) * 100 + 0.5);
	std::cout << "Current density: " << whole << ".";
	if (decimal < 10)
		std::cout << decimal << "%" << std::endl;
}


using std::cout;
using std::endl;


int main( int argc, char* argv[] )
{
	/**
	 *       A--(7)--B--(12)--E
	 *       |       |        |
	 *      (1)     (2)      (4)
	 *       |       |        |
	 *       F       H--(3)---G
	 *       |       |
	 *     (22)     (6)
	 *       |       |
	 *       C--(2)--D
	 */

	const int N = 8;
	WeightedAdjacencyMatrix g( N );
	g.addUndirectedEdge( 'A', 'B', 7 );
	g.addUndirectedEdge( 'B', 'E', 12 );
	g.addUndirectedEdge( 'E', 'G', 4 );
	g.addUndirectedEdge( 'H', 'G', 3 );
	g.addUndirectedEdge( 'B', 'H', 2 );
	g.addUndirectedEdge( 'A', 'F', 1 );
	g.addUndirectedEdge( 'F', 'C', 22 );
	g.addUndirectedEdge( 'H', 'D', 6 );
	g.addUndirectedEdge( 'C', 'D', 2 );

	cout << "\t The input graph (adjacency matrix)..." << endl;
	{
		g.print();
	}

	cout << "\t Discarding some vertices..." << endl;
	{
		WeightedAdjacencyMatrix g_copy( g );
		//
		discardVertex( g_copy, 'G'-'A' );
		cout << "After discarding 'G': " << endl;
		g_copy.print();
		//
		discardVertex( g_copy, 'H'-'A' );
		cout << "After discarding 'H': " << endl;
		g_copy.print();
	}

	cout << "\t Constructing shortest paths..." << endl;
	{
		WeightedAdjacencyMatrix g_copy( g );
		floydWarshallShortestPaths( g_copy );
		g_copy.print();
	}

	WeightedAdjacencyList h( N );
	h.addUndirectedEdge( 'A', 'B', 7 );
	h.addUndirectedEdge( 'B', 'E', 12 );
	h.addUndirectedEdge( 'E', 'G', 4 );
	h.addUndirectedEdge( 'H', 'G', 3 );
	h.addUndirectedEdge( 'B', 'H', 2 );
	h.addUndirectedEdge( 'A', 'F', 1 );
	h.addUndirectedEdge( 'F', 'C', 22 );
	h.addUndirectedEdge( 'H', 'D', 6 );
	h.addUndirectedEdge( 'C', 'D', 2 );

	cout << "\t The input graph (adjacency list)..." << endl;
	{
		h.print();
	}

	cout << "\t Discarding some vertices..." << endl;
	{
		WeightedAdjacencyList h_copy( h );
		//
		discardVertex( h_copy, 'G'-'A' );
		cout << "After discarding 'G': " << endl;
		h_copy.print();
		//
		discardVertex( h_copy, 'H'-'A' );
		cout << "After discarding 'H': " << endl;
		h_copy.print();
	}

	cout << "\t Constructing shortest paths..." << endl;
	{
		WeightedAdjacencyList h_copy( h );
		floydWarshallShortestPaths( h_copy );
		h_copy.print();
	}

	cout << "\t Constructing shortest paths with glues..." << endl;
	{
		WeightedAdjacencyMatrix g_copy( g );
		glues_matrix_type glues( 
				g_copy.size(), 
				std::vector<int>( g_copy.size(), -1 ) );
		floydWarshallShortestPathsWithGlues( g_copy, glues );
		printGluesMatrix( glues );

		cout << "One shortest path is:";
		printPathInclusive( glues, 'A'-'A', 'C'-'A' );

		cout << "Another shortest path is:";
		printPathInclusive( glues, 'F'-'A', 'E'-'A' );
	}

	return 0;
}
