#include <iostream>
#include <math.h>
#include "triangle.hpp"

enum Point::Orientation { LEFT, RIGHT, BETWEEN, AHEAD, BEHIND };

Point::Point(float _x = 0, float _y = 0) : x(_x), y(_y) {}

void Point::set_x(float _x) {
	x = _x;
}
void Point::set_y(float _y) {
	y = _y;
}
void Point::set_coords(float _x, float _y) {
	x = _x;
	y = _y;
}

Point Point::operator +(const Point& point) const {
	return Point(x + point.x, y + point.y);
}
Point Point::operator -(const Point& point) const {
	return Point(x - point.x, y - point.y);
}

void Point::rotate(float angle) {
	float _x = x, _y = y;

	x = _x * cos(angle) - _y * sin(angle);
	y = _x * sin(angle) + _y * cos(angle);
}

void Point::print(char end) {
	printf("(%10.3f, %10.3f)%c", x, y, end);
}
void Point::scan(FILE* stream) {
	fscanf_s(stream, "%f%f", &x, &y);
}

Point::Orientation Point::get_orientation(Point& vector_begin, Point& vector_end) {
	Point ORIGIN(0, 0);
	Point vector_from_origin = vector_end - vector_begin;
	Point this_from_origin = *this - vector_begin;

	float det = vector_from_origin.x * this_from_origin.y - this_from_origin.x * vector_from_origin.y;

	if (det > 0) return LEFT;
	if (det < 0) return RIGHT;

	if (vector_from_origin.x * this_from_origin.x < 0 || vector_from_origin.y * this_from_origin.y) return BEHIND;
	if (Distance(ORIGIN, this_from_origin) > Distance(ORIGIN, vector_from_origin)) return AHEAD;

	return BETWEEN;
}

bool Point::is_in_or(Triangle& triangle) {
	if (get_orientation(triangle.p1, triangle.p2) != RIGHT) return false;
	if (get_orientation(triangle.p2, triangle.p3) != RIGHT) return false;
	if (get_orientation(triangle.p3, triangle.p1) != RIGHT) return false;

	return true;
}

bool Point::is_in(Triangle& triangle) {
	Triangle t1(triangle.p1, triangle.p2, *this);
	Triangle t2(triangle.p1, *this, triangle.p3);
	Triangle t3(*this, triangle.p2, triangle.p3);

	return triangle.area() == t1.area() + t2.area() + t3.area();
}

float Distance(Point& a, Point& b) {
	return sqrt((b.x - a.x) * ((b.x - a.x)) + (b.y - a.y) * ((b.y - a.y)));
}

// -------------------------------------------------------------------------------------

Triangle::Triangle() {
	name = new char[32];
	sprintf_s(name, 32, "Треугольник %d", number++);

	s12 = s13 = s23 = 0;
}
Triangle::Triangle(const Point& a, const Point& b, const Point& c) : p1(a), p2(b), p3(c) {
	name = new char[32];
	sprintf_s(name, 32, "Треугольник %d", number++);

	s12 = Distance(p1, p2);
	s13 = Distance(p1, p3);
	s23 = Distance(p2, p3);
}
Triangle::~Triangle() {
	delete[] name;
}

void Triangle::set_points(const Point& a, const Point& b, const Point& c) {
	p1 = a; p2 = b; p3 = c;

	s12 = Distance(p1, p2);
	s13 = Distance(p1, p3);
	s23 = Distance(p2, p3);
}

char* Triangle::get_name() {
	return name;
}

Triangle& Triangle::operator =(const Triangle& triangle) {
	p1 = triangle.p1;
	p2 = triangle.p2;
	p3 = triangle.p3;

	s12 = triangle.s12;
	s13 = triangle.s13;
	s23 = triangle.s23;

	return *this;
}

bool Triangle::operator <(Triangle& triangle) {
	return area() < triangle.area();
}
bool Triangle::operator >(Triangle& triangle) {
	return area() > triangle.area();
}
bool Triangle::operator ==(Triangle& triangle) {
	return area() == triangle.area();
}
bool Triangle::operator !=(Triangle& triangle) {
	return area() != triangle.area();
}

void Triangle::transform(Point dxdy, float angle) {
	if (dxdy.x != 0 || dxdy.y != 0) {
		p1 = p1 + dxdy;
		p2 = p2 + dxdy;
		p3 = p3 + dxdy;
	}
	if (angle) {
		p1.rotate(angle);
		p2.rotate(angle);
		p3.rotate(angle);
	}
}

float Triangle::area() {
	float x1 = p2.x - p1.x;
	float x2 = p3.x - p1.x;

	float y1 = p2.y - p1.y;
	float y2 = p3.y - p1.y;

	float S = 0.5f * (x1 * y2 - x2 * y1);

	return S >= 0 ? S : -S;
}

bool Triangle::is_in(Triangle& triangle) {
	return (p1.is_in(triangle) && p2.is_in(triangle) && p3.is_in(triangle));
}

void Triangle::print() {
	printf("%-15s: ", name);
	p1.print(' ');
	p2.print(' ');
	p3.print('\0');
	printf("   Площадь: %f", area());
	printf("\n");
}

void Triangle::scan(FILE* stream) {
	fscanf_s(stream, "%f%f%f%f%f%f", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);

	s12 = Distance(p1, p2);
	s13 = Distance(p1, p3);
	s23 = Distance(p2, p3);
}

int Triangle::number = 1;

Triangle& FindBiggestTriangle(Triangle* triangles, int size) {
	Triangle* biggest_triangle = triangles;

	for (int i = 1; i < size; i++) {
		if (triangles[i] > *biggest_triangle) {
			biggest_triangle = &triangles[i];
		}
	}

	return *biggest_triangle;
}