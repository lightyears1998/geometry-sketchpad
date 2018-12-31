#pragma once

#include "stdafx.h"
#include "Shape.h"
#include "Point.h"

// 线段
class Segment : public Shape
{
public:
	Point head, tail;  // 线段的起点和终点

	Segment() = default;
	Segment(const Point &head, const Point &tail) : head(head), tail(tail) {};

	DECLARE_SERIAL(Segment)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
