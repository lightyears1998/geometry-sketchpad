#pragma once


// 所有几何图形的抽象基类
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	// 序列化实现
	void Serialize(CArchive &ar) = 0;

	// 计算面积
	virtual double GetArea() = 0;

	// 计算周长
	virtual double GetPerimeter() = 0;
};


// 点
class Point : public Shape
{
public:
	double x, y;

	virtual void Serialize(CArchive &ar);
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
