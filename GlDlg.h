#pragma once


// CGlDlg 对话框

class CGlDlg : public CDialog
{
	DECLARE_DYNAMIC(CGlDlg)

public:
	CGlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGlDlg();

// 对话框数据
	enum { IDD = IDD_DLG_GL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBackup();
	afx_msg void OnBnClickedBtnRecovery();
	afx_msg void OnBnClickedBtnEditpw();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAdduser();
	afx_msg void OnBnClickedBtnDeluser();
};
