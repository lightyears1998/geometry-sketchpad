// DialogShapeSelection.cpp : implementation file
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "DialogShapeSelection.h"
#include "afxdialogex.h"


// DialogShapeSelection dialog

IMPLEMENT_DYNAMIC(DialogShapeSelection, CDialogEx)

DialogShapeSelection::DialogShapeSelection(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHAPE_SELECTION, pParent)
{

}

DialogShapeSelection::~DialogShapeSelection()
{
}

void DialogShapeSelection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogShapeSelection, CDialogEx)
END_MESSAGE_MAP()


// DialogShapeSelection message handlers
