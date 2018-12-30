#pragma once

#include "stdafx.h"

// Array
// 用于储存对象的数组
// 具有自动扩容功能
template <typename T>
class Array
{
public:
	Array<T>(size_t allocated = 10);
	virtual ~Array<T>();

	void Add(const T& nxt);
	T& GetAt(size_t index);

protected:
	void Enlarge();  // 扩大容量

	size_t count = 0;  // 储存的对象的数量
	size_t allocated;  // 已分配的空间
	T * arr;  // 储存数组的容器
};

template<typename T>
inline Array<T>::Array(size_t allocated)
{
	allocated = max(32, allocated);  // 为避免频繁地扩大容量，预分配的空间至少为32
	this->allocated = allocated;
	arr = new T[allocated];
}

template<typename T>
inline Array<T>::~Array()
{
	for (size_t i = 0; i < count; ++i) {
		delete arr[i];
	}
	delete arr;
}

template<typename T>
inline void Array<T>::Add(const T & nxt)
{

}

template<typename T>
inline T& Array<T>::GetAt(size_t index)
{
	return T();
}

template<typename T>
inline void Array<T>::Enlarge()
{
	size_t allocated = allocated / 2 * 3;  // 将预分配的空间扩大为原来的二分之三
	T * nxt = new T[allocated];

	for (size_t i = 0; i < count; ++i) nxt[i] = arr[i];
	delete arr; arr = nxt;
}
