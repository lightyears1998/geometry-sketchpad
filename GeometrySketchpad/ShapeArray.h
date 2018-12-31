#pragma once

#include "Shape.h"


// ShapeArray
// ����Shape����ָ��Ķ�̬����
// �ڴ���������ʱ��Shapeָ��ָ��Ķ��󽫱�deleteɾ��
class ShapeArray : public CObject
{
public:
	ShapeArray(size_t allocated = 10);
	ShapeArray(const ShapeArray& arr);
	virtual ~ShapeArray();

	DECLARE_SERIAL(ShapeArray);
	virtual void Serialize(CArchive &ar);

	// Shape���������
	size_t GetCount() const;

	// ȡ������λ�õ�Shape����ָ��
	Shape * GetAt(size_t) const;

	// ���µ�Shape����ָ���������
	void Add(Shape * shape);

	// �Ƴ�ָ��λ��Shape����
	void Remove(size_t index);

protected:
	Shape ** arr;  // ָ�򴢴�Shape����ָ���������ָ��
	size_t count = 0;  // �Ѵ������ָ�������
	size_t allocated;  // �ѷ�������ڴ������ָ��������ռ�

	void Enlarge();  // ����Shape����ָ�봢����������
};
