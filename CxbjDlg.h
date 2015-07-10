#pragma once


// CCxbjDlg 对话框

class CCxbjDlg : public CDialog
{
	DECLARE_DYNAMIC(CCxbjDlg)

public:
	CCxbjDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCxbjDlg();

// 对话框数据
	enum { IDD = IDD_DLG_CXBJ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSearJq();
	afx_msg void OnBnClickedBtnSearMh();
	// 记录集指针
	_RecordsetPtr m_pRecordset;
	// 显示当前记录中的内容
	void ShowInfo(void);
	// 清空个人信息区域的内容
	void ClearInfo(void);
	afx_msg void OnBnClickedBtnFirst();
	afx_msg void OnBnClickedBtnPre();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnLast();
	afx_msg void OnBnClickedBtnDetail();
	afx_msg void OnBnClickedBtnExit();
};
