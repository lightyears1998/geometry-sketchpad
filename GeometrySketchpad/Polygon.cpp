#include "stdafx.h"
#include "Polygon.h"
#include "Point.h"


IMPLEMENT_SERIAL(PolygonShape, CObject, 1)
void PolygonShape::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // 储存过程
		vertexs.Serialize(ar);
	}
	else {  // 读取过程
		vertexs.Serialize(ar);
	}
}


Shape * PolygonShape::Clone() const
{
	return new PolygonShape(vertexs);
}


void PolygonShape::OnDraw(CDC * pDC)
{
	// 不考虑退化成点、线段的情况
	pDC->MoveTo(((Point *)(vertexs.GetAt(0)))->ToCPoint());
	for (size_t i = 1; i < vertexs.GetCount(); ++i) {
		pDC->LineTo(((Point *)(vertexs.GetAt(i)))->ToCPoint());
	}
	pDC->LineTo(((Point *)(vertexs.GetAt(0)))->ToCPoint());
}


double PolygonShape::GetArea()
{
	return 0.0;
}


double PolygonShape::GetPerimeter()
{
	return 0.0;
}


