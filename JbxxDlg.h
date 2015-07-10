#pragma once
#include "afxwin.h"


// CJbxxDlg 对话框

class CJbxxDlg : public CDialog
{
	DECLARE_DYNAMIC(CJbxxDlg)

public:
	CJbxxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJbxxDlg();

// 对话框数据
	enum { IDD = IDD_DLG_JBXX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit4();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	CComboBox m_BoxWH;
	CComboBox m_BoxXB;
	afx_msg void OnBnClickedOk();
	// 0——新建   1——查看
	int m_mode;
	CString m_strNB;
	// 显示要查看的人员信息
	void ShowInfo(void);
	// 将各信息框设置为只读
	void ReadOnlySet(void);
	// 取消各信息框的只读状态
	void ReadOnlyCancel(void);
	afx_msg void OnCbnSelchangeComboSex();
};
