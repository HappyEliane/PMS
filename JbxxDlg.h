#pragma once
#include "afxwin.h"


// CJbxxDlg �Ի���

class CJbxxDlg : public CDialog
{
	DECLARE_DYNAMIC(CJbxxDlg)

public:
	CJbxxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CJbxxDlg();

// �Ի�������
	enum { IDD = IDD_DLG_JBXX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit4();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	CComboBox m_BoxWH;
	CComboBox m_BoxXB;
	afx_msg void OnBnClickedOk();
	// 0�����½�   1�����鿴
	int m_mode;
	CString m_strNB;
	// ��ʾҪ�鿴����Ա��Ϣ
	void ShowInfo(void);
	// ������Ϣ������Ϊֻ��
	void ReadOnlySet(void);
	// ȡ������Ϣ���ֻ��״̬
	void ReadOnlyCancel(void);
	afx_msg void OnCbnSelchangeComboSex();
};
