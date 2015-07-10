#pragma once
#include "jbxxdlg.h"
#include "afxcmn.h"
#include "gzqkdlg.h"
#include "shgxdlg.h"
#include "bzdlg.h"


// CDalrDlg 对话框

class CDalrDlg : public CDialog
{
	DECLARE_DYNAMIC(CDalrDlg)

public:
	CDalrDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDalrDlg();

// 对话框数据
	enum { IDD = IDD_DLG_DALR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 基本信息对话框
	CJbxxDlg jbxxDlg;
	virtual BOOL OnInitDialog();
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	// 工作情况对话框
	CGzqkDlg gzqkDlg;
	// 社会关系对话框
	CShgxDlg shgxDlg;
	// 备注对话框
	CBzDlg bzDlg;
	afx_msg void OnBnClickedOk();
	_RecordsetPtr m_pRecordset;
	// 向记录表中添加新的人员记录
	void AddInfo(void);
	// 0 新建   1 查看   2 修改
	int m_mode;
	// 当前显示的职工编码
	CString strNB;
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnSave();
	// 向m_pRecordset中的各个字段添加信息
	void SetData(void);
	afx_msg void OnBnClickedBtnDel();
	// 删除标记
	int m_Del;
	afx_msg void OnBnClickedBtnPrintView();
	afx_msg void OnBnClickedBtnPrint();
	// 打印的消息响应函数
	afx_msg LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);

private:
	CFont  m_fontPrinter; //打印机字体
	UINT   m_cyPrinter; //打印机行距
public:
	afx_msg void OnBnClickedBtnExit();
};
