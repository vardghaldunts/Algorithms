
#ifndef _WEIGHTED_ADJACENCY_MATRIX_HPP
#define _WEIGHTED_ADJACENCY_MATRIX_HPP

#include <vector>
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>


/// How the weight is being represented
typedef int adj_matrix_weight_type;

/// How absence of edge is represented.
static const adj_matrix_weight_type WEIGHTED_ADJ_MATRIX_INF = 999'999;


/// This class represents a simple adjacency matrix of a unweighted graph.
struct WeightedAdjacencyMatrix
{
	typedef std::vector< std::vector< adj_matrix_weight_type > > matrix_type;

	/// The adjacency matrix.
	/// "_m[u][v]" denotes weight of edge (u,v).
	/// If there is no such edge, then "_m[u][v] = WEIGHTED_ADJ_MATRIX_INF".
	matrix_type _m;

public:
	/// [Default] constructor
	explicit WeightedAdjacencyMatrix( int N = 0 )
		{ setSize( N ); }

	/// Sets number of vertices in this graph.
	/// Removes all existing edges by the way.
	void setSize( int N )
		{ _m.clear();
		  _m.resize( N, std::vector< adj_matrix_weight_type >( N, WEIGHTED_ADJ_MATRIX_INF ) ); }

	/// Number of vertices in this graph.
	int size() const
		{ return (int)_m.size(); }

	/// Check if edge "(u,v)" is present.
	bool hasEdge( int u, int v ) const
		{ return _m[u][v] != WEIGHTED_ADJ_MATRIX_INF; }
	bool hasEdge( char u, char v ) const
		{ return hasEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Adds directed edge "(u,v)" with specified 'weight' to this graph.
	void addEdge( int u, int v, adj_matrix_weight_type weight )
		{ _m[u][v] = weight; }
	void addEdge( char u, char v, adj_matrix_weight_type weight )
		{ addEdge( (int)(u-'A'), (int)(v-'A'), weight ); }

	/// Adds undirected edge (u,v) to this graph, with specified 'weight'.
	void addUndirectedEdge( int u, int v, adj_matrix_weight_type weight )
		{ addEdge( u, v, weight );
		  addEdge( v, u, weight ); }
	void addUndirectedEdge( char u, char v, adj_matrix_weight_type weight )
		{ addUndirectedEdge( (int)(u-'A'), (int)(v-'A'), weight ); }

	/// Removes directed edge "(u,v)" from this graph, in case if it is present.
	void removeEdge( int u, int v )
		{ _m[u][v] = WEIGHTED_ADJ_MATRIX_INF; }
	void removeEdge( char u, char v )
		{ removeEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Removes undirected edge (u,v) from this graph.
	void removeUndirectedEdge( int u, int v )
		{ removeEdge( u, v );
		  removeEdge( v, u ); }
	void removeUndirectedEdge( char u, char v )
		{ removeUndirectedEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Prints this matrix to the console
	void print() const
	{
		using namespace std;
		const int W = 3;  // Width of one cell
		const int N = size();
		// Print the header
		cout << setw( W+1 ) << " ";
		for ( int j = 0; j < N; ++j )
			cout << setw( W ) << char('A'+j);
		cout << endl;
		cout << setw( W+1 ) << " ";
		for ( int j = 0; j < N; ++j )
			cout << setw( W ) << "--";
		cout << endl;
		// Print the table
		for ( int i = 0; i < N; ++i ) {
			cout << setw( W ) << char('A'+i) << "|";
			for ( int j = 0; j < N; ++j )
				cout << setw( W ) << (hasEdge(i,j) ? std::to_string( _m[i][j] ) : "-");
			cout << endl;
		}
	}
};


#endif // _WEIGHTED_ADJACENCY_MATRIX_HPP
