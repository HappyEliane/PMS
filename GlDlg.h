#pragma once


// CGlDlg �Ի���

class CGlDlg : public CDialog
{
	DECLARE_DYNAMIC(CGlDlg)

public:
	CGlDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGlDlg();

// �Ի�������
	enum { IDD = IDD_DLG_GL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBackup();
	afx_msg void OnBnClickedBtnRecovery();
	afx_msg void OnBnClickedBtnEditpw();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAdduser();
	afx_msg void OnBnClickedBtnDeluser();
};
