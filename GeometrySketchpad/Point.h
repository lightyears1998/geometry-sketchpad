#pragma once

#include "Shape.h"

// µã
class Point : public Shape
{
public:
	double x, y;

	Point() : x(0), y(0) {};
	Point(double x, double y) : x(x), y(y) {};
	Point(const Point & pt) : x(pt.x), y(pt.y) {};
	Point(const CPoint & pt) : x(pt.x), y(pt.y) {};

	Point& operator =(const Point & pt);

	CPoint ToCPoint();

	DECLARE_SERIAL(Point)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
