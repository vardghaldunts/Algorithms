
#ifndef _ADJACENCY_MATRIX_HPP
#define _ADJACENCY_MATRIX_HPP

#include <vector>


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
	bool hasEdge( char u, char v ) const
		{ return hasEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Adds edge "(u,v)" to this graph, in case if it was not present.
	void addEdge( int u, int v )
		{ _m[u][v] = true; }
	void addEdge( char u, char v )
		{ addEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Removes edge "(u,v)" from this graph, in case if it is present.
	void removeEdge( int u, int v )
		{ _m[u][v] = false; }
	void removeEdge( char u, char v )
		{ removeEdge( (int)(u-'A'), (int)(v-'A') ); }

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
};


#endif // _ADJACENCY_MATRIX_HPP
