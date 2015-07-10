#pragma once


// CDelUserDlg 对话框

class CDelUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CDelUserDlg)

public:
	CDelUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDelUserDlg();

// 对话框数据
	enum { IDD = IDD_DLG_DELUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 待删除的账户名
	CString m_un;
	afx_msg void OnBnClickedOk();
};
