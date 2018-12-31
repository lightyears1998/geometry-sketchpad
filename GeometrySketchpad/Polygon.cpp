#include "stdafx.h"
#include "Polygon.h"
#include "Point.h"


IMPLEMENT_SERIAL(PolygonShape, CObject, 1)
void PolygonShape::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

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


void PolygonShape::OnDraw(CDC * pDC)
{
	pDC->MoveTo((vertexs.GetAt(0).ToCPoint()));
	for (size_t i = 1; i < vertexs.GetCount(); ++i) {
		pDC->LineTo(vertexs.GetAt(i).ToCPoint());
	}
	pDC->LineTo(vertexs.GetAt(0).ToCPoint());
}


double PolygonShape::GetArea()
{
	return 0.0;
}


double PolygonShape::GetPerimeter()
{
	return 0.0;
}


