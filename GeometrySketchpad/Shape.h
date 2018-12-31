#pragma once


// 所有几何图形的抽象基类
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	// 序列化实现
	virtual void Serialize(CArchive &ar) = 0;

	// 绘图函数
	virtual void OnDraw(CDC* pDC) = 0;

	// 面积计算函数
	virtual double GetArea() = 0;

	// 周长计算函数
	virtual double GetPerimeter() = 0;
};


// 点
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

// 线
class Segment : public Shape
{
public:
	Point head, tail;  // 线段的起点和终点

	Segment() = default;
	Segment(const Point &head, const Point &tail) : head(head), tail(tail) {};

	DECLARE_SERIAL(Segment)
	virtual void Serialize(CArchive &ar);
	
	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};

// 圆
class Circle : public Shape
{
public:
	Point center;  // 圆心
	double radius;  // 半径

	Circle() : center(0, 0), radius(0) {};
	Circle(Point center, double radius) : center(center), radius(radius) {};

	DECLARE_SERIAL(Circle)
	virtual void Serialize(CArchive &ar);

	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};


// 三角形

// 四边形

// 平行四边形

// 矩形
