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

	// ������㺯��
	virtual double GetArea() = 0;

	// �ܳ����㺯��
	virtual double GetPerimeter() = 0;
};


// ��
class Point : public Shape
{
public:
	double x, y;
	
	Point() : x(0), y(0) {};
	Point(double x, double y) : x(x), y(y) {};
	Point(const Point & pt) : x(pt.x), y(pt.y) {};

	CPoint ToCPoint();

	DECLARE_SERIAL(Point)
	virtual void Serialize(CArchive &ar);
	
	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};

// ��
class Segment : public Shape
{
public:
	Point head, tail;  // �߶ε������յ�

	Segment() = default;
	Segment(const Point &head, const Point &tail) : head(head), tail(tail) {};

	DECLARE_SERIAL(Segment)
	virtual void Serialize(CArchive &ar);
	
	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};

// Բ
class Circle : public Shape
{
public:
	Point center;  // Բ��
	double radius;  // �뾶

	Circle() : center(0, 0), radius(0) {};
	Circle(Point center, double radius) : center(center), radius(radius) {};

	DECLARE_SERIAL(Circle)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};


// ������

// �ı���

// ƽ���ı���

// ����
