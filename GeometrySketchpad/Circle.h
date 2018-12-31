#pragma once

#include "Shape.h"
#include "Point.h"

// Բ
class Circle : public Shape
{
public:
	Point center;  // Բ��
	double radius;  // �뾶

	Circle() : center(0, 0), radius(0) {};
	Circle(Point center, double radius) : center(center), radius(radius) {};

	DECLARE_SERIAL(Circle)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};