#pragma once


// CShgxEditDlg �Ի���

class CShgxEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CShgxEditDlg)

public:
	CShgxEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShgxEditDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SHGX_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_gx;
	CString m_name;
	CString m_gz;
	afx_msg void OnBnClickedOk();
	// 0 ���   1 �޸�
	int m_mode;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
