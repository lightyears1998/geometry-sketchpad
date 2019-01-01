#pragma once

#include "stdafx.h"


// 所有几何图形的抽象基类
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	bool IsSelected = true;  // 当前图形是否被选中

	// 序列化实现
	virtual void Serialize(CArchive &ar) = 0;

	// 绘图函数
	virtual void OnDraw(CDC* pDC) = 0;

	// 面积计算函数
	virtual double GetArea() = 0;

	// 周长计算函数
	virtual double GetPerimeter() = 0;
};
