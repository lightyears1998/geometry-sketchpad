// GeometrySketchpadView.h: CGeometrySketchpadView 类的接口


#pragma once


class CGeometrySketchpadView : public CView
{
protected: // 仅从序列化创建
	CGeometrySketchpadView() noexcept;
	DECLARE_DYNCREATE(CGeometrySketchpadView)

// 特性
public:
	CGeometrySketchpadDoc* GetDocument() const;
	
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
};

#ifndef _DEBUG  // GeometrySketchpadView.cpp 中的调试版本
inline CGeometrySketchpadDoc* CGeometrySketchpadView::GetDocument() const
   { return reinterpret_cast<CGeometrySketchpadDoc*>(m_pDocument); }
#endif

