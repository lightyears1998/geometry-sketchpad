#pragma once


// DialogAddPoint dialog

class DialogAddPoint : public CDialogEx
{
	DECLARE_DYNAMIC(DialogAddPoint)

public:
	DialogAddPoint(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogAddPoint();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_POINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
