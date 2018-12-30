#include "stdafx.h"
#include "Shape.h"

#include <cmath>

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

double Point::GetArea()
{
	return 0.0;  // ������Ϊ0
}

double Point::GetPerimeter()
{
	return 0.0;  // ����ܲ�Ϊ0
}

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
double Segment::GetArea()
{
	return 0.0;  // �ߵ����Ϊ0
}

double Segment::GetPerimeter()
{
	return hypot(head.x - tail.x, head.y - tail.y);
}

