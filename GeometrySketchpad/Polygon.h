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

	ArbitraryPolygon() : vertexs() {
		Identifier = TEXT("多边形");
	};
	ArbitraryPolygon(const ObArray<Point> & arr) : vertexs(arr) {
		switch (arr.GetCount()) {
		case size_t(1):
			Identifier = TEXT("点"); break;
		case size_t(2):
			Identifier = TEXT("线段"); break;
		case size_t(3):
			Identifier = TEXT("三角形"); break;
		case size_t(4):
			Identifier = TEXT("四边形"); break;
		default:
			Identifier = TEXT("多边形");
		}
	};

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
