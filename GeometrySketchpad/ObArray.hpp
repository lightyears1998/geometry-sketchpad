#pragma once

#include "stdafx.h"

// ObArray
// 储存对象的动态数组
template <typename T>
class ObArray : public CObject
{
public:
	ObArray(size_t allocated = 32);
	ObArray(const ObArray &src);
	virtual ~ObArray();

	// T对象的数量
	size_t GetCount() const;

	// 取得索引位置的对象
	T& GetAt(size_t) const;

	// 将新的T对象加入数组
	void Add(const T &pt);

	// 移除指定位置T对象
	void Remove(size_t index);

	// 清空容器
	void Empty();

protected:
	T * arr;  // 指向储存T对象的容器的指针
	size_t count = 0;  // 已储存对象的数量
	size_t allocated;  // 已分配可用于储存对象的容器空间

	// 扩大T对象指针储存器的容量
	void Enlarge();
};

template <typename T>
inline ObArray<T>::ObArray(size_t allocated)
{
	allocated = max(size_t(32), allocated);  // 为避免频繁地扩大容量，预分配的空间至少为32
	this->allocated = allocated;
	arr = new T[allocated];
}

template<typename T>
inline ObArray<T>::ObArray(const ObArray & src)
{
	new (this)ObArray();
	for (size_t i = 0; i < src.GetCount(); ++i) {
		Add(src.GetAt(i));
	}
}

template <typename T>
inline void ObArray<T>::Enlarge()
{
	allocated = allocated / 2 * 3;  // 将预分配的空间扩大为原来的二分之三
	T * nxt = new T [allocated];

	for (size_t i = 0; i < count; ++i) nxt[i] = arr[i];  // 将原储存位置中的内容逐项复制至新储存位置
	delete arr; arr = nxt;  // 释放旧储存位置的空间
}


template <typename T>
inline ObArray<T>::~ObArray()
{
	delete[] arr;  // 释放容器空间
}

template <typename T>
inline size_t ObArray<T>::GetCount() const
{
	return count;
}

template <typename T>
inline T& ObArray<T>::GetAt(size_t index) const
{
	if (index >= 0 && index < count)  // 检查边界条件
		return arr[index];
	AfxThrowInvalidArgException();  // 数组下标越界
}

template <typename T>
inline void ObArray<T>::Add(const T &pt)
{
	if (count + 1 == allocated) Enlarge();  // 容器空间将满时扩大容器空间
	arr[count] = pt; ++count;  // 将对象装入容器
}

template <typename T>
inline void ObArray<T>::Remove(size_t index)
{
	if (index >= 0 && index < count) {
		for (size_t i = index; i < count - 1; ++i) {
			arr[i] = arr[i + 1];  // 将被移除对象索引位置后的指针逐项前移
		}
		--count;  // 持有对象的总数减一
	}
}

template <typename T>
inline void ObArray<T>::Empty()
{
	count = 0;
}
