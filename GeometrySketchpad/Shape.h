#pragma once


// ���м���ͼ�εĳ������
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	// ���л�ʵ��
	virtual void Serialize(CArchive &ar) = 0;

	// ��ͼ����
	virtual void OnDraw(CDC* pDC) = 0;

	// �������
	virtual double GetArea() = 0;

	// �����ܳ�
	virtual double GetPerimeter() = 0;
};


// ��
class Point : public Shape
{
public:
	double x, y;

	virtual void Serialize(CArchive &ar);
	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};

// ��
class Segment : public Shape
{
	Point head, tail;  // �߶ε������յ�

	virtual void Serialize(CArchive &ar);
	virtual double GetArea();
	virtual double GetPerimeter();
};

// Բ

// ������

// �ı���

// ƽ���ı���

// ����
