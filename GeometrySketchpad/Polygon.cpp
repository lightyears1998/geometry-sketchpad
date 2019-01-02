#include "stdafx.h"
#include "Polygon.h"
#include "Point.h"


IMPLEMENT_SERIAL(ArbitraryPolygon, CObject, 1)
void ArbitraryPolygon::Serialize(CArchive & ar)
{
	Shape::Serialize(ar);

	if (ar.IsStoring()) {  // 储存过程
		size_t count = vertexs.GetCount();
		ar << count;
		for (size_t i = 0; i < count; ++i) {
			vertexs.GetAt(i).Serialize(ar);
		}
	}
	else {  // 读取过程
		vertexs.Serialize(ar);
		size_t count; ar >> count;
		for (size_t i = 0; i < count; ++i) {
			Point pt; pt.Serialize(ar);
			vertexs.Add(pt);
		}
	}
}

void ArbitraryPolygon::MakeRectangle(const Point & v1, const Point & v2)
{
	vertexs.Clear();

	Point a(v1), b(v1.x, v2.y), c(v2), d(v2.x, v1.y);
	vertexs.Add(a), vertexs.Add(b), vertexs.Add(c), vertexs.Add(d);

	Identifier = TEXT("矩形");
}


void ArbitraryPolygon::MakeTriangle(const Point & a, const Point & b, const Point & c)
{
	vertexs.Clear();  // 清空原有顶点

	vertexs.Add(a), vertexs.Add(b), vertexs.Add(c);

	Identifier = TEXT("三角形");
}


void ArbitraryPolygon::MakeParallelogramFromPoints(const Point & a, const Point & b, const Point & c)
{
	vertexs.Clear();  // 清空原有顶点

	const Point d(a.x + c.x - b.x, a.y + c.y - b.y);  // 计算出第四个顶点的位置
	vertexs.Add(a), vertexs.Add(b), vertexs.Add(c), vertexs.Add(d);

	Identifier = TEXT("平行四边形");
}


void ArbitraryPolygon::OnDraw(CDC * pDC)
{
	CPen black_pen(PS_SOLID, 3, RGB(0, 0, 0)), red_pen(PS_SOLID, 3, RGB(237, 85, 106));
	CPen * old_pen = pDC->SelectObject(IsSelected ? &red_pen : &black_pen);

	pDC->MoveTo((vertexs.GetAt(0).ToCPoint()));
	for (size_t i = 1; i < vertexs.GetCount(); ++i) {
		pDC->LineTo(vertexs.GetAt(i).ToCPoint());
	}
	pDC->LineTo(vertexs.GetAt(0).ToCPoint());

	pDC->SelectObject(old_pen);
}


double ArbitraryPolygon::GetArea()
{
	return 0.0;
}


double ArbitraryPolygon::GetPerimeter()
{
	return 0.0;
}


