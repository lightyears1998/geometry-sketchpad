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

CPoint Point::ToCPoint()
{
	return CPoint(int(x), int(y));
}

Shape * Point::Clone() const
{
	return new Point(x, y);
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
