#pragma once

#include "stdafx.h"
#include "Shape.h"
#include "Point.h"
#include "PtArray.hpp"

// ¶à±ßÐÎ
class PolygonShape : public Shape
{
public:
	PtArray<Point> vertexs;

	PolygonShape() : vertexs() {};
	// PolygonShape(const PtArray<Point> & arr) : vertexs(arr) {};

	DECLARE_SERIAL(PolygonShape)
	virtual void Serialize(CArchive &ar);

	virtual Shape * Clone() const;

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
