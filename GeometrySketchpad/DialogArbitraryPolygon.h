#pragma once

#include "ObArray.hpp"
#include "Point.h"

// DialogArbitraryPolygon dialog

class DialogArbitraryPolygon : public CDialogEx
{
	DECLARE_DYNAMIC(DialogArbitraryPolygon)

public:
	DialogArbitraryPolygon(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogArbitraryPolygon();
	ObArray<Point> * vertexs;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARTBITRARY_POLYGON };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	CListCtrl list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedOk();
};
