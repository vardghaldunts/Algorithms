/**
 * Tasks:
 * 
 * Look at how "DFS_runner::dfs()" method is implemented.
 *     >> finish remaining expressions.
 * 
 * Implement method "DFS_runner::reportReachableAndUnreachable()".
 *     >> check it with the tests.
 * 
 * Enhance "DFS_runner" class (or write another class), so we can 
 *         run DFS also on AdjacencyList.
 * 
 * Implement "DFS_runner::reportAsymmetricalPairs()" method,
 *     >> check that it passes the tests.
 * 
 * Implement method "DFS_runner::runIterative()".
 *     >> check that the results are same.
 * 
 */


#include <vector>
#include <iostream>
#include <cassert>

#include "AdjacencyMatrix.hpp"
#include "AdjacencyList.hpp"


/// This class is intended to run DFS algorithm over graphs, 
/// represented by adjacency matrix.
struct DFS_runner
{
	/// The graph, to run DFS on.
	AdjacencyMatrix _g;

	/// The vertex from which DFS was run.
	int _source;

	/// Colors used for labeling the vertices.
	enum Color {
		WHITE = 0,
		GRAY = 1,
		BLACK = 2
	};

	/// Colors of all the vertices.
	std::vector< Color > _colors;

protected:
	/// Continues DFS algorithm from vertex 's'.
	void dfs( int s ) {
		const int N = _g.size();  // Number of vertices
		assert( _colors[ s ] == WHITE );
		_colors[ s ] = GRAY;  // We enter the vertex 's'
		for ( int t = 0; t < N; ++t )
			if ( _g._m[s][t] && _colors[ t ] == WHITE )
				dfs( t );
		_colors[ s ] = BLACK;  // We leave the vertex 's'
	}

public:
	/// Runs DFS on graph 'g_', from provided vertex 'source_'.
	void run( const AdjacencyMatrix& g_, int source_ ) {
		_g = g_;  // Remember the arguments
		_source = source_;
		const int N = _g.size();  // Number of vertices
		_colors = std::vector< Color >( N, WHITE );  // All vertices start from white
		dfs( source_ );
	}
	//
	void run( const AdjacencyMatrix& g_, char source_ )
		{ run( g_, source_-'A' ); }

	/// Reports list of reachable and unreachable vertices, in 2 lines.
	void reportReachableAndUnreachable() const {


		std::cout << "reachable"<<std::endl;
		for ( int i = 0 ; i < _colors.size() ; ++i){
			if ( _colors[i] != WHITE){

				char result = 'A' + i;
				std::cout << result <<" , ";
			}
		}
		std::cout << "unreachable"<<std::endl;
		for ( int i = 0 ; i < _colors.size() ; ++i){
			if ( _colors[i] == WHITE){

				char result = 'A' + i;
				std::cout << result <<" , ";
			}
		}

		std::cout<<std::endl;
	}


	/// Prints pairs of all such vertices (u,v) where only one is 
	/// reachable from the other.
	void reportAsymmetricalPairs()  {

		const int N = _g.size();

		std::vector<std::vector<bool>> reachable(N ,std::vector<bool> (N , false));

		for ( int u = 0; u < N ; ++ u){
			run(_g,u);
			for ( int v = 0; v < N ;++v){
				if(_colors[v] != WHITE){
					reachable[u][v] = true;
				}
			}
		}

		for ( int u = 0 ; u < N ; ++u){
			for (int v = u+1; v < N ; ++v){
				if ( reachable[u][v] != reachable[v][u]){
					std::cout<<"( "<<(char)('A' + u) <<" , "<< (char)('A'+ v) <<" )"<<std::endl;
				}
			}
		}
	}


	/// Runs DFS on graph 'g_', in an iterative manner.
	void runIterative(const AdjacencyMatrix& g_, int source_) {
		_g = g_;
		_source = source_;
		const int N = _g.size();
		_colors = std::vector<Color>(N, WHITE);

		std::vector<int> stack;
		stack.push_back(source_);

		while (!stack.empty()) {
			int s = stack.back();

			if (_colors[s] == WHITE) {
				_colors[s] = GRAY;
			}

			bool pushed = false;
			for (int t = 0; t < N; ++t) {
				if (_g._m[s][t] && _colors[t] == WHITE) {
					stack.push_back(t);
					pushed = true;
					break;
				}
			}

			if (!pushed) {
				_colors[s] = BLACK;
				stack.pop_back();
			}
		}
	}

};


