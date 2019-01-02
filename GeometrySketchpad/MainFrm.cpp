// MainFrm.cpp: CMainFrame 类的实现


#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "GeometrySketchpadDoc.h"
#include "GeometrySketchpadView.h"

#include "DialogPoint.h"
#include "DialogSegment.h"
#include "DialogCircle.h"
#include "DialogArbitraryPolygon.h"

#include "Shape.h"
#include "Segment.h"
#include "Point.h"
#include "Circle.h"
#include "Polygon.h"
#include "MainFrm.h"

#include "PtArray.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_DEBUG, &CMainFrame::OnDebug)
	ON_COMMAND(ID_ADD_POINT, &CMainFrame::OnAddPoint)
	ON_COMMAND(ID_MOUSE_SELECTON, &CMainFrame::OnMouseSelecton)
	ON_COMMAND(ID_MOUSE_DRAW_TRIANGLE, &CMainFrame::OnMouseDrawTriangle)
	ON_COMMAND(ID_MOUSE_DRAW_RECTANGLE, &CMainFrame::OnMouseDrawRectangle)
	ON_COMMAND(ID_MOUSE_DRAW_POINT, &CMainFrame::OnMouseDrawPoint)
	ON_COMMAND(ID_MOUSE_DRAW_PARALLELOGRAM, &CMainFrame::OnMouseDrawParallelogram)
	ON_COMMAND(ID_MOUSE_DRAW_LINE, &CMainFrame::OnMouseDrawLine)
	ON_COMMAND(ID_MOUSE_DRAW_CIRCLE, &CMainFrame::OnMouseDrawCircle)
	ON_COMMAND(ID_VIEW_SHAPE_LIST, &CMainFrame::OnViewShapeList)
	ON_COMMAND(ID_ADD_CIRCLE, &CMainFrame::OnAddCircle)
	ON_COMMAND(ID_ADD_SEGMENT, &CMainFrame::OnAddSegment)
	ON_COMMAND(ID_ADD_ARTBITTRARY_POLOGEN, &CMainFrame::OnAddArtbittraryPologen)
	ON_COMMAND(IDM_CALC_ALL_AREA, &CMainFrame::OnCalcAllArea)
	ON_COMMAND(IDM_CALC_ALL_PRERIMETER, &CMainFrame::OnCalcAllPrerimeter)
	ON_COMMAND(IDM_CALC_SEL_AREA, &CMainFrame::OnCalcSelArea)
	ON_COMMAND(IDM_CALC_SEL_PRERIMETER, &CMainFrame::OnCalcSelPrerimeter)
	ON_COMMAND(IDM_REMOVE_SELECTED, &CMainFrame::OnRemoveSelected)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	
	// 在此处通过修改
	// CREATESTRUCT cs 来修改窗口类或样式

	// 注意到默认的窗口标题取自字符串资源 IDR_MAINFRAME 的第一个子串

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


// 用于调试程序功能的函数
void CMainFrame::OnDebug()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();
	PtArray<Shape> & shape_array = doc->shape_array;

	// 测试添加功能
	for (int i = 0; i < 128; ++i) {
		shape_array.Add(new Point(2 * i, 2 * i));
	}

	// 测试移除功能
	for (int i = 0; i < 128; ++i) {
		shape_array.Remove(i * 4);
	}

	// 测试添加线段
	shape_array.Add(new Segment(Point(100, 200), Point(200, 200)));

	// 测试添加圆
	shape_array.Add(new Circle(Point(500, 500), 200));
	shape_array.Add(new Circle(Point(300, 200), 200));

	// 测试添加多边形
	ObArray<Point> pts;
	pts.Add(Point(500, 500));
	pts.Add(Point(500, 1000));
	pts.Add(Point(1000, 1000));
	shape_array.Add(new ArbitraryPolygon(pts));

	Invalidate();
}


void CMainFrame::OnAddPoint()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();

	DialogPoint dlg;
	if (dlg.DoModal() == IDOK) {
		double x = dlg.coordinate_x, y = dlg.coordinate_y;
		Point * pt = new Point(x, y);
		doc->shape_array.Add(pt);
	}
	doc->NotifyShapeArrayUpdated();
}


void CMainFrame::OnAddCircle()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();
	
	DialogCircle dlg;
	if (dlg.DoModal() == IDOK) {
		double x = dlg.coordinate_x, y = dlg.coordinate_y;
		double radius = dlg.radius;
		doc->shape_array.Add(new Circle(Point(x, y), radius));
	}
	doc->NotifyShapeArrayUpdated();
}




void CMainFrame::OnMouseSelecton()
{
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetActiveView();
	view->ChangeMouseState(CGeometrySketchpadView::MouseState::Selection);
}


