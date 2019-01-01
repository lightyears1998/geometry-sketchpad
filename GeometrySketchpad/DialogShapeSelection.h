#pragma once


// DialogShapeSelection dialog

class DialogShapeSelection : public CDialogEx
{
	DECLARE_DYNAMIC(DialogShapeSelection)

public:
	DialogShapeSelection(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogShapeSelection();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE_SELECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
