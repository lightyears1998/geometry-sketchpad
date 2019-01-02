#pragma once

#include "PtArray.hpp"

// DialogShapeSelection dialog

class DialogShapeSelection : public CDialogEx
{
	DECLARE_DYNAMIC(DialogShapeSelection)

public:
	DialogShapeSelection(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogShapeSelection();
	
	CGeometrySketchpadDoc * doc = nullptr;
	PtArray<Shape> * shape_array = nullptr;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE_SELECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void OnShapeArrayUpdated();
	CTreeCtrl shape_tree;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSelect();
	afx_msg void OnBnClickedButtonSelectAll();
	afx_msg void OnBnClickedButtonDeselect();
	afx_msg void OnBnClickedButtonRemove();
};
