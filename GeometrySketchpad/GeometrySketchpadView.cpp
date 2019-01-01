// GeometrySketchpadView.cpp: CGeometrySketchpadView 类的实现


#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GeometrySketchpad.h"
#endif

#include "GeometrySketchpadDoc.h"
#include "GeometrySketchpadView.h"

#include "PtArray.hpp"
#include "ObArray.hpp"
#include "Shape.h"
#include "Point.h"
#include "Segment.h"
#include "Polygon.h"
#include "Circle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeometrySketchpadView

IMPLEMENT_DYNCREATE(CGeometrySketchpadView, CView)

BEGIN_MESSAGE_MAP(CGeometrySketchpadView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
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

	// 应尝试双缓冲技术以减少闪烁
	// https://mykbn.wordpress.com/2013/06/24/double-buffering-technique-in-mfc-for-flicker-free-drawing/

	size_t count;

	count = realtime_feedback.GetCount();  
	for (size_t i = 0; i < count; ++i) {  // 绘制实时反馈
		realtime_feedback.GetAt(i)->OnDraw(pDC);
	}
	
	PtArray<Shape> & shape_array = GetDocument()->shape_array;
	count = shape_array.GetCount();
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

	size_t count = previous_click.GetCount();   // 鼠标左键单击事件的计数器

	switch (mouse_state)
	{
	case MouseState::DrawPoint: {
		shape_array.Add(new Point(point.x, point.y));
		break;
	}
	case MouseState::DrawLine: {
		if (count == 0) {
			previous_click.Add(point);
		}
		else if (count == 1) {
			Point head = previous_click.GetAt(0), tail = point;
			previous_click.Clear();
			shape_array.Add(new Segment(head, tail));
		}
		break;
	}
	case MouseState::DrawTriangle: {
		if (count == 0 || count == 1) {
			previous_click.Add(point);
		}
		else if (count == 2) {
			Point pt1 = previous_click.GetAt(0);
			Point pt2 = previous_click.GetAt(1);
			previous_click.Clear();
			
			ObArray<Point> vertexs;
			vertexs.Add(pt1), vertexs.Add(pt2), vertexs.Add(point);

			shape_array.Add(new PolygonShape(vertexs));
		}
		break;
	}
	case MouseState::DrawRectangle: {
		if (count == 0) {
			previous_click.Add(point);
		}
		else if (count == 1) {
			Point dia_p1 = previous_click.GetAt(0);  // 矩形对角线上的一点
			Point dia_p2 = point;  // 矩形对角线上的另一点
			previous_click.Clear();

			ObArray<Point> vertexs;
			Point a(dia_p1), b(dia_p1.x, dia_p2.y), c(dia_p2), d(dia_p2.x, dia_p1.y);
			vertexs.Add(a), vertexs.Add(b), vertexs.Add(c), vertexs.Add(d);
			shape_array.Add(new PolygonShape(vertexs));
		}
		break;
	}
	case MouseState::DrawCircle: {
		if (count == 0) {
			previous_click.Add(point);
		}
		else if (count == 1) {
			Point center = previous_click.GetAt(0);
			previous_click.Clear();
			
			double radius = hypot(point.x - center.x, point.y - center.y);
			shape_array.Add(new Circle(center, radius));
		}
		break;
	}
	case MouseState::DrawParallelogram: {
		if (count == 0 || count == 1) {
			previous_click.Add(point);
		}
		else {
			Point a = previous_click.GetAt(0),
				b = previous_click.GetAt(1),
				c = point,
				d = Point(a.x + c.x - b.x, a.y + c.y - b.y);

			previous_click.Clear();

			ObArray<Point> vertexs;
			vertexs.Add(a), vertexs.Add(b), vertexs.Add(c), vertexs.Add(d);
			shape_array.Add(new PolygonShape(vertexs));
		}
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
	realtime_feedback.Clear();
}


BOOL CGeometrySketchpadView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (mouse_state != MouseState::Selection) {
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		return true;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CGeometrySketchpadView::OnMouseMove(UINT nFlags, CPoint point)
{
	size_t count = previous_click.GetCount();

	if (count == 0) return;

	switch (mouse_state)
	{
	case MouseState::DrawLine: {
		if (count == 1) {
			realtime_feedback.Clear();
			realtime_feedback.Add(new Segment(previous_click.GetAt(0), point));
		}
		break;
	}
	case MouseState::DrawTriangle: {
		if (count == 1) {
			realtime_feedback.Clear();
			realtime_feedback.Add(new Segment(previous_click.GetAt(0), point));
		}
		else if (count == 2) {
			realtime_feedback.Clear();
			realtime_feedback.Add(new Segment(previous_click.GetAt(0), previous_click.GetAt(1)));
			realtime_feedback.Add(new Segment(previous_click.GetAt(0), point));
			realtime_feedback.Add(new Segment(previous_click.GetAt(1), point));
		}
		break;
	}
	case MouseState::DrawRectangle: {
		if (count == 1) {
			realtime_feedback.Clear();
			
			Point dia_p1 = previous_click.GetAt(0);  // 矩形对角线上的一点
			Point dia_p2 = point;  // 矩形对角线上的另一点

			ObArray<Point> vertexs;
			Point a(dia_p1), b(dia_p1.x, dia_p2.y), c(dia_p2), d(dia_p2.x, dia_p1.y);
			vertexs.Add(a), vertexs.Add(b), vertexs.Add(c), vertexs.Add(d);
			realtime_feedback.Add(new PolygonShape(vertexs));
		}
		break;
	}
	case MouseState::DrawCircle: {
		if (count == 1) {
			realtime_feedback.Clear();
			Point center = previous_click.GetAt(0);

			double radius = hypot(point.x - center.x, point.y - center.y);
			realtime_feedback.Add(new Circle(center, radius));
		}
		break;
	}
	default:
		return;
	}

	Invalidate();
	// 不需要调用基类函数
	// CView::OnMouseMove(nFlags, point);
}
