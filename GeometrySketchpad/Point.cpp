#include "stdafx.h"
#include "Point.h"

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
	CBrush black_brush(RGB(0, 0, 0)), red_brush(RGB(237, 85, 106));
	CBrush * old_brush = pDC->SelectObject(IsSelected ? &red_brush : &black_brush);
	
	pDC->Ellipse(x-5, y-5, x+5, y+5);  // ���뾶5�߼���λ��Բ��ɫ

	pDC->SelectObject(old_brush);
}

double Point::GetArea()
{
	return 0.0;  // ������Ϊ0
}

double Point::GetPerimeter()
{
	return 0.0;  // ����ܳ�Ϊ0
}
