#pragma once


// CEditPwDlg �Ի���

class CEditPwDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditPwDlg)

public:
	CEditPwDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditPwDlg();

// �Ի�������
	enum { IDD = IDD_DLG_EDITPW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ������
	CString m_oldpw;
	CString m_newpw;
	CString m_newpw2;
	afx_msg void OnBnClickedOk();
};
