#pragma once
#include "afxcmn.h"
#include "bmwhsondlg.h"


// CBmwhDlg 对话框

class CBmwhDlg : public CDialog
{
	DECLARE_DYNAMIC(CBmwhDlg)

public:
	CBmwhDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBmwhDlg();

// 对话框数据
	enum { IDD = IDD_DLG_BMWH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	virtual BOOL OnInitDialog();
	CBmwhSonDlg m_sonDlg;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
