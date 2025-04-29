
#ifndef _ADJACENCY_LIST_HPP
#define _ADJACENCY_LIST_HPP

#include <list>
#include <vector>
#include <algorithm>


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
	bool hasEdge( char u, char v ) const
		{ return hasEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Adds edge "(u,v)" to this graph, in case if it was not present.
	void addEdge( int u, int v ) {
		if ( ! hasEdge( u, v ) )
			_adj[ u ].push_back( v );
	}
	void addEdge( char u, char v )
		{ addEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Removes edge "(u,v)" from this graph, in case if it is present.
	void removeEdge( int u, int v ) {
		_adj[ u ].remove( v );
	}
	void removeEdge( char u, char v )
		{ removeEdge( (int)(u-'A'), (int)(v-'A') ); }

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
};


#endif // _ADJACENCY_LIST_HPP
