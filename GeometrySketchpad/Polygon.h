#pragma once

#include "stdafx.h"
#include "Shape.h"
#include "ShapeArray.h"


// ¶à±ßÐÎ
class PolygonShape : public Shape
{
public:
	ShapeArray vertexs;

	PolygonShape() : vertexs() {};
	PolygonShape(const ShapeArray & arr) : vertexs(arr) {};

	DECLARE_SERIAL(PolygonShape)
	virtual void Serialize(CArchive &ar);

	virtual Shape * Clone() const;

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
