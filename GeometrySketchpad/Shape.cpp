#include "stdafx.h"
#include "Shape.h"

#include <cmath>


IMPLEMENT_SERIAL(Point, CObject, 1)
void Point::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // �������
		ar << x << y;
	}
	else {  // ��ȡ����
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
	return 0.0;  // ������Ϊ0
}

double Point::GetPerimeter()
{
	return 0.0;  // ����ܳ�Ϊ0
}


IMPLEMENT_SERIAL(Segment, CObject, 1)
void Segment::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // �洢����
		head.Serialize(ar);
		tail.Serialize(ar);
	}
	else {  // ��ȡ����
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
	return 0.0;  // �ߵ����Ϊ0
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
