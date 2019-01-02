#pragma once


// DialogMove dialog

class DialogMove : public CDialogEx
{
	DECLARE_DYNAMIC(DialogMove)

public:
	DialogMove(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogMove();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double dx;
	double dy;
};
