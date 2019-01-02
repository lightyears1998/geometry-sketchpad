#include "stdafx.h"
#include "Shape.h"

void Shape::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // �������
		ar << Identifier << IsSelected;
	}
	else {  // ��ȡ����
		ar >> Identifier >> IsSelected;
	}
}
