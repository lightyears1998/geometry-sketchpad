#include "stdafx.h"
#include "Point.h"

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

Point & Point::operator=(const Point & pt)
{
	if (this == &pt) {
		return *this;
	}

	this->x = pt.x;
	this->y = pt.y;
	return *this;
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
