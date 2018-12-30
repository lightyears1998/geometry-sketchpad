#include "stdafx.h"
#include "ShapeArray.h"

#include <algorithm>

using namespace std;


ShapeArray::ShapeArray(size_t allocated)
{
	allocated = max(size_t(32), allocated);  // 为避免频繁地扩大容量，预分配的空间至少为32
	this->allocated = allocated;
	arr = new Shape *[allocated];
}


IMPLEMENT_SERIAL(ShapeArray, CObject, 1);
void ShapeArray::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring()) {  // 储存过程
		ar << count;
		for (size_t i = 0; i < count; ++i) {
			arr[i]->Serialize(ar);
		}
	}
	else {  // 读取过程
		ar >> count;
		for (size_t i = 0; i < count; ++i) {
			arr[i]->Serialize(ar);
		}
	}
}

void ShapeArray::Enlarge()
{
	allocated = allocated / 2 * 3;  // 将预分配的空间扩大为原来的二分之三
	Shape ** nxt = new Shape *[allocated];

	for (size_t i = 0; i < count; ++i) nxt[i] = arr[i];  // 将原储存位置中的内容逐项复制至新储存位置
	delete arr; arr = nxt;  // 释放旧储存位置的空间
}


ShapeArray::~ShapeArray()
{
	for (size_t i = 0; i < count; ++i) {
		delete arr[i];  // 释放Shape对象
	}
	delete arr;  // 释放容器空间
}



Shape * ShapeArray::GetAt(size_t)
{
	return nullptr;
}
