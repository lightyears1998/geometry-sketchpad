#pragma once

#include "Shape.h"


// ShapeArray
class ShapeArray : public CObject
{
public:
	ShapeArray(size_t allocated = 10);
	virtual ~ShapeArray();

	DECLARE_SERIAL(ShapeArray);
	virtual void Serialize(CArchive &ar);

	Shape * GetAt(size_t);
	void Add(Shape * shape);

protected:
	Shape ** arr;  // ָ�򴢴�Shape����ָ���������ָ��
	size_t count = 0;  // �Ѵ������ָ�������
	size_t allocated;  // �ѷ�������ڴ������ָ��������ռ�

	void Enlarge();  // ����Shape����ָ�봢����������
};
