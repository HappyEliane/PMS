#pragma once


// CCxbjDlg �Ի���

class CCxbjDlg : public CDialog
{
	DECLARE_DYNAMIC(CCxbjDlg)

public:
	CCxbjDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCxbjDlg();

// �Ի�������
	enum { IDD = IDD_DLG_CXBJ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSearJq();
	afx_msg void OnBnClickedBtnSearMh();
	// ��¼��ָ��
	_RecordsetPtr m_pRecordset;
	// ��ʾ��ǰ��¼�е�����
	void ShowInfo(void);
	// ��ո�����Ϣ���������
	void ClearInfo(void);
	afx_msg void OnBnClickedBtnFirst();
	afx_msg void OnBnClickedBtnPre();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnLast();
	afx_msg void OnBnClickedBtnDetail();
	afx_msg void OnBnClickedBtnExit();
};
