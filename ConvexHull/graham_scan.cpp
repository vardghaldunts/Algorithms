
/**
 * Question: Why "graham_scan()" accepts just vector of points, and not 
 *     const-reference to such vector?
 * 
 * Question: Why we wrote here a separate "next()" function, and not 
 *     calculated "(i+1)%N" every time when needed?
 * 
 * Question: Why for the stack 'st' we use "std::vector<>" class, and 
 *     not "std::stack<>"?
 * 
 * Question: Why in the outer loop of the algorithm we consider 
 *     "v[ rightmost_index ]" twice - at the beginning and at the end?
 * 
 * Change the function "graham_scan()" in such way, that all the points 
 *     will be sorted and processed not in counter-clockwise, but in 
 *     clockwise order.
 * 
 * Change the function in the way that all points will be sorted by 
 *     angle around bottom-right point, and not the algebraic center.
 */

#include <algorithm>
#include <stack>

#include "Point.hpp"


/// Returns "i+1" modulo "N".
int next( int i, int N )
{
	++i;
	if ( i == N )
		i = 0;  // reset 'i', once reaching 'N'
	return i;
}


/// Performs Graham scan algorithm on given set of points, and returns 
/// their convex hull.
std::vector< Point > graham_scan( std::vector< Point >& vertices )
{
	const int N = (int)vertices.size();
	const Point center = find_center( vertices );
	// Sort all the vertices around center
	std::sort( vertices.begin(), vertices.end(),
			[&center]( const Point& a, const Point& b ) {
				return (a - center).angle_from_zero() < (b - center).angle_from_zero();
			});
	if ( N <= 3 )
		return vertices;  // Convex hull has at least 3 verices.
	// Find index of the right-most point
	int rightmost_index = std::max_element( 
			vertices.begin(), vertices.end(), 
			[]( const Point& a, const Point& b ) {
				return a._x < b._x;
			}) - vertices.begin();
	// Place & take off the stack
	std::vector< Point > st;
	int i = rightmost_index;
	st.push_back( vertices[ i ] );  // Place the rightmost point
	i = next( i, N );
	st.push_back( vertices[ i ] );  // Place also the point next to it
	i = next( i, N );
	//    ... cyclic iterate over sorted "vertices" array 
	while ( i != next( rightmost_index, N ) ) {
		const Point& v = vertices[i];
		//    ... remove from the stack vertices as long, as right turn
		//        is being formed with 'v'
		while ( st.size() >= 2 
				&& is_right_turn( st[st.size()-2], st[st.size()-1], v ) )
			st.pop_back();
		st.push_back( v );  // Always add current vertex 'v' to the stack.
		i = next( i, N );  // Move to cyclic-next point.
	}
	st.pop_back();  // Remove the rightmost vertex, placed 2nd time.
	return st;
}


int main()
{
	using std::cout;
	using std::endl;

	cout << "\t Testing 'graham_scan()' function ..." << endl;
	{
		//     *   *
		//       *
		//       *
		//
		std::vector< Point > vertices({
				Point(0,2), Point(4,2),
				Point(2,1),
				Point(2,0) });
		std::vector< Point > ch = graham_scan( vertices );
		cout << "Convex hull is :";
		print_points( ch );
	}
	{
		//     *     *
		//   *   **   *
		//      *    *     *
		//     *    
		//            *
		//
		std::vector< Point > vertices({
				Point(2,4), Point(8,4),
				Point(0,3), Point(4,3), Point(5,3), Point(9,3),
				Point(3,2), Point(8,2), Point(14,2),
				Point(2,1),
				Point(9,0) });
		std::vector< Point > ch = graham_scan( vertices );
		cout << "Convex hull is :";
		print_points( ch );
	}

	return 0;
}
