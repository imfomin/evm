#include <iostream>
#include <math.h>

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

class Triangle;

class Point {
private:
	float x;
	float y;

	enum Orientation;
	Orientation get_orientation(Point& vector_begin, Point& vector_end);
public:
	Point(float _x, float _y);

	void set_x(float _x);
	void set_y(float _y);
	void set_coords(float _x, float _y);

	Point operator +(const Point& point) const;
	Point operator -(const Point& point) const;

	void rotate(float angle);

	void print(char end = '\n');
	void scan(FILE* stream = stdin);

	bool is_in_or(Triangle& _triangle);
	bool is_in(Triangle& _triangle);

	friend float Distance(Point& a, Point& b);
	friend class Triangle;
};

float Distance(Point& a, Point& b);

class Triangle {
private:
	char* name;
	Point p1, p2, p3;
	float s12, s13, s23;
public:
	static int number;

	Triangle();
	Triangle(const Point& a, const Point& b, const Point& c);
	~Triangle();

	Triangle& operator =(const Triangle& triangle);
	bool operator <(Triangle& triangle);
	bool operator >(Triangle& triangle);
	bool operator ==(Triangle& triangle);
	bool operator !=(Triangle& triangle);

	void set_points(const Point& a, const Point& b, const Point& c);

	char* get_name();

	void transform(Point dxdy, float angle = 0);
	float area();

	bool is_in(Triangle& triangle);

	void print();
	void scan(FILE* stream = stdin);

	friend class Point;
};

Triangle& FindBiggestTriangle(Triangle* triangles, int size);

#endif // TRIANGLE_HPP