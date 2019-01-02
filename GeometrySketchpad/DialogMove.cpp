// DialogMove.cpp : implementation file
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "DialogMove.h"
#include "afxdialogex.h"


// DialogMove dialog

IMPLEMENT_DYNAMIC(DialogMove, CDialogEx)

DialogMove::DialogMove(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOVE, pParent)
	, dx(0)
	, dy(0)
{

}

DialogMove::~DialogMove()
{
}

void DialogMove::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dx);
	DDX_Text(pDX, IDC_EDIT2, dy);
}


BEGIN_MESSAGE_MAP(DialogMove, CDialogEx)
END_MESSAGE_MAP()


// DialogMove message handlers
