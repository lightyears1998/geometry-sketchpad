// DialogArbitraryPolygon.cpp : implementation file
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "DialogArbitraryPolygon.h"
#include "afxdialogex.h"

#include "DialogPoint.h"


// DialogArbitraryPolygon dialog

IMPLEMENT_DYNAMIC(DialogArbitraryPolygon, CDialogEx)

DialogArbitraryPolygon::DialogArbitraryPolygon(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARTBITRARY_POLYGON, pParent)
{

}

DialogArbitraryPolygon::~DialogArbitraryPolygon()
{
}

void DialogArbitraryPolygon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, list);
}


BEGIN_MESSAGE_MAP(DialogArbitraryPolygon, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &DialogArbitraryPolygon::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &DialogArbitraryPolygon::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &DialogArbitraryPolygon::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDOK, &DialogArbitraryPolygon::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogArbitraryPolygon message handlers

BOOL DialogArbitraryPolygon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	list.SetExtendedStyle(list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	list.InsertColumn(0, TEXT("x坐标"), LVCFMT_LEFT, list.GetStringWidth(TEXT("0123456789")));
	list.InsertColumn(1, TEXT("y坐标"), LVCFMT_LEFT, list.GetStringWidth(TEXT("0123456789")));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void DialogArbitraryPolygon::OnBnClickedButtonAdd()
{
	DialogPoint dlg;
	if (dlg.DoModal() == IDOK) {
		double x = dlg.coordinate_x;
		double y = dlg.coordinate_y;

		CString str_x, str_y; 
		str_x.Format(TEXT("%d"), int(x));
		str_y.Format(TEXT("%d"), int(y));
		
		list.InsertItem(list.GetItemCount(), str_x);
		list.SetItemText(list.GetItemCount() - 1, 1, str_y);
	}
}


void DialogArbitraryPolygon::OnBnClickedButtonModify()
{
	if (list.GetSelectionMark() >= 0) {
		int mark = list.GetSelectionMark();

		CString str_x, str_y;
		str_x = list.GetItemText(mark, 0);
		str_y = list.GetItemText(mark, 1);
		double x = _ttoi(str_x), y = _ttoi(str_y);

		DialogPoint dlg;
		dlg.coordinate_x = x; 
		dlg.coordinate_y = y;

		if (dlg.DoModal() == IDOK) {
			x = dlg.coordinate_x;
			y = dlg.coordinate_y;

			str_x.Format(TEXT("%d"), int(x));
			str_y.Format(TEXT("%d"), int(y));
			
			list.SetItemText(mark, 0, str_x);
			list.SetItemText(mark, 1, str_y);
		}
	}
	else {
		MessageBox(TEXT("请选中一行后再修改~"), TEXT("提示"));
	}
}


void DialogArbitraryPolygon::OnBnClickedButtonRemove()
{
	if (list.GetSelectionMark() >= 0) {
		int mark = list.GetSelectionMark();

		list.DeleteItem(mark);
	}
}


void DialogArbitraryPolygon::OnBnClickedOk()
{
	int count = list.GetItemCount();
	for (int i = 0; i < count; ++i) {
		double x = _ttoi(list.GetItemText(i, 0));
		double y = _ttoi(list.GetItemText(i, 1));
		vertexs->Add(Point(x, y));
	}

	CDialogEx::OnOK();
}
