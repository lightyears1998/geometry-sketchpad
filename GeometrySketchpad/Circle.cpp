#include "stdafx.h"
#include "Circle.h"

#include <cmath>

IMPLEMENT_SERIAL(Circle, CObject, 1)
void Circle::Serialize(CArchive & ar)
{
	Shape::Serialize(ar);

	if (ar.IsStoring()) {
		center.Serialize(ar);
		ar << radius;
	}
	else {
		center.Serialize(ar);
		ar >> radius;
	}
}

void Circle::OnDraw(CDC * pDC)
{
	CPen black_pen(PS_SOLID, 3, RGB(0, 0, 0)), red_pen(PS_SOLID, 3, RGB(237, 85, 106));
	CPen * old_pen = pDC->SelectObject(IsSelected ? &red_pen : &black_pen);

	int x1 = int(center.x - radius), y1 = int(center.y - radius);  // 圆外接矩形左上角
	int x2 = int(center.x + radius), y2 = int(center.y + radius);  // 圆外界矩形右下角
	int x3 = int(center.x + radius), y3 = int(center.y);  // 绘制起点
	int x4 = int(center.x + radius), y4 = int(center.y);  // 绘制终点
	pDC->Arc(x1, y1, x2, y2, x3, y3, x4, y4);

	pDC->SelectObject(old_pen);
}

double Circle::GetArea()
{
	const double PI = acos(-1);
	return PI * radius * radius;
}

double Circle::GetPerimeter()
{
	const double PI = acos(-1);
	return 2 * PI * radius;
}
