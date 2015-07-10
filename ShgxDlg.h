#pragma once
#include "afxcmn.h"


// CShgxDlg �Ի���

class CShgxDlg : public CDialog
{
	DECLARE_DYNAMIC(CShgxDlg)

public:
	CShgxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShgxDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SHGX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// 0�����½�   1�����鿴
	int m_mode;
	// �鿴ģʽʱ��ָ�����ڲ鿴��Ա�����
	CString m_strNB;
	// ��ʾҪ�鿴����Ա��Ϣ
	void ShowInfo(void);
	// ����Ϣ������Ϊֻ�������������༭��ť��
	void ReadOnlySet(void);
	// ȡ����Ϣ���ֻ��״̬����ʾ�����༭��ť��
	void ReadOnlyCancel(void);
protected:
	virtual void OnOK();
};
