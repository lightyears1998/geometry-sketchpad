// GeometrySketchpadView.cpp: CGeometrySketchpadView 类的实现


#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GeometrySketchpad.h"
#endif

#include "GeometrySketchpadDoc.h"
#include "GeometrySketchpadView.h"

#include "Shape.h"
#include "PtArray.hpp"
#include "Point.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeometrySketchpadView

IMPLEMENT_DYNCREATE(CGeometrySketchpadView, CView)

BEGIN_MESSAGE_MAP(CGeometrySketchpadView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CGeometrySketchpadView 构造/析构

CGeometrySketchpadView::CGeometrySketchpadView() noexcept
{
	// TODO: 在此处添加构造代码

}

CGeometrySketchpadView::~CGeometrySketchpadView()
{
}

BOOL CGeometrySketchpadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGeometrySketchpadView 绘图

void CGeometrySketchpadView::OnDraw(CDC* pDC)
{
	CGeometrySketchpadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	PtArray<Shape> & shape_array = GetDocument()->shape_array;
	size_t count = shape_array.GetCount();
	for (size_t i = 0; i < count; ++i) {
		shape_array.GetAt(i)->OnDraw(pDC);
	}
}


// CGeometrySketchpadView 诊断

#ifdef _DEBUG
void CGeometrySketchpadView::AssertValid() const
{
	CView::AssertValid();
}

void CGeometrySketchpadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeometrySketchpadDoc* CGeometrySketchpadView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeometrySketchpadDoc)));
	return (CGeometrySketchpadDoc*)m_pDocument;
}
#endif //_DEBUG


// CGeometrySketchpadView 消息处理程序


void CGeometrySketchpadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CGeometrySketchpadDoc * doc = GetDocument();
	PtArray<Shape> & shape_array = doc->shape_array;

	switch (mouse_state)
	{
	case MouseState::DrawPoint: {
		shape_array.Add(new Point(point.x, point.y));
	}
	}

	Invalidate();
	// 不需要调用基类函数
	// CView::OnLButtonDown(nFlags, point);
}


void CGeometrySketchpadView::ChangeMouseState(MouseState state)
{
	mouse_state = state;
	previous_click.Clear();
}


BOOL CGeometrySketchpadView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (mouse_state != MouseState::Selection) {
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return true;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}
