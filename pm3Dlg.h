// pm3Dlg.h : 头文件
//

#pragma once


// Cpm3Dlg 对话框
class Cpm3Dlg : public CDialog
{
// 构造
public:
	Cpm3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PM3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBtnBmwh();
	afx_msg void OnBnClickedBtnDalr();
	afx_msg void OnBnClickedBtnCxbj();
	afx_msg void OnBnClickedBtnTj();
	afx_msg void OnBnClickedBtnGl();
	afx_msg void OnBnClickedOk();
};
