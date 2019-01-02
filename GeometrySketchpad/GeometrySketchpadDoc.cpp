// GeometrySketchpadDoc.cpp: CGeometrySketchpadDoc 类的实现


#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GeometrySketchpad.h"
#endif

#include "GeometrySketchpadDoc.h"
#include "GeometrySketchpadView.h"
#include "Shape.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGeometrySketchpadDoc

IMPLEMENT_DYNCREATE(CGeometrySketchpadDoc, CDocument)

BEGIN_MESSAGE_MAP(CGeometrySketchpadDoc, CDocument)
END_MESSAGE_MAP()


// CGeometrySketchpadDoc 构造/析构

CGeometrySketchpadDoc::CGeometrySketchpadDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CGeometrySketchpadDoc::~CGeometrySketchpadDoc()
{
}

void CGeometrySketchpadDoc::SelectShape(size_t index, bool is_selected)
{
	shape_array.GetAt(index)->IsSelected = is_selected;
	NotifyShapeArrayUpdated();
}

BOOL CGeometrySketchpadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	shape_array.Clear();
	POSITION view_postion = GetFirstViewPosition();
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetNextView(view_postion);
	view->RestoreDefaultState();

	return TRUE;
}




// CGeometrySketchpadDoc 序列化

void CGeometrySketchpadDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())  // 储存过程
	{
		size_t shape_count = shape_array.GetCount();
		ar << shape_count;

		for (size_t i = 0; i < shape_count; ++i) {
			ar.WriteObject(shape_array.GetAt(i));
		}
	}
	else  // 加载过程
	{
		size_t shape_count; ar >> shape_count;
		for (size_t i = 0; i < shape_count; ++i) {
			Shape * shape = (Shape *)ar.ReadObject(nullptr);
			shape_array.Add(shape);
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CGeometrySketchpadDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CGeometrySketchpadDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CGeometrySketchpadDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGeometrySketchpadDoc 诊断

#ifdef _DEBUG
void CGeometrySketchpadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGeometrySketchpadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGeometrySketchpadDoc 命令


// 通知View类ShapeArray已经发生改变
void CGeometrySketchpadDoc::NotifyShapeArrayUpdated()
{
	POSITION view_postion = GetFirstViewPosition();
	CGeometrySketchpadView * view = (CGeometrySketchpadView *)GetNextView(view_postion);
	view->OnShapeArrayUpdated();
}
