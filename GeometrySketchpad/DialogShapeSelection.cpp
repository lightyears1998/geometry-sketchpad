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
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &DialogShapeSelection::OnSelchangedTree)
END_MESSAGE_MAP()


// DialogShapeSelection message handlers


void DialogShapeSelection::OnShapeArrayUpdated()
{
	shape_tree.DeleteAllItems();  // 删除原有项目

	size_t count = shape_array->GetCount();
	for (size_t i = 0; i < count; ++i) {
		Shape * shape = shape_array->GetAt(i);
		CString & identifier = shape->Identifier;
		HTREEITEM item = shape_tree.InsertItem(identifier);
		shape_tree.SetCheck(item, shape->IsSelected);
	}
}


BOOL DialogShapeSelection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// MFC TreeCtrl Issue
	// 重新设置TVS_CHECKBOXES，以避免对话框初始化过程中调用SetCheck()函数失效
	shape_tree.ModifyStyle(TVS_CHECKBOXES, 0);
	shape_tree.ModifyStyle(0, TVS_CHECKBOXES);

	OnShapeArrayUpdated();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void DialogShapeSelection::OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	TVITEM item_new = pNMTreeView->itemNew;
	

	*pResult = 0;
}
