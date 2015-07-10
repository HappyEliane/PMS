#pragma once
#include "jbxxdlg.h"
#include "afxcmn.h"
#include "gzqkdlg.h"
#include "shgxdlg.h"
#include "bzdlg.h"


// CDalrDlg �Ի���

class CDalrDlg : public CDialog
{
	DECLARE_DYNAMIC(CDalrDlg)

public:
	CDalrDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDalrDlg();

// �Ի�������
	enum { IDD = IDD_DLG_DALR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ������Ϣ�Ի���
	CJbxxDlg jbxxDlg;
	virtual BOOL OnInitDialog();
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	// ��������Ի���
	CGzqkDlg gzqkDlg;
	// ����ϵ�Ի���
	CShgxDlg shgxDlg;
	// ��ע�Ի���
	CBzDlg bzDlg;
	afx_msg void OnBnClickedOk();
	_RecordsetPtr m_pRecordset;
	// ���¼��������µ���Ա��¼
	void AddInfo(void);
	// 0 �½�   1 �鿴   2 �޸�
	int m_mode;
	// ��ǰ��ʾ��ְ������
	CString strNB;
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnSave();
	// ��m_pRecordset�еĸ����ֶ������Ϣ
	void SetData(void);
	afx_msg void OnBnClickedBtnDel();
	// ɾ�����
	int m_Del;
	afx_msg void OnBnClickedBtnPrintView();
	afx_msg void OnBnClickedBtnPrint();
	// ��ӡ����Ϣ��Ӧ����
	afx_msg LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);

private:
	CFont  m_fontPrinter; //��ӡ������
	UINT   m_cyPrinter; //��ӡ���о�
public:
	afx_msg void OnBnClickedBtnExit();
};
