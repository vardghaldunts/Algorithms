#ifndef __POINT_HPP
#define __POINT_HPP


/**
 * Exercises:
 *
 * Look how the class "Point", and the next global functions are implemented.
 */


#include <vector>
#include <iostream>
#include <cmath>


/// The value of PI constant.
static const float PI = acosf(-1.0f);


/// This class represents a point on a plane.
struct Point
{
	float _x, _y;  // The coordinates

	Point()  // Default constructor
		: _x(0.0f), _y(0.0f)
		{}

	Point( float x_, float y_ )  // Constructor
		: _x(x_), _y(y_)
		{}

	/// Returns distance of this point from (0,0).
	float length() const {
		return sqrt( _x*_x + _y*_y );
	}

	/// Returns cosine of the angle, that this point forms when looking
	/// from (0,0).
	float angle_cos_from_zero() const {
		return _y / length();
	}

	/// Returns the angle that this point forms, when looking from (0,0).
	float angle_from_zero() const {
		return atan2f( _y, _x );
	}
};

/// Sum of 2 vectors.
inline Point operator+( const Point& a, const Point& b ) {
	return Point( a._x+b._x, a._y+b._y );
}

/// Difference of 2 vectors.
inline Point operator-( const Point& a, const Point& b ) {
	return Point( a._x-b._x, a._y-b._y );
}

/// Calculates and returns the angle "a,b,c", at point 'b'.
float angle( const Point& a, const Point& b, const Point&c ) {
	Point u = b - a;
	Point v = c - b;
	float angle = v.angle_from_zero() - u.angle_from_zero();
	// Make sure the angle stays in [-PI, PI).
	if ( angle < -PI )
		angle += 2.0f*PI;
	else if ( angle >= PI )
		angle -= 2.0f*PI;
	return angle;
}

/// Tests if points [a, b, c] form a left turn.
bool is_left_turn( const Point& a, const Point& b, const Point& c ) {
	return angle( a, b, c ) < 0.0f;
}

/// Tests if points [a, b, c] form a right turn.
bool is_right_turn( const Point& a, const Point& b, const Point& c ) {
	return angle( a, b, c ) > 0.0f;
}

/// Calculates and returns algebraic center of given points.
Point find_center( const std::vector< Point >& points ) {
	const int N = (int)points.size();
	Point center;
	for ( const Point& v : points )
		center = center + v;
	center._x /= N;
	center._y /= N;
	return center;
}

/// Prints provided points in one line.
void print_points( const std::vector< Point >& pts ) {
	std::cout << "[ ";
	for ( const Point& pt : pts )
		std::cout << "(" << pt._x << "," << pt._y << ") ";
	std::cout << "]" << std::endl;
}


#endif // __POINT_HPP
