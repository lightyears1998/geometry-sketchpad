#pragma once

#include "stdafx.h"
#include "Shape.h"
#include "Point.h"

// �߶�
class Segment : public Shape
{
public:
	Point head, tail;  // �߶ε������յ�

	Segment() {
		Identifier = TEXT("�߶�");
	};
	Segment(const Point &head, const Point &tail) : head(head), tail(tail) {
		Identifier = TEXT("�߶�");
	};

	DECLARE_SERIAL(Segment)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};
