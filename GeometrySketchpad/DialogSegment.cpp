// DialogSegment.cpp : implementation file
//

#include "stdafx.h"
#include "GeometrySketchpad.h"
#include "DialogSegment.h"
#include "afxdialogex.h"


// DialogSegment dialog

IMPLEMENT_DYNAMIC(DialogSegment, CDialogEx)

DialogSegment::DialogSegment(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEGMENT, pParent)
	, coordinate_x1(0)
	, coordinate_y1(0)
	, coordinate_x2(0)
	, coordinate_y2(0)
{

}

DialogSegment::~DialogSegment()
{
}

void DialogSegment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, coordinate_x1);
	DDX_Text(pDX, IDC_EDIT2, coordinate_y1);
	DDX_Text(pDX, IDC_EDIT3, coordinate_x2);
	DDX_Text(pDX, IDC_EDIT4, coordinate_y2);
}


BEGIN_MESSAGE_MAP(DialogSegment, CDialogEx)
END_MESSAGE_MAP()


// DialogSegment message handlers
