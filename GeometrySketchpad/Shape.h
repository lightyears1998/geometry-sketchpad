#pragma once

#include "stdafx.h"

// ���м���ͼ�εĳ������
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	CString Identifier;   // ��ǰͼ�ε�һ���üǵ�����
	bool IsSelected = false;  // ��ǰͼ���Ƿ�ѡ��

	// ���л�ʵ��
	virtual void Serialize(CArchive &ar);

	// ��ͼ����
	virtual void OnDraw(CDC* pDC) = 0;

	// ������㺯��
	virtual double GetArea() = 0;

	// �ܳ����㺯��
	virtual double GetPerimeter() = 0;

	// ���ź���
	virtual void Scale(double ratio) = 0;

	// ƽ�ƺ���
	virtual void Move(double dx, double dy) = 0;
};
