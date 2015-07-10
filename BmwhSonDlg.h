#pragma once
#include "afxcmn.h"


// CBmwhSonDlg 对话框

class CBmwhSonDlg : public CDialog
{
	DECLARE_DYNAMIC(CBmwhSonDlg)

public:
	CBmwhSonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBmwhSonDlg();

// 对话框数据
	enum { IDD = IDD_DLG_BMWH_SON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 0 职称编码表   1 部门编码表   2 文化程度编码表
	int m_table;
	virtual BOOL OnInitDialog();
	(CWnd *) m_AddCtrlArr[7];
	(CWnd *) m_EditCtrlArr[11];
	//显示“添加编码”区域
	void ShowAddFace(void);
	// 隐藏“添加编码”区域
	void HideAddFace(void);
	// 显示“修改编码”区域
	void ShowEditFace(void);
	// 隐藏“修改编码”区域
	void HideEditFace(void);

	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
	// 刷新对话框，重新显示数据列表
	void ReOpen(void);
	CListCtrl m_list;
	_RecordsetPtr m_pRecordset;
	// 表示当前处于编辑状态，m_pRecordset的位置不应被改变。
	bool m_lock;
	CString m_columnName1;
	CString m_columnName2;
	CString m_tableName;
	// 重置表名与列名
	void ResetColumnName(void);
	afx_msg void OnBnClickedBtnQrtj();
	afx_msg void OnBnClickedBtnQrxg();
	afx_msg void OnBnClickedBtnCancle1();
	afx_msg void OnBnClickedBtnCancle2();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
