// DialogPoint.cpp : implementation file
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "DialogPoint.h"
#include "afxdialogex.h"


// DialogPoint dialog

IMPLEMENT_DYNAMIC(DialogPoint, CDialogEx)

DialogPoint::DialogPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POINT, pParent)
	, coordinate_x(0)
	, coordinate_y(0)
{

}

DialogPoint::~DialogPoint()
{
}

void DialogPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, coordinate_x);
	DDX_Text(pDX, IDC_EDIT_Y, coordinate_y);
}


BEGIN_MESSAGE_MAP(DialogPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogPoint::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogPoint message handlers


void DialogPoint::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
