// DialogShapeSelection.cpp : implementation file
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "GeometrySketchpadView.h"
#include "GeometrySketchpadDoc.h"
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
	DDX_Control(pDX, IDC_TREE, shape_tree);
}


BEGIN_MESSAGE_MAP(DialogShapeSelection, CDialogEx)
END_MESSAGE_MAP()


// DialogShapeSelection message handlers


void DialogShapeSelection::UpdateShapeState()
{
	shape_tree.DeleteAllItems();

	size_t count = shape_array->GetCount();
	for (size_t i = 0; i < count; ++i) {
		Shape * shape = shape_array->GetAt(i);
		HTREEITEM item = shape_tree.InsertItem(L"ÐÎ×´");
		if (shape->IsSelected) {
			shape_tree.SetCheck(item);  // !ÎÞÐ§
		}
	}
}


BOOL DialogShapeSelection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateShapeState();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