struct DFS_runner_List {
    AdjacencyList _g;
    int _source;

    enum Color {
        WHITE = 0,
        GRAY = 1,
        BLACK = 2
    };

    std::vector<Color> _colors;

protected:
    void dfs(int s) {
        assert(_colors[s] == WHITE);
        _colors[s] = GRAY;
        for (int t : _g._adj[s]) {
            if (_colors[t] == WHITE)
                dfs(t);
        }
        _colors[s] = BLACK;
    }

public:
    void run(const AdjacencyList& g_, int source_) {
        _g = g_;
        _source = source_;
        int N = _g.size();
        _colors = std::vector<Color>(N, WHITE);
        dfs(source_);
    }

    void run(const AdjacencyList& g_, char source_) {
        run(g_, source_ - 'A');
    }

    void reportReachableAndUnreachable() const {
        std::cout << "reachable" << std::endl;
        for (int i = 0; i < _colors.size(); ++i) {
            if (_colors[i] != WHITE)
                std::cout << (char)('A' + i) << " , ";
        }

        std::cout << std::endl << "unreachable" << std::endl;
        for (int i = 0; i < _colors.size(); ++i) {
            if (_colors[i] == WHITE)
                std::cout << (char)('A' + i) << " , ";
        }
        std::cout << std::endl;
    }

    void reportAsymmetricalPairs() {
        int N = _g.size();
        std::vector<std::vector<bool>> reachable(N, std::vector<bool>(N, false));

        for (int u = 0; u < N; ++u) {
            run(_g, u);
            for (int v = 0; v < N; ++v) {
                if (_colors[v] != WHITE)
                    reachable[u][v] = true;
            }
        }

        for (int u = 0; u < N; ++u) {
            for (int v = u + 1; v < N; ++v) {
                if (reachable[u][v] != reachable[v][u])
                    std::cout << "( " << (char)('A' + u) << " , " << (char)('A' + v) << " )" << std::endl;
            }
        }
    }

    void runIterative(const AdjacencyList& g_, int source_) {
        _g = g_;
        _source = source_;
        int N = _g.size();
        _colors = std::vector<Color>(N, WHITE);

        std::vector<int> stack;
        stack.push_back(source_);

        while (!stack.empty()) {
            int s = stack.back();

            if (_colors[s] == WHITE)
                _colors[s] = GRAY;

            bool pushed = false;
            for (int t : _g._adj[s]) {
                if (_colors[t] == WHITE) {
                    stack.push_back(t);
                    pushed = true;
                    break;
                }
            }

            if (!pushed) {
                _colors[s] = BLACK;
                stack.pop_back();
            }
        }
    }
};

using std::cout;
using std::endl;

int main()
{
	/*
	 *     A --> B --> F
	 *           |
	 *           v
	 *     D <-- C --> E     I <-- K
	 *           ^     |     |
	 *           |     v     v
	 *           G <-- H     J
	 */
	const int N = 8 + 3;  // Number of vertices
	AdjacencyMatrix g;
	g._m.resize( N, std::vector< bool >( N, false ) );
	g.addEdge( 'A', 'B' );
	g.addEdge( 'B', 'F' );
	g.addEdge( 'B', 'C' );
	g.addEdge( 'C', 'E' );
	g.addEdge( 'C', 'D' );
	g.addEdge( 'E', 'H' );
	g.addEdge( 'H', 'G' );
	g.addEdge( 'G', 'C' );
	g.addEdge( 'I', 'J' );
	g.addEdge( 'K', 'I' );

	DFS_runner runner;

	cout << "\t Testing 'reportReachableAndUnreachable()' ..." << endl;
	{
		runner.run( g, 'A' );
		cout << "After running from 'A': " << endl;
		runner.reportReachableAndUnreachable();

		runner.run( g, 'G' );
		cout << "After running from 'G': " << endl;
		runner.reportReachableAndUnreachable();

		runner.run( g, 'K' );
		cout << "After running from 'K': " << endl;
		runner.reportReachableAndUnreachable();
	}

	cout << "\t Testing 'reportAsymmetricalPairs()' ..." << endl;
	{
		runner.reportAsymmetricalPairs();
	}

	return 0;
}
