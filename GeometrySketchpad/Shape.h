#pragma once


// ���м���ͼ�εĳ������
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	// ���л�ʵ��
	void Serialize(CArchive &ar) = 0;

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
