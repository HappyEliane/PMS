#pragma once
#include "afxcmn.h"


// CShgxDlg 对话框

class CShgxDlg : public CDialog
{
	DECLARE_DYNAMIC(CShgxDlg)

public:
	CShgxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShgxDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SHGX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedBtnDel();
	// 0——新建   1——查看
	int m_mode;
	// 查看模式时，指出现在查看的员工编号
	CString m_strNB;
	// 显示要查看的人员信息
	void ShowInfo(void);
	// 将信息框设置为只读（隐藏三个编辑按钮）
	void ReadOnlySet(void);
	// 取消信息框的只读状态（显示三个编辑按钮）
	void ReadOnlyCancel(void);
protected:
	virtual void OnOK();
};
