#pragma once

#include "stdafx.h"

// PtArray
// 管理对象指针的动态数组
// 在此数组析构时，指针指向的对象将被使用delete释放空间
template <typename T>
class PtArray : public CObject
{
public:
	PtArray(size_t allocated = 10);
	virtual ~PtArray();

	// T对象的数量
	size_t GetCount() const;

	// 取得索引位置的T对象指针
	T * GetAt(size_t) const;

	// 将新的T对象指针加入数组
	void Add(T * pt);

	// 移除指定位置T对象
	void Remove(size_t index);

	// 清空容器
	void Empty();

protected:
	T ** arr;  // 指向储存T对象指针的容器的指针
	size_t count = 0;  // 已储存对象指针的数量
	size_t allocated;  // 已分配可用于储存对象指针的容器空间

	// 扩大T对象指针储存器的容量
	void Enlarge();
};

template <typename T>
inline PtArray<T>::PtArray(size_t allocated)
{
	allocated = max(size_t(32), allocated);  // 为避免频繁地扩大容量，预分配的空间至少为32
	this->allocated = allocated;
	arr = new T *[allocated];
}

template <typename T>
inline void PtArray<T>::Enlarge()
{
	allocated = allocated / 2 * 3;  // 将预分配的空间扩大为原来的二分之三
	T ** nxt = new T *[allocated];

	for (size_t i = 0; i < count; ++i) nxt[i] = arr[i];  // 将原储存位置中的内容逐项复制至新储存位置
	delete arr; arr = nxt;  // 释放旧储存位置的空间
}


template <typename T>
inline PtArray<T>::~PtArray()
{
	for (size_t i = 0; i < count; ++i) {
		delete arr[i];  // 释放T对象
	}
	delete[] arr;  // 释放容器空间
}


template <typename T>
inline size_t PtArray<T>::GetCount() const
{
	return count;
}

template <typename T>
inline T * PtArray<T>::GetAt(size_t index) const
{
	if (index >= 0 && index < count)  // 检查边界条件
		return arr[index];
	return nullptr;
}

template <typename T>
inline void PtArray<T>::Add(T * pt)
{
	if (count + 1 == allocated) Enlarge();  // 容器空间将满时扩大容器空间
	arr[count] = pt; ++count;  // 将对象指针装入容器
}

template <typename T>
inline void PtArray<T>::Remove(size_t index)
{
	if (index >= 0 && index < count) {
		delete arr[index];  // 释放被移除对象的空间
		for (size_t i = index; i < count - 1; ++i) {
			arr[i] = arr[i + 1];  // 将被移除对象索引位置后的指针逐项前移
		}
		--count;  // 持有对象的总数减一
	}
}

template <typename T>
inline void PtArray<T>::Empty()
{
	for (size_t i = GetCount(); i; --i)
		delete arr[i - 1];
	count = 0;
}
