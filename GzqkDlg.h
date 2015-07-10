#pragma once
#include "afxwin.h"


// CGzqkDlg 对话框

class CGzqkDlg : public CDialog
{
	DECLARE_DYNAMIC(CGzqkDlg)

public:
	CGzqkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGzqkDlg();

// 对话框数据
	enum { IDD = IDD_DLG_GZQK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_BoxBM;
	CComboBox m_BoxZC;
	virtual BOOL OnInitDialog();
	// 0——新建   1——查看
	int m_mode;
	// 查看模式时，指出现在查看的员工编号
	CString m_strNB;
	// 显示要查看的人员信息
	void ShowInfo(void);
	// 将各信息框设置为只读
	void ReadOnlySet(void);
	// 取消各信息框的只读状态
	void ReadOnlyCancel(void);
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
