#pragma once


// DialogScale dialog

class DialogScale : public CDialogEx
{
	DECLARE_DYNAMIC(DialogScale)

public:
	DialogScale(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogScale();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double ratio;
	afx_msg void OnBnClickedOk();
};
