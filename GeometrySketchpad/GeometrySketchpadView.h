// GeometrySketchpadView.h: CGeometrySketchpadView 类的接口


#pragma once


#include "GeometrySketchpadDoc.h"
#include "DialogShapeSelection.h"

#include "PtArray.hpp"
#include "ObArray.hpp"
#include "Point.h"

class CGeometrySketchpadView : public CView
{
protected: // 仅从序列化创建
	CGeometrySketchpadView() noexcept;
	DECLARE_DYNCREATE(CGeometrySketchpadView)

// 特性
public:
	CGeometrySketchpadDoc* GetDocument() const;
	PtArray<Shape> realtime_feedback;  // 给予用户的实时反馈
	ObArray<Point> click_positions;
	DialogShapeSelection shape_selection_dialog;

	enum MouseState : unsigned {
		Selection, DrawPoint, DrawLine, DrawTriangle,
		DrawParallelogram, DrawRectangle, DrawCircle
	} mouse_state = MouseState::Selection;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CGeometrySketchpadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void ChangeMouseState(MouseState state);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// 将视图恢复到默认状态
	void RestoreDefaultState();
	// 显示“图形列表”窗口
	void ShowShapeListDialog();
	// 将特定的图形标记为选取状态
	void SelectShape(size_t index, bool is_selected);
protected:
	// 在视图类与图形选择窗口之间同步选择状态
	void SyncShapeState();
};

#ifndef _DEBUG  // GeometrySketchpadView.cpp 中的调试版本
inline CGeometrySketchpadDoc* CGeometrySketchpadView::GetDocument() const
   { return reinterpret_cast<CGeometrySketchpadDoc*>(m_pDocument); }
#endif

