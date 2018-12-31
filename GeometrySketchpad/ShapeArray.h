#pragma once

#include "Shape.h"


// ShapeArray
// 管理Shape对象指针的动态数组
// 在此数组析构时，Shape指针指向的对象将被delete删除
class ShapeArray : public CObject
{
public:
	ShapeArray(size_t allocated = 10);
	ShapeArray(const ShapeArray& arr);
	virtual ~ShapeArray();

	DECLARE_SERIAL(ShapeArray);
	virtual void Serialize(CArchive &ar);

	// Shape对象的数量
	size_t GetCount() const;

	// 取得索引位置的Shape对象指针
	Shape * GetAt(size_t) const;

	// 将新的Shape对象指针加入数组
	void Add(Shape * shape);

	// 移除指定位置Shape对象
	void Remove(size_t index);

protected:
	Shape ** arr;  // 指向储存Shape对象指针的容器的指针
	size_t count = 0;  // 已储存对象指针的数量
	size_t allocated;  // 已分配可用于储存对象指针的容器空间

	void Enlarge();  // 扩大Shape对象指针储存器的容量
};
