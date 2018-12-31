// MainFrm.cpp: CMainFrame 类的实现


#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "GeometrySketchpadDoc.h"

#include "DialogAddPoint.h"

#include "Shape.h"
#include "ShapeArray.h"
#include "Segment.h"
#include "Point.h"
#include "Circle.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_DEBUG, &CMainFrame::OnDebug)
	ON_COMMAND(ID_ADD_POINT, &CMainFrame::OnAddPoint)
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
	ShapeArray & shape_array = *(doc->shape_array);

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

	Invalidate();
}


void CMainFrame::OnAddPoint()
{
	CGeometrySketchpadDoc * doc = (CGeometrySketchpadDoc *)GetActiveDocument();

	DialogAddPoint dlg;
	if (dlg.DoModal() == IDOK) {
		double x = dlg.coordinate_x, y = dlg.coordinate_y;
		Point * pt = new Point(x, y);
		doc->shape_array->Add(pt);
	}
	Invalidate();
}
