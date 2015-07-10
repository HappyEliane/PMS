#pragma once


// CShgxEditDlg 对话框

class CShgxEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CShgxEditDlg)

public:
	CShgxEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShgxEditDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SHGX_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_gx;
	CString m_name;
	CString m_gz;
	afx_msg void OnBnClickedOk();
	// 0 添加   1 修改
	int m_mode;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
