#pragma once

#include "stdafx.h"

// ObArray
// �������Ķ�̬����
template <typename T>
class ObArray : public CObject
{
public:
	ObArray(size_t allocated = 32);
	ObArray(const ObArray &src);
	virtual ~ObArray();

	// T���������
	size_t GetCount() const;

	// ȡ������λ�õĶ���
	T& GetAt(size_t) const;

	// ���µ�T�����������
	void Add(const T &pt);

	// �Ƴ�ָ��λ��T����
	void Remove(size_t index);

	// �������
	void Empty();

protected:
	T * arr;  // ָ�򴢴�T�����������ָ��
	size_t count = 0;  // �Ѵ�����������
	size_t allocated;  // �ѷ�������ڴ������������ռ�

	// ����T����ָ�봢����������
	void Enlarge();
};

template <typename T>
inline ObArray<T>::ObArray(size_t allocated)
{
	allocated = max(size_t(32), allocated);  // Ϊ����Ƶ��������������Ԥ����Ŀռ�����Ϊ32
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
	allocated = allocated / 2 * 3;  // ��Ԥ����Ŀռ�����Ϊԭ���Ķ���֮��
	T * nxt = new T [allocated];

	for (size_t i = 0; i < count; ++i) nxt[i] = arr[i];  // ��ԭ����λ���е�������������´���λ��
	delete arr; arr = nxt;  // �ͷžɴ���λ�õĿռ�
}


template <typename T>
inline ObArray<T>::~ObArray()
{
	delete[] arr;  // �ͷ������ռ�
}

template <typename T>
inline size_t ObArray<T>::GetCount() const
{
	return count;
}

template <typename T>
inline T& ObArray<T>::GetAt(size_t index) const
{
	if (index >= 0 && index < count)  // ���߽�����
		return arr[index];
	AfxThrowInvalidArgException();  // �����±�Խ��
}

template <typename T>
inline void ObArray<T>::Add(const T &pt)
{
	if (count + 1 == allocated) Enlarge();  // �����ռ佫��ʱ���������ռ�
	arr[count] = pt; ++count;  // ������װ������
}

template <typename T>
inline void ObArray<T>::Remove(size_t index)
{
	if (index >= 0 && index < count) {
		for (size_t i = index; i < count - 1; ++i) {
			arr[i] = arr[i + 1];  // �����Ƴ���������λ�ú��ָ������ǰ��
		}
		--count;  // ���ж����������һ
	}
}

template <typename T>
inline void ObArray<T>::Empty()
{
	count = 0;
}
