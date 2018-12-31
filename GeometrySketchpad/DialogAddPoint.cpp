// DialogAddPoint.cpp : implementation file
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "DialogAddPoint.h"
#include "afxdialogex.h"


// DialogAddPoint dialog

IMPLEMENT_DYNAMIC(DialogAddPoint, CDialogEx)

DialogAddPoint::DialogAddPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_POINT, pParent)
	, coordinate_x(0)
	, coordinate_y(0)
{

}

DialogAddPoint::~DialogAddPoint()
{
}

void DialogAddPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, coordinate_x);
	DDX_Text(pDX, IDC_EDIT_Y, coordinate_y);
}


BEGIN_MESSAGE_MAP(DialogAddPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogAddPoint::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogAddPoint message handlers


void DialogAddPoint::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
