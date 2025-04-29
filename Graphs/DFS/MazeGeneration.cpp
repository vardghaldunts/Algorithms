
/**
 * Tasks:
 * 
 * Look at how the class "Maze" is written.
 * 
 * Look at how global function "generate_maze()" is written.
 * 
 * Change the function "generate_helper()", so real randomized mazes
 *         will be generated.
 * 
 * Implement function "generate_maze_with_walls()".
 *     >> write a test to check its correctness.
 * 
 */


#include <vector>
#include <iostream>
#include <cassert>


/// This class represents a maze on a plane.
class Maze
{
protected:
	typedef std::vector< std::vector< bool > > walls_type;

	/// The matrix of horizontal walls
	walls_type _h_walls;

	/// The matrix of vertical walls
	walls_type _v_walls;

public:
	/// Constructor
	/// Prepares an "m*n" sizes maze, with no walls.
	Maze( int m_, int n_ )
		: _h_walls( m_+1, std::vector< bool >( n_, false ) ), 
		  _v_walls( m_, std::vector< bool >( n_+1, false ) ) {
		// Place horizontal bounding walls
		_h_walls.front() = _h_walls.back() 
				= std::vector< bool >( n_, true );
		// Place vertical bounding walls
		for ( int row = 0; row < m_; ++row )
			_v_walls[row].front() = _v_walls[row].back() = true;
	}

	/// Returns number of rows
	int m() const
		{ return _v_walls.size(); }

	/// Returns number of columns
	int n() const
		{ return _h_walls[ 0 ].size(); }

	/// Places / removes horizontal wall at the top of cell (row,col).
	void set_h_wall( int row, int col, bool on )
		{ _h_walls[row][col] = on; }

	/// Places / removes vertical wall at the left side of cell (row,col).
	void set_v_wall( int row, int col, bool on )
		{ _v_walls[row][col] = on; }

	/// Checks is we can step by specified direction, while being 
	/// on cell (row,col).
	bool can_go_left( int row, int col ) const
		{ return _h_walls[row][col] == false; }
	bool can_go_right( int row, int col ) const
		{ return _h_walls[row][col+1] == false; }
	bool can_go_up( int row, int col ) const
		{ return _v_walls[row][col] == false; }
	bool can_go_down( int row, int col ) const
		{ return _v_walls[row+1][col] == false; }

	/// Prints this maze
	void print() const
	{
		for ( int i = 0; i < 2*m()+1; ++i ) {
			for ( int j = 0; j < 2*n()+1; ++j ) {
				if ( i % 2 == 0 ) {
					if ( j % 2 == 0 )
						std::cout.put( '+' );
					else
						std::cout.put( _h_walls[ i/2 ][ j/2 ] ? '-' : ' ' );
				}
				else {
					if ( j % 2 == 0 )
						std::cout.put( _v_walls[ i/2 ][ j/2 ] ? '|' : ' ' );
					else
						std::cout.put( ' ' );
				}
			}
			std::cout << std::endl;
		}
	}
};


/// The colors, used during DFS algorithm
enum Color {
	WHITE, 
	GRAY, 
	BLACK
};

// How a matrix of colors is represented.
typedef std::vector< std::vector< Color > > colors_matrix_type;


/// Continues generation of maze, by removing walls in 'g', assuming 
/// that we are now on the cell (i,j), and want to go on some adjacent cell.
void generate_helper( Maze& g, int i, int j, colors_matrix_type& colors )
{
	assert( colors[i][j] == WHITE );
	// Enter the cell
	colors[i][j] = GRAY;
	// Try all the 4 directions
	if ( i > 0 && colors[i-1][j] == WHITE ) {
		g.set_h_wall( i, j, false );  // remove the wall upwards
		generate_helper( g, i-1, j, colors );
	}
	if ( j > 0 && colors[i][j-1] == WHITE ) {
		g.set_v_wall( i, j, false );  // remove the wall to left
		generate_helper( g, i, j-1, colors );
	}
	if ( i < g.m()-1 && colors[i+1][j] == WHITE) {
		g.set_h_wall( i+1, j, false );  // remove the wall downwards
		generate_helper( g, i+1, j, colors );
	}
	if ( j < g.n()-1 && colors[i][j+1] == WHITE) {
		g.set_v_wall( i, j+1, false );  // remove the wall to right
		generate_helper( g, i, j+1, colors );
	}
	// Leave the cell
	colors[i][j] = BLACK;
}


/// Generates a random maze of size 'm*n'.
Maze generate_maze( int m, int n )
{
	Maze g( m, n );
	// Initially place all walls
	for ( int i = 0; i < m; ++i )
		for ( int j = 1; j < n; ++j )
			g.set_v_wall( i, j, true );
	for ( int i = 1; i < m; ++i )
		for ( int j = 0; j < n; ++j )
			g.set_h_wall( i, j, true );
	// Prepare the matrix of colors
	colors_matrix_type colors(
			m, 
			std::vector< Color >( n, WHITE ) );
	// Run DFS from top-left cell.
	generate_helper( g, 0, 0, colors );
	// Return all the remaining walls
	return g;
}

#include <random>
#include <algorithm>

void generate_helper_random(Maze& g, int i, int j, colors_matrix_type& colors) {
	assert(colors[i][j] == WHITE);
	colors[i][j] = GRAY;

	std::vector<std::pair<int, int>> directions = {
		{-1, 0}, // up
		{0, -1}, // left
		{1, 0},  // down
		{0, 1}   // right
	};

	std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device{}()));

	for (auto [di, dj] : directions) {
		int ni = i + di, nj = j + dj;
		if (ni >= 0 && ni < g.m() && nj >= 0 && nj < g.n() && colors[ni][nj] == WHITE) {
			if (di == -1) g.set_h_wall(i, j, false);       // up
			if (di == 1)  g.set_h_wall(i + 1, j, false);   // down
			if (dj == -1) g.set_v_wall(i, j, false);       // left
			if (dj == 1)  g.set_v_wall(i, j + 1, false);   // right
			generate_helper_random(g, ni, nj, colors);
		}
	}

	colors[i][j] = BLACK;
}


/// Generates a random maze of size 'm*n', such that all walls which 
/// are set in 'walls', remain in the generated maze.
Maze generate_maze_with_walls(int m, int n, const Maze& walls)
{
	Maze g(m, n);

	for (int i = 0; i < m; ++i)
		for (int j = 1; j < n; ++j)
			g.set_v_wall(i, j, walls.can_go_right(i, j) == false);

	for (int i = 1; i < m; ++i)
		for (int j = 0; j < n; ++j)
			g.set_h_wall(i, j, walls.can_go_down(i - 1, j) == false);

	colors_matrix_type colors(m, std::vector<Color>(n, WHITE));
	generate_helper_random(g, 0, 0, colors);

	return g;
}



using std::cout;
using std::endl;


int main()
{
	cout << "\t Creating an empty maze..." << endl;
	{
		Maze g( 6, 4 );
		g.print();
	}

	cout << "\t Generating maze..." << endl;
	{
		// Sizes of a maze
		const int M = 8, N = 16;
		Maze g = generate_maze( M, N );
		g.print();
	}

	return 0;
}

