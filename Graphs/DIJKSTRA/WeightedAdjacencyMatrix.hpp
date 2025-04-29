
#ifndef _WEIGHTED_ADJACENCY_MATRIX_HPP
#define _WEIGHTED_ADJACENCY_MATRIX_HPP

#include <vector>
#include <limits>


/// How absence of edge is represented.
static const double WEIGHTED_ADJ_MATRIX_INF = 1e+40;


/// This class represents a simple adjacency matrix of a unweighted graph.
struct WeightedAdjacencyMatrix
{
	typedef std::vector< std::vector< double > > matrix_type;

	/// The adjacency matrix.
	/// "_m[u][v]" denotes weight of edge (u,v).
	/// If there is no such edge, then "_m[u][v] = WEIGHTED_ADJ_MATRIX_INF".
	matrix_type _m;

public:
	/// Sets number of vertices in this graph.
	/// Removes all existing edges by the way.
	void setSize( int N )
		{ _m.clear();
		  _m.resize( N, std::vector< double >( N, WEIGHTED_ADJ_MATRIX_INF ) ); }

	/// Number of vertices in this graph.
	int size() const
		{ return (int)_m.size(); }

	/// Check if edge "(u,v)" is present.
	bool hasEdge( int u, int v ) const
		{ return _m[u][v] != WEIGHTED_ADJ_MATRIX_INF; }
	bool hasEdge( char u, char v ) const
		{ return hasEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Adds directed edge "(u,v)" with specified 'weight' to this graph.
	void addEdge( int u, int v, double weight )
		{ _m[u][v] = weight; }
	void addEdge( char u, char v, double weight )
		{ addEdge( (int)(u-'A'), (int)(v-'A'), weight ); }

	/// Adds undirected edge (u,v) to this graph, with specified 'weight'.
	void addUndirectedEdge( int u, int v, double weight )
		{ addEdge( u, v, weight );
		  addEdge( v, u, weight ); }
	void addUndirectedEdge( char u, char v, double weight )
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
};


#endif // _WEIGHTED_ADJACENCY_MATRIX_HPP
