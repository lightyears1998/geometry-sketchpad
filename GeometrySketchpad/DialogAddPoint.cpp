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
{

}

DialogAddPoint::~DialogAddPoint()
{
}

void DialogAddPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogAddPoint, CDialogEx)
END_MESSAGE_MAP()


// DialogAddPoint message handlers
