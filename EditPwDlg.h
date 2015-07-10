#pragma once


// CEditPwDlg 对话框

class CEditPwDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditPwDlg)

public:
	CEditPwDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditPwDlg();

// 对话框数据
	enum { IDD = IDD_DLG_EDITPW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 旧密码
	CString m_oldpw;
	CString m_newpw;
	CString m_newpw2;
	afx_msg void OnBnClickedOk();
};
