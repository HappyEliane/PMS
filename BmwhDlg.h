#pragma once
#include "afxcmn.h"
#include "bmwhsondlg.h"


// CBmwhDlg �Ի���

class CBmwhDlg : public CDialog
{
	DECLARE_DYNAMIC(CBmwhDlg)

public:
	CBmwhDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBmwhDlg();

// �Ի�������
	enum { IDD = IDD_DLG_BMWH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	virtual BOOL OnInitDialog();
	CBmwhSonDlg m_sonDlg;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