void CMainFrame::OnMouseDrawTriangle()
{
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetActiveView();
	view->ChangeMouseState(CGeometrySketchpadView::MouseState::DrawTriangle);
}


void CMainFrame::OnMouseDrawRectangle()
{
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetActiveView();
	view->ChangeMouseState(CGeometrySketchpadView::MouseState::DrawRectangle);
}


void CMainFrame::OnMouseDrawPoint()
{
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetActiveView();
	view->ChangeMouseState(CGeometrySketchpadView::MouseState::DrawPoint);
}


void CMainFrame::OnMouseDrawParallelogram()
{
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetActiveView();
	view->ChangeMouseState(CGeometrySketchpadView::MouseState::DrawParallelogram);
}


void CMainFrame::OnMouseDrawLine()
{
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetActiveView();
	view->ChangeMouseState(CGeometrySketchpadView::MouseState::DrawLine);
}


void CMainFrame::OnMouseDrawCircle()
{
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetActiveView();
	view->ChangeMouseState(CGeometrySketchpadView::MouseState::DrawCircle);
}


void CMainFrame::OnViewShapeList()
{
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetActiveView();
	view->ShowShapeListDialog();
}



void CMainFrame::OnAddSegment()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();
	DialogSegment dlg;

	if (dlg.DoModal() == IDOK) {
		double x1 = dlg.coordinate_x1, y1 = dlg.coordinate_y1;
		double x2 = dlg.coordinate_x2, y2 = dlg.coordinate_y2;
		doc->shape_array.Add(new Segment(Point(x1, y1), Point(x2, y2)));
	}
	doc->NotifyShapeArrayUpdated();
}


void CMainFrame::OnAddArtbittraryPologen()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();
	ObArray<Point> vertexs;
	
	DialogArbitraryPolygon dlg;	
	dlg.vertexs = &vertexs;

	if (dlg.DoModal() == IDOK) {
		doc->shape_array.Add(new ArbitraryPolygon(vertexs));
	}
	doc->NotifyShapeArrayUpdated();
}


void CMainFrame::OnCalcAllArea()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();

	double result = 0;
	for (size_t i = 0; i < doc->shape_array.GetCount(); ++i) {
		Shape * shape = doc->shape_array.GetAt(i);
		result += shape->GetArea();
	}
	
	CString str;
	str.Format(TEXT("%f"), result);
	MessageBox(str, TEXT("所有图形的面积"));
}


void CMainFrame::OnCalcAllPrerimeter()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();

	double result = 0;
	for (size_t i = 0; i < doc->shape_array.GetCount(); ++i) {
		Shape * shape = doc->shape_array.GetAt(i);
		result += shape->GetPerimeter();
	}

	CString str;
	str.Format(TEXT("%f"), result);
	MessageBox(str, TEXT("所有图形的周长"));
}


void CMainFrame::OnCalcSelArea()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();
	
	bool has_selection = false;
	double result = 0;
	for (size_t i = 0; i < doc->shape_array.GetCount(); ++i) {
		Shape * shape = doc->shape_array.GetAt(i);
		if (shape->IsSelected)
			result += shape->GetArea(), has_selection = true;
	}

	CString str;
	str.Format(TEXT("%f"), result);
	if (has_selection)
		MessageBox(str, TEXT("选定图形的面积"));
	else
		MessageBox(TEXT("当前没有选中图形呀~"), TEXT("提示"));
}


void CMainFrame::OnCalcSelPrerimeter()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();
	
	bool has_selection = false;
	double result = 0;
	for (size_t i = 0; i < doc->shape_array.GetCount(); ++i) {
		Shape * shape = doc->shape_array.GetAt(i);
		if (shape->IsSelected)
			result += shape->GetPerimeter(), has_selection = true;
	}

	CString str;
	str.Format(TEXT("%f"), result);
	if (has_selection)
		MessageBox(str, TEXT("选定图形的面周长"));
	else 
		MessageBox(TEXT("当前没有选中图形呀~"), TEXT("提示"));
}


void CMainFrame::OnRemoveSelected()
{
	if (MessageBox(TEXT("确认要进行删除喵？"), TEXT("删除确认"), MB_OKCANCEL) == IDOK) {
		bool removed = false;
		CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();

		for (size_t i = doc->shape_array.GetCount(); i; --i) {  // 自后向前遍历数组，并删除具有选中标记的图形
			if (doc->shape_array.GetAt(i - 1)->IsSelected) {
				doc->shape_array.Remove(i - 1);
				removed = true;
			}
		}

		if (!removed) {
			MessageBox(TEXT("还没有选择图形呢~"), TEXT("用户提示"));
		}
		else {
			doc->NotifyShapeArrayUpdated();
		}
	}
}
