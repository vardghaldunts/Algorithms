
/**
 * Exercises:
 * 
 * Implement function "is_right_turn()".                    v
 * 
 * Implement function "is_convex_polygon()".
 * 
 * Look at how function "sort_ccw()" is implemented.
 * 
 * Implement function "is_clockwise_round()".
 *     >> write 2 tests for it.
 */


#include <iostream>
#include <algorithm>

#include "Point.hpp"


/// Tests if given sequence of "vertices" represent a convex polygon.
/// Note, "vertices" can list all the points both in clockwise and 
/// counter-clockwise orders.
bool is_convex_polygon( const std::vector< Point >& vertices ) {
   //implement
	return false;
}

/// Sorts given points in counter-clockwise order.
void sort_ccw( std::vector< Point >& vertices ) {
	const Point center = find_center( vertices );
	// Sort around it
	std::sort( vertices.begin(), vertices.end(), 
			[&center]( const Point& a, const Point& b ) {
				return (a - center).angle_from_zero() < (b - center).angle_from_zero();
			} );
}

/// Determines if cyclic round on "vertices" results in clockwise turn around, 
/// or counter-clockwise turn around.
bool is_clockwise_round( const std::vector< Point >& vertices ) {
	//
	// Implement
	//
	return false;
}


int main()
{
	using std::cout;
	using std::endl;

	cout << "\t Testing angles ..." << endl;
	{
		Point a( 5, 3 );
		Point b( -7, 9 );
		Point c( -1, -1 );
		cout << "Angle of 'a' is " << a.angle_from_zero() << endl;
		cout << "Angle of 'b' is " << b.angle_from_zero() << endl;
		cout << "Angle of 'c' is " << c.angle_from_zero() << endl;
	}

	{
		Point a( 5, 3 );
		Point b( 6, 4 );
		Point c( 7, 5 );
		cout << "Angle of [a, b, c] is " << angle( a, b, c ) << endl;

		Point d( 7, 10 );
		cout << "Angle of [a, b, d] is " << angle( a, b, d ) << endl;

		Point e( 12, 5 );
		cout << "Angle of [a, b, e] is " << angle( a, b, e ) << endl;
	}

	cout << "\t Testing 'is_convex_polygon()' function ..." << endl;
	{
		//       *
		//    *     *
		//    *      
		//          *
		//
		std::vector< Point > vertices_1({
				Point(3,3), Point(0,2), Point(0,1),
				Point(6,0), Point(6,2) });
		cout << "Is convex (vertices_1) : " << is_convex_polygon( vertices_1 ) << endl;

		//       *
		//    *     *   *
		//    *      
		//          *
		//
		std::vector< Point > vertices_2 = vertices_1;
		vertices_2.push_back( Point(10,2) );
		cout << "Is convex (vertices_2) : " << is_convex_polygon( vertices_2 ) << endl;

		// Reversed polygon 1
		std::reverse( vertices_1.begin(), vertices_1.end() );
		cout << "Is convex (vertices_1 reversed) : " << is_convex_polygon( vertices_1 ) << endl;
	}

	cout << "\t Testing 'sort_ccw()' function ..." << endl;
	{
		//    *   *
		//   *     *
		//      *
		//
		std::vector< Point > vertices_1({
				Point(3,0), Point(0,1), Point(6,1),
				Point(5,2), Point(1,2) });
		sort_ccw( vertices_1 );
		print_points( vertices_1 );

		//     *
		//       *
		//     *
		//       *
		std::vector< Point > vertices_2({
				Point(0,3), Point(2,2), Point(0,1), Point(2,0) });
		sort_ccw( vertices_2 );
		print_points( vertices_2 );
	}

	cout << "\t Testing 'is_clockwise_round()' function ..." << endl;
	{
		// Write 2 tests here
		//
		//
	}

	return 0;
}
