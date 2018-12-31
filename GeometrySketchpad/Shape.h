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
	
	Point() = default;
	Point(double x, double y) : x(x), y(y) {};

	DECLARE_SERIAL(Point)
	virtual void Serialize(CArchive &ar);
	virtual void OnDraw(CDC* pDC);
	virtual double GetArea();
	virtual double GetPerimeter();
};

// 线
class Segment : public Shape
{
	Point head, tail;  // 线段的起点和终点

	virtual void Serialize(CArchive &ar);
	virtual double GetArea();
	virtual double GetPerimeter();
};

// 圆

// 三角形

// 四边形

// 平行四边形

// 矩形
