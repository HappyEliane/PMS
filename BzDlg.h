#pragma once


// CBzDlg �Ի���

class CBzDlg : public CDialog
{
	DECLARE_DYNAMIC(CBzDlg)

public:
	CBzDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBzDlg();

// �Ի�������
	enum { IDD = IDD_DLG_BZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// 0�����½�   1�����鿴
	int m_mode;
	// �鿴ģʽʱ��ָ�����ڲ鿴��Ա�����
	CString m_strNB;
	// ��ʾҪ�鿴����Ա��Ϣ
	void ShowInfo(void);
	// ����Ϣ������Ϊֻ��
	void ReadOnlySet(void);
	// ȡ����Ϣ���ֻ��״̬
	void ReadOnlyCancel(void);
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
