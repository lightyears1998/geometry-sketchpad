#pragma once

#include "stdafx.h"
#include "Shape.h"
#include "Point.h"
#include "ObArray.hpp"

// �����
class ArbitraryPolygon : public Shape
{
public:
	ObArray<Point> vertexs;

	ArbitraryPolygon() : vertexs() {
		Identifier = TEXT("�����");
	};
	ArbitraryPolygon(const ObArray<Point> & arr) : vertexs(arr) {
		switch (arr.GetCount()) {
		case size_t(1):
			Identifier = TEXT("��"); break;
		case size_t(2):
			Identifier = TEXT("�߶�"); break;
		case size_t(3):
			Identifier = TEXT("������"); break;
		case size_t(4):
			Identifier = TEXT("�ı���"); break;
		default:
			Identifier = TEXT("�����");
		}
	};

	DECLARE_SERIAL(ArbitraryPolygon)
	virtual void Serialize(CArchive &ar);

	// ͨ���Խ����ϵ��������㴴������
	void MakeRectangle(const Point& v1, const Point& v2);

	// ͨ���������㴴��������
	void MakeTriangle(const Point& a, const Point& b, const Point & c);

	// ͨ���������㴴��ƽ���ı���
	void MakeParallelogramFromPoints(const Point& a, const Point& b, const Point& c);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
