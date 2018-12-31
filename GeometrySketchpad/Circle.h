#pragma once

#include "Shape.h"
#include "Point.h"

// Ô²
class Circle : public Shape
{
public:
	Point center;  // Ô²ÐÄ
	double radius;  // °ë¾¶

	Circle() : center(0, 0), radius(0) {};
	Circle(Point center, double radius) : center(center), radius(radius) {};

	DECLARE_SERIAL(Circle)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};