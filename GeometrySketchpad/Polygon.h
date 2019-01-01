#pragma once

#include "stdafx.h"
#include "Shape.h"
#include "Point.h"
#include "ObArray.hpp"

// 多边形
class ArbitraryPolygon : public Shape
{
public:
	ObArray<Point> vertexs;

	ArbitraryPolygon() : vertexs() {};
	ArbitraryPolygon(const ObArray<Point> & arr) : vertexs(arr) {};

	DECLARE_SERIAL(ArbitraryPolygon)
	virtual void Serialize(CArchive &ar);

	// 通过对角线上的两个顶点创建矩形
	void MakeRectangle(const Point& v1, const Point& v2);

	// 通过三个顶点创建三角形
	void MakeTriangle(const Point& a, const Point& b, const Point & c);

	// 通过三个顶点创建平行四边形
	void MakeParallelogramFromPoints(const Point& a, const Point& b, const Point& c);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
