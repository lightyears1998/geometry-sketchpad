#pragma once

#include "stdafx.h"

// 所有几何图形的抽象基类
class Shape : public CObject
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	CString Identifier;   // 当前图形的一个好记的名称
	bool IsSelected = false;  // 当前图形是否被选中

	// 序列化实现
	virtual void Serialize(CArchive &ar);

	// 绘图函数
	virtual void OnDraw(CDC* pDC) = 0;

	// 面积计算函数
	virtual double GetArea() = 0;

	// 周长计算函数
	virtual double GetPerimeter() = 0;

	// 缩放函数
	virtual void Scale(double ratio) = 0;

	// 平移函数
	virtual void Move(double dx, double dy) = 0;
};
