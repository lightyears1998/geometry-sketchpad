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
	Shape ** arr;  // 指向储存Shape对象指针的容器的指针
	size_t count = 0;  // 已储存对象指针的数量
	size_t allocated;  // 已分配可用于储存对象指针的容器空间

	void Enlarge();  // 扩大Shape对象指针储存器的容量
};
