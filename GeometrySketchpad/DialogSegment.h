#pragma once


// DialogSegment dialog

class DialogSegment : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSegment)

public:
	DialogSegment(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogSegment();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEGMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double coordinate_x1;
	double coordinate_y1;
	double coordinate_x2;
	double coordinate_y2;
};
