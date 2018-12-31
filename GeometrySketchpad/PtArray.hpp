#pragma once

#include "stdafx.h"

// PtArray
// �������ָ��Ķ�̬����
// �ڴ���������ʱ��ָ��ָ��Ķ��󽫱�ʹ��delete�ͷſռ�
template <typename T>
class PtArray : public CObject
{
public:
	PtArray(size_t allocated = 10);
	virtual ~PtArray();

	// T���������
	size_t GetCount() const;

	// ȡ������λ�õ�T����ָ��
	T * GetAt(size_t) const;

	// ���µ�T����ָ���������
	void Add(T * pt);

	// �Ƴ�ָ��λ��T����
	void Remove(size_t index);

	// �������
	void Empty();

protected:
	T ** arr;  // ָ�򴢴�T����ָ���������ָ��
	size_t count = 0;  // �Ѵ������ָ�������
	size_t allocated;  // �ѷ�������ڴ������ָ��������ռ�

	// ����T����ָ�봢����������
	void Enlarge();
};

template <typename T>
inline PtArray<T>::PtArray(size_t allocated)
{
	allocated = max(size_t(32), allocated);  // Ϊ����Ƶ��������������Ԥ����Ŀռ�����Ϊ32
	this->allocated = allocated;
	arr = new T *[allocated];
}

template <typename T>
inline void PtArray<T>::Enlarge()
{
	allocated = allocated / 2 * 3;  // ��Ԥ����Ŀռ�����Ϊԭ���Ķ���֮��
	T ** nxt = new T *[allocated];

	for (size_t i = 0; i < count; ++i) nxt[i] = arr[i];  // ��ԭ����λ���е�������������´���λ��
	delete arr; arr = nxt;  // �ͷžɴ���λ�õĿռ�
}


template <typename T>
inline PtArray<T>::~PtArray()
{
	for (size_t i = 0; i < count; ++i) {
		delete arr[i];  // �ͷ�T����
	}
	delete[] arr;  // �ͷ������ռ�
}


template <typename T>
inline size_t PtArray<T>::GetCount() const
{
	return count;
}

template <typename T>
inline T * PtArray<T>::GetAt(size_t index) const
{
	if (index >= 0 && index < count)  // ���߽�����
		return arr[index];
	return nullptr;
}

template <typename T>
inline void PtArray<T>::Add(T * pt)
{
	if (count + 1 == allocated) Enlarge();  // �����ռ佫��ʱ���������ռ�
	arr[count] = pt; ++count;  // ������ָ��װ������
}

template <typename T>
inline void PtArray<T>::Remove(size_t index)
{
	if (index >= 0 && index < count) {
		delete arr[index];  // �ͷű��Ƴ�����Ŀռ�
		for (size_t i = index; i < count - 1; ++i) {
			arr[i] = arr[i + 1];  // �����Ƴ���������λ�ú��ָ������ǰ��
		}
		--count;  // ���ж����������һ
	}
}

template <typename T>
inline void PtArray<T>::Empty()
{
	for (size_t i = GetCount(); i; --i)
		delete arr[i - 1];
	count = 0;
}
