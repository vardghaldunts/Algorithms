
#ifndef _WEIGHTED_ADJACENCY_LIST_HPP
#define _WEIGHTED_ADJACENCY_LIST_HPP

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>


// How weight of an edge is represented
typedef int adj_list_weight_type;


/// This class represents given weighted graph as adjacency list.
struct WeightedAdjacencyList
{
	/// How 1 edge is represented
	typedef std::pair< int, adj_list_weight_type > edge_type;

	/// How all adjacent edges are represented
	typedef std::list< edge_type > list_type;

	/// How the graph is represented
	typedef std::vector< list_type > lists_type;

	/// Adjacency list of the entire graph.
	lists_type _adj;

public:
	/// [Default] constructor.
	explicit WeightedAdjacencyList( int N = 0 )
		{ setSize( N ); }

	/// Updates number of vertices in the graph.
	/// Clears existing edges, by the way.
	void setSize( int N )
		{ _adj.clear();
		  _adj.resize( N ); }

	/// Returns number of vertices in this graph.
	int size() const
		{ return (int)_adj.size(); }

	/// Checks if the graph has edge "(u,v)".
	bool hasEdge( int u, int v ) const
		{ return std::count_if( _adj[u].cbegin(), _adj[u].cend(), 
				[v]( const edge_type& e ) 
					{ return e.first == v; } 
				) == 1; }
	bool hasEdge( char u, char v ) const
		{ return hasEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Adds edge "(u,v)", having weight 'w' to this graph, 
	/// in case if it was not present.
	void addEdge( int u, int v, adj_list_weight_type w ) {
		if ( ! hasEdge(u, v) )
			_adj[ u ].push_back( edge_type(v, w) );
	}
	void addEdge( char u, char v, adj_list_weight_type w )
		{ addEdge( (int)(u-'A'), (int)(v-'A'), w ); }

	/// Adds undirected edge (u,v) to this graph, with specified 'w'.
	void addUndirectedEdge( int u, int v, adj_list_weight_type w )
		{ addEdge( u, v, w );
		  addEdge( v, u, w ); }
	void addUndirectedEdge( char u, char v, adj_list_weight_type w )
		{ addUndirectedEdge( (int)(u-'A'), (int)(v-'A'), w ); }

	/// Removes edge "(u,v)" from this graph, in case if it is present.
	void removeEdge( int u, int v ) {
		_adj[ u ].remove_if(
				[v]( const edge_type& e ) 
					{ return e.first == v; } 
				);
	}
	void removeEdge( char u, char v )
		{ removeEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Removes undirected edge (u,v) from this graph.
	void removeUndirectedEdge( int u, int v )
		{ removeEdge( u, v );
		  removeEdge( v, u ); }
	void removeUndirectedEdge( char u, char v )
		{ removeUndirectedEdge( (int)(u-'A'), (int)(v-'A') ); }

	/// Prints this adjacency list to the console
	void print() const
	{
		using namespace std;
		const int N = size();
		for ( int i = 0; i < N; ++i ) {
			cout << "  " << char('A'+i) << ": [";
			for ( const auto& e : _adj[i] )
				cout << " (" << char('A'+e.first) << "," << e.second << ")";
			cout << " ]" << endl;
		}
	}
};


#endif // _WEIGHTED_ADJACENCY_LIST_HPP
