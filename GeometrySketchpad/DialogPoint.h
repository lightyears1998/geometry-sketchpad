#pragma once


// DialogPoint dialog

class DialogPoint : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPoint)

public:
	DialogPoint(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogPoint();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double coordinate_x;
	double coordinate_y;
};
