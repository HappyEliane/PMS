#pragma once


// CDelUserDlg �Ի���

class CDelUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CDelUserDlg)

public:
	CDelUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDelUserDlg();

// �Ի�������
	enum { IDD = IDD_DLG_DELUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ɾ�����˻���
	CString m_un;
	afx_msg void OnBnClickedOk();
};
