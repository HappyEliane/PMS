#pragma once


// CAddUserDlg �Ի���

class CAddUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddUserDlg)

public:
	CAddUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddUserDlg();

// �Ի�������
	enum { IDD = IDD_DLG_ADDUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �û���
	CString m_un;
	afx_msg void OnBnClickedOk();
	// ����
	CString m_pw;
	// ����
	CString m_pw2;
};
