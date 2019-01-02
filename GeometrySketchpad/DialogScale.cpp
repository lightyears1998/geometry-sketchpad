// DialogScale.cpp : implementation file
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "DialogScale.h"
#include "afxdialogex.h"


// DialogScale dialog

IMPLEMENT_DYNAMIC(DialogScale, CDialogEx)

DialogScale::DialogScale(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCALE, pParent)
	, ratio(0)
{

}

DialogScale::~DialogScale()
{
}

void DialogScale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ratio);
}


BEGIN_MESSAGE_MAP(DialogScale, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogScale::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogScale message handlers


void DialogScale::OnBnClickedOk()
{
	UpdateData();
	if (ratio > 0)
		CDialogEx::OnOK();
	else
		MessageBox(TEXT("缩放倍率必须大于0"), TEXT("提示"));
}
