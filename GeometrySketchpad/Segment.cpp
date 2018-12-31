#include "stdafx.h"
#include "Segment.h"

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
