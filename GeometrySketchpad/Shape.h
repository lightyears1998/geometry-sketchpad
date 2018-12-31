#pragma once

#include "stdafx.h"


// ���м���ͼ�εĳ������
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	// ��ȡ�����һ����¡
	virtual Shape * Clone() const = 0;

	// ���л�ʵ��
	virtual void Serialize(CArchive &ar) = 0;

	// ��ͼ����
	virtual void OnDraw(CDC* pDC) = 0;

	// ������㺯��
	virtual double GetArea() = 0;

	// �ܳ����㺯��
	virtual double GetPerimeter() = 0;
};
