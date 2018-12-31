#include "stdafx.h"
#include "ShapeArray.h"

#include <algorithm>

using namespace std;


ShapeArray::ShapeArray(size_t allocated)
{
	allocated = max(size_t(32), allocated);  // Ϊ����Ƶ��������������Ԥ����Ŀռ�����Ϊ32
	this->allocated = allocated;
	arr = new Shape *[allocated];
}


IMPLEMENT_SERIAL(ShapeArray, CObject, 1)
void ShapeArray::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // �������
		ar << count;
		for (size_t i = 0; i < count; ++i) {
			arr[i]->Serialize(ar);
		}
	}
	else {  // ��ȡ����
		size_t count;  ar >> count;
		for (size_t i = 0; i < count; ++i) {
			Shape * shape = (Shape *)ar.ReadObject(nullptr);
			Add(shape);
		}
	}
}


void ShapeArray::Enlarge()
{
	allocated = allocated / 2 * 3;  // ��Ԥ����Ŀռ�����Ϊԭ���Ķ���֮��
	Shape ** nxt = new Shape *[allocated];

	for (size_t i = 0; i < count; ++i) nxt[i] = arr[i];  // ��ԭ����λ���е�������������´���λ��
	delete arr; arr = nxt;  // �ͷžɴ���λ�õĿռ�
}


ShapeArray::~ShapeArray()
{
	for (size_t i = 0; i < count; ++i) {
		delete arr[i];  // �ͷ�Shape����
	}
	delete arr;  // �ͷ������ռ�
}


size_t ShapeArray::GetCount()
{
	return count;
}

Shape * ShapeArray::GetAt(size_t index)
{
	if (index >= 0 && index < count)  // ���߽�����
		return arr[index];
	return nullptr;
}


void ShapeArray::Add(Shape * shape)
{
	if (count + 1 == allocated) Enlarge();  // �����ռ佫��ʱ���������ռ�
	arr[count] = shape; ++count;  // ������ָ��װ������
}

void ShapeArray::Remove(size_t index)
{
	if (index >= 0 && index < count) {
		delete arr[index];  // �ͷű��Ƴ�����Ŀռ�
		for (size_t i = index; i < count - 1; ++i) {
			arr[i] = arr[i + 1];  // �����Ƴ���������λ�ú��ָ������ǰ��
		}
		--count;  // ���ж����������һ
	}
}
