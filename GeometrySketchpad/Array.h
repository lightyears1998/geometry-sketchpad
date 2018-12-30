#pragma once

#include "stdafx.h"

// Array
// ���ڴ�����������
// �����Զ����ݹ���
template <typename T>
class Array
{
public:
	Array<T>(size_t allocated = 10);
	virtual ~Array<T>();

	void Add(const T& nxt);
	T& GetAt(size_t index);

protected:
	void Enlarge();  // ��������

	size_t count = 0;  // ����Ķ��������
	size_t allocated;  // �ѷ���Ŀռ�
	T * arr;  // �������������
};

template<typename T>
inline Array<T>::Array(size_t allocated)
{
	allocated = max(32, allocated);  // Ϊ����Ƶ��������������Ԥ����Ŀռ�����Ϊ32
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
	size_t allocated = allocated / 2 * 3;  // ��Ԥ����Ŀռ�����Ϊԭ���Ķ���֮��
	T * nxt = new T[allocated];

	for (size_t i = 0; i < count; ++i) nxt[i] = arr[i];
	delete arr; arr = nxt;
}
