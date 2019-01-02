#include "stdafx.h"
#include "Segment.h"

IMPLEMENT_SERIAL(Segment, CObject, 1)
void Segment::Serialize(CArchive & ar)
{
	Shape::Serialize(ar);

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
	CPen black_pen(PS_SOLID, 3, RGB(0, 0, 0)), red_pen(PS_SOLID, 3, RGB(237, 85, 106));
	CPen * old_pen = pDC->SelectObject(IsSelected ? &red_pen : &black_pen);

	pDC->MoveTo(head.ToCPoint());
	pDC->LineTo(tail.ToCPoint());

	pDC->SelectObject(old_pen);
}

double Segment::GetArea()
{
	return 0.0;  // 线的面积为0
}

double Segment::GetPerimeter()
{
	return hypot(head.x - tail.x, head.y - tail.y);
}
