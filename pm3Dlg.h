// pm3Dlg.h : ͷ�ļ�
//

#pragma once


// Cpm3Dlg �Ի���
class Cpm3Dlg : public CDialog
{
// ����
public:
	Cpm3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PM3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBtnBmwh();
	afx_msg void OnBnClickedBtnDalr();
	afx_msg void OnBnClickedBtnCxbj();
	afx_msg void OnBnClickedBtnTj();
	afx_msg void OnBnClickedBtnGl();
	afx_msg void OnBnClickedOk();
};
