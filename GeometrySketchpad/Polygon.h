#pragma once

#include "stdafx.h"
#include "Shape.h"
#include "Point.h"
#include "ObArray.hpp"

// ¶à±ßÐÎ
class PolygonShape : public Shape
{
public:
	ObArray<Point> vertexs;

	PolygonShape() : vertexs() {};
	PolygonShape(const ObArray<Point> & arr) : vertexs(arr) {};

	DECLARE_SERIAL(PolygonShape)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
