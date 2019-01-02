#pragma once


// DialogCircle 对话框

class DialogCircle : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCircle)

public:
	DialogCircle(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogCircle();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIRCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double coordinate_x;
	double coordinate_y;
	double radius;
};
