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
ON_BN_CLICKED(IDC_BUTTON_SELECT, &DialogShapeSelection::OnBnClickedButtonSelect)
ON_BN_CLICKED(IDC_BUTTON_SELECT_ALL, &DialogShapeSelection::OnBnClickedButtonSelectAll)
ON_BN_CLICKED(IDC_BUTTON_DESELECT, &DialogShapeSelection::OnBnClickedButtonDeselect)
ON_BN_CLICKED(IDC_BUTTON_REMOVE, &DialogShapeSelection::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// DialogShapeSelection message handlers


void DialogShapeSelection::OnShapeArrayUpdated()
{
	shape_tree.DeleteAllItems();  // ɾ��ԭ����Ŀ

	size_t count = shape_array->GetCount();
	for (size_t i = 0; i < count; ++i) {
		Shape * shape = shape_array->GetAt(i);
		UINT32 index = UINT32(i);
		CString & identifier = shape->Identifier;
		HTREEITEM item = shape_tree.InsertItem(identifier);
		shape_tree.SetCheck(item, shape->IsSelected);
		shape_tree.SetItemData(item, index);  // ����shape_array�е�����
	}
}


BOOL DialogShapeSelection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// MFC TreeCtrl Issue
	// ��������TVS_CHECKBOXES���Ա���Ի����ʼ�������е���SetCheck()����ʧЧ
	shape_tree.ModifyStyle(TVS_CHECKBOXES, 0);
	shape_tree.ModifyStyle(0, TVS_CHECKBOXES);

	OnShapeArrayUpdated();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void DialogShapeSelection::OnBnClickedButtonSelect()
{
	for (HTREEITEM item = shape_tree.GetRootItem(); item; item = shape_tree.GetNextItem(item, TVGN_NEXT)) {
		UINT32 index = UINT32(shape_tree.GetItemData(item));
		shape_array->GetAt(index)->IsSelected = shape_tree.GetCheck(item);
	}
	doc->NotifyShapeArrayUpdated();
}


void DialogShapeSelection::OnBnClickedButtonSelectAll()
{
	for (HTREEITEM item = shape_tree.GetRootItem(); item; item = shape_tree.GetNextItem(item, TVGN_NEXT)) {
		shape_tree.SetCheck(item, true);
	}
}


void DialogShapeSelection::OnBnClickedButtonDeselect()
{
	for (HTREEITEM item = shape_tree.GetRootItem(); item; item = shape_tree.GetNextItem(item, TVGN_NEXT)) {
		shape_tree.SetCheck(item, false);
	}
}


void DialogShapeSelection::OnBnClickedButtonRemove()
{
	if (MessageBox(TEXT("ȷ��Ҫ����ɾ������"), TEXT("ɾ��ȷ��"), MB_OKCANCEL) == IDOK) {
		bool removed = false;

		for (size_t i = doc->shape_array.GetCount(); i; --i) {  // �Ժ���ǰ�������飬��ɾ������ѡ�б�ǵ�ͼ��
			if (shape_array->GetAt(i - 1)->IsSelected) {
				shape_array->Remove(i - 1);
				removed = true;
			}
		}

		if (!removed) {
			MessageBox(TEXT("��û��ѡ��ͼ����~"), TEXT("�û���ʾ"));
		}
		else {
			doc->NotifyShapeArrayUpdated();
		}
	}
}
