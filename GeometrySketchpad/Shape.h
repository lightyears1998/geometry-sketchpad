#pragma once

#include "stdafx.h"


// 所有几何图形的抽象基类
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	// 获取对象的一个克隆
	virtual Shape * Clone() const = 0;

	// 序列化实现
	virtual void Serialize(CArchive &ar) = 0;

	// 绘图函数
	virtual void OnDraw(CDC* pDC) = 0;

	// 面积计算函数
	virtual double GetArea() = 0;

	// 周长计算函数
	virtual double GetPerimeter() = 0;
};
