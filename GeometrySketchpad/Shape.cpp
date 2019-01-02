#include "stdafx.h"
#include "Shape.h"

void Shape::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // 储存过程
		ar << Identifier << IsSelected;
	}
	else {  // 读取过程
		ar >> Identifier >> IsSelected;
	}
}
