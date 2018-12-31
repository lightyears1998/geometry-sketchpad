#include "stdafx.h"
#include "Shape.h"

#include <cmath>


IMPLEMENT_SERIAL(Point, CObject, 1)
void Point::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // 储存过程
		ar.WriteClass(RUNTIME_CLASS(Point));
		ar << x << y;
	}
	else {  // 读取过程
		ar >> x >> y;
	}
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
double Segment::GetArea()
{
	return 0.0;  // 线的面积为0
}

double Segment::GetPerimeter()
{
	return hypot(head.x - tail.x, head.y - tail.y);
}

