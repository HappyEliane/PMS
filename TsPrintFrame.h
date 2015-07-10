#pragma once
#include "TsPrintView.h"

#define	UM_TS_PRINT			      WM_USER+1
#define	UM_TS_BEGIN_PRINTING	  WM_USER+2
#define	UM_TS_END_PRINTING		  WM_USER+3

// CTsPrintFrame 框架

class CTsPrintFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CTsPrintFrame)
protected:
	CTsPrintFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CTsPrintFrame();

public:
	void Print(void);
	void PreviewPrint(void);
	CDialog *m_pCallerDlg;
private:
	// 视类窗口
	CTsPrintView *m_pView;
	// 主窗口
	CWnd *m_pMainWnd;

// Operations
public:
	CTsPrintFrame(CDialog * pCallerDlg); 

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTsPrintFrame)
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTsPrintFrame)
	afx_msg void OnDestroy();
	//}}AFX_MSG


protected:
	DECLARE_MESSAGE_MAP()
};


