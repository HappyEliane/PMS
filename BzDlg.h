#pragma once


// CBzDlg 对话框

class CBzDlg : public CDialog
{
	DECLARE_DYNAMIC(CBzDlg)

public:
	CBzDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBzDlg();

// 对话框数据
	enum { IDD = IDD_DLG_BZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 0——新建   1——查看
	int m_mode;
	// 查看模式时，指出现在查看的员工编号
	CString m_strNB;
	// 显示要查看的人员信息
	void ShowInfo(void);
	// 将信息框设置为只读
	void ReadOnlySet(void);
	// 取消信息框的只读状态
	void ReadOnlyCancel(void);
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
