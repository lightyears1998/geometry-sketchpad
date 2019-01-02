// DialogCircle.cpp: 实现文件
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "DialogCircle.h"
#include "afxdialogex.h"


// DialogCircle 对话框

IMPLEMENT_DYNAMIC(DialogCircle, CDialogEx)

DialogCircle::DialogCircle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CIRCLE, pParent)
	, coordinate_x(0)
	, coordinate_y(0)
	, radius(0)
{

}

DialogCircle::~DialogCircle()
{
}

void DialogCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, coordinate_x);
	DDX_Text(pDX, IDC_EDIT2, coordinate_y);
	DDX_Text(pDX, IDC_EDIT3, radius);
}


BEGIN_MESSAGE_MAP(DialogCircle, CDialogEx)
END_MESSAGE_MAP()


// DialogCircle 消息处理程序
