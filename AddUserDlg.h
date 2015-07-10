#pragma once


// CAddUserDlg 对话框

class CAddUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddUserDlg)

public:
	CAddUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddUserDlg();

// 对话框数据
	enum { IDD = IDD_DLG_ADDUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 用户名
	CString m_un;
	afx_msg void OnBnClickedOk();
	// 密码
	CString m_pw;
	// 密码
	CString m_pw2;
};
