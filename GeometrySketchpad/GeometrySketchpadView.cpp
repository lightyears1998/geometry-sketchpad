// GeometrySketchpadView.cpp: CGeometrySketchpadView 类的实现


#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GeometrySketchpad.h"
#endif

#include "GeometrySketchpadDoc.h"
#include "GeometrySketchpadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeometrySketchpadView

IMPLEMENT_DYNCREATE(CGeometrySketchpadView, CView)

BEGIN_MESSAGE_MAP(CGeometrySketchpadView, CView)
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

	ShapeArray & arr = *(GetDocument()->arr);
	size_t count = arr.GetCount();
	for (size_t i = 0; i < count; ++i) {
		arr.GetAt(i)->OnDraw(pDC);
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
