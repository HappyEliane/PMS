#pragma once
#include "afxwin.h"


// CGzqkDlg �Ի���

class CGzqkDlg : public CDialog
{
	DECLARE_DYNAMIC(CGzqkDlg)

public:
	CGzqkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGzqkDlg();

// �Ի�������
	enum { IDD = IDD_DLG_GZQK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_BoxBM;
	CComboBox m_BoxZC;
	virtual BOOL OnInitDialog();
	// 0�����½�   1�����鿴
	int m_mode;
	// �鿴ģʽʱ��ָ�����ڲ鿴��Ա�����
	CString m_strNB;
	// ��ʾҪ�鿴����Ա��Ϣ
	void ShowInfo(void);
	// ������Ϣ������Ϊֻ��
	void ReadOnlySet(void);
	// ȡ������Ϣ���ֻ��״̬
	void ReadOnlyCancel(void);
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
