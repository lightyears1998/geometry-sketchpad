#pragma once

#include "Shape.h"

// 点
class Point : public Shape
{
public:
	double x, y;

	Point() : x(0), y(0) {
		Identifier = TEXT("点");
	};
	Point(double x, double y) : x(x), y(y) {
		Identifier = TEXT("点");
	};
	Point(const Point & pt) : x(pt.x), y(pt.y) {
		Identifier = pt.Identifier;
	};
	Point(const CPoint & pt) : x(pt.x), y(pt.y) {
		Identifier = TEXT("点");
	};

	Point& operator =(const Point & pt);

	CPoint ToCPoint();

	DECLARE_SERIAL(Point)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
