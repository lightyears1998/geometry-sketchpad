#include "stdafx.h"
#include "Shape.h"

#include <cmath>


IMPLEMENT_SERIAL(Point, CObject, 1)
void Point::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // 储存过程
		ar << x << y;
	}
	else {  // 读取过程
		ar >> x >> y;
	}
}

CPoint Point::ToCPoint()
{
	return CPoint(int(x), int(y));
}

void Point::OnDraw(CDC* pDC)
{
	pDC->SetPixelV(int(x), int(y), RGB(0, 0, 0));
}

double Point::GetArea()
{
	return 0.0;  // 点的面积为0
}

double Point::GetPerimeter()
{
	return 0.0;  // 点的周长为0
}


IMPLEMENT_SERIAL(Segment, CObject, 1)
void Segment::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // 存储过程
		head.Serialize(ar);
		tail.Serialize(ar);
	}
	else {  // 读取过程
		head.Serialize(ar);
		tail.Serialize(ar);
	}
}


void Segment::OnDraw(CDC * pDC)
{
	pDC->MoveTo(head.ToCPoint());
	pDC->LineTo(tail.ToCPoint());
}

double Segment::GetArea()
{
	return 0.0;  // 线的面积为0
}

double Segment::GetPerimeter()
{
	return hypot(head.x - tail.x, head.y - tail.y);
}

void Circle::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {
		// ar.WriteClass(RUMTIME_CLASS()) ar.WriteClass(RUMTIME_CLASS());
	}
	else {

	}
}
