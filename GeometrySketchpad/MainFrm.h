// MainFrm.h: CMainFrame 类的接口


#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDebug();
	afx_msg void OnAddPoint();
	afx_msg void OnMouseSelecton();
	afx_msg void OnMouseDrawTriangle();
	afx_msg void OnMouseDrawRectangle();
	afx_msg void OnMouseDrawPoint();
	afx_msg void OnMouseDrawParallelogram();
	afx_msg void OnMouseDrawLine();
	afx_msg void OnMouseDrawCircle();
	afx_msg void OnViewShapeList();
};


