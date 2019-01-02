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

	click_positions.Add(point);
	size_t click_count = click_positions.GetCount();   // 左键单词次数

	switch (mouse_state)
	{
	case MouseState::DrawPoint: {
		if (click_count == 1) {
			shape_array.Add(new Point(point.x, point.y));
			click_positions.Clear();
		}
		break;
	}
	case MouseState::DrawLine: {
		if (click_count == 2) {
			Point head = click_positions.GetAt(0), tail = point;
			click_positions.Clear();
			shape_array.Add(new Segment(head, tail));
		}
		break;
	}
	case MouseState::DrawTriangle: {
		if (click_count == 3) {
			Point pt1 = click_positions.GetAt(0);
			Point pt2 = click_positions.GetAt(1);
			Point pt3 = point;
			click_positions.Clear();

			ArbitraryPolygon * triangle = new ArbitraryPolygon();
			triangle->MakeTriangle(pt1, pt2, pt3);
			shape_array.Add(triangle);
		}
		break;
	}
	case MouseState::DrawRectangle: {
		if (click_count == 2) {
			Point pt1 = click_positions.GetAt(0);  // 矩形对角线上的一点
			Point pt2 = point;  // 矩形对角线上的另一点
			click_positions.Clear();

			ArbitraryPolygon * rectangle = new ArbitraryPolygon();
			rectangle->MakeRectangle(pt1, pt2);
			shape_array.Add(rectangle);
		}
		break;
	}
	case MouseState::DrawCircle: {
		if (click_count == 2) {
			Point center = click_positions.GetAt(0);
			click_positions.Clear();
			
			double radius = hypot(point.x - center.x, point.y - center.y);
			shape_array.Add(new Circle(center, radius));
		}
		break;
	}
	case MouseState::DrawParallelogram: {
		if (click_count == 3) {
			Point pt1 = click_positions.GetAt(0),
				pt2 = click_positions.GetAt(1),
				pt3 = point;
			click_positions.Clear();

			ArbitraryPolygon * parallelogram = new ArbitraryPolygon();
			parallelogram->MakeParallelogramFromPoints(pt1, pt2, pt3);
			shape_array.Add(parallelogram);
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
	click_positions.Clear();
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
	size_t click_count = click_positions.GetCount();

	if (click_count == 0) return;
	realtime_feedback.Clear();  // 清除以往的实时预览

	switch (mouse_state)
	{
	case MouseState::DrawLine: {
		if (click_count == 1) {
			
			realtime_feedback.Add(new Segment(click_positions.GetAt(0), point));
		}
		break;
	}
	case MouseState::DrawTriangle: {
		if (click_count == 1) {
			realtime_feedback.Add(new Segment(click_positions.GetAt(0), point));
		}
		else if (click_count == 2) {
			realtime_feedback.Add(new Segment(click_positions.GetAt(0), click_positions.GetAt(1)));
			realtime_feedback.Add(new Segment(click_positions.GetAt(0), point));
			realtime_feedback.Add(new Segment(click_positions.GetAt(1), point));
		}
		break;
	}
	case MouseState::DrawRectangle: {
		if (click_count == 1) {
			Point v1 = click_positions.GetAt(0);  // 矩形对角线上的一点
			Point v2 = point;  // 矩形对角线上的另一点

			ArbitraryPolygon * rectangle = new ArbitraryPolygon();
			rectangle->MakeRectangle(v1, v2);
			realtime_feedback.Add(rectangle);
		}
		break;
	}
	case MouseState::DrawCircle: {
		if (click_count == 1) {
			Point center = click_positions.GetAt(0);

			double radius = hypot(point.x - center.x, point.y - center.y);
			realtime_feedback.Add(new Circle(center, radius));
		}
		break;
	}
	case MouseState::DrawParallelogram: {
		if (click_count == 1) {
			realtime_feedback.Add(new Segment(click_positions.GetAt(0), point));
		}
		else if (click_count == 2) {
			Point pt1 = click_positions.GetAt(0),
				pt2 = click_positions.GetAt(1),
				pt3 = point;

			ArbitraryPolygon * parallelogram = new ArbitraryPolygon();
			parallelogram->MakeParallelogramFromPoints(pt1, pt2, pt3);
			realtime_feedback.Add(parallelogram);
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


// 将视图恢复到默认状态
void CGeometrySketchpadView::RestoreDefaultState()
{
	ChangeMouseState(MouseState::Selection);
}


// 显示“图形列表”窗口
void CGeometrySketchpadView::ShowShapeListDialog()
{
	if (shape_selection_dialog.m_hWnd == nullptr) {  // 如果此前没有创建“图形列表”窗口则创建
		shape_selection_dialog.doc = GetDocument();
		shape_selection_dialog.shape_array = &(GetDocument()->shape_array);
		shape_selection_dialog.Create(IDD_SHAPE_SELECTION, this);
	}
	shape_selection_dialog.ShowWindow(SW_NORMAL);
	shape_selection_dialog.OnShapeArrayUpdated();
}


// 同步ShapeArray的更新状态
void CGeometrySketchpadView::OnShapeArrayUpdated()
{
	realtime_feedback.Clear();  // 清空原有的反馈图案
	Invalidate();  // 使原有绘制失效，将最新的ShapeArray绘制到屏幕上
	if (shape_selection_dialog.m_hWnd != nullptr)
		shape_selection_dialog.OnShapeArrayUpdated();  // 同步“图形列表”窗口的状态
}
