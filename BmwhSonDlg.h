#pragma once
#include "afxcmn.h"


// CBmwhSonDlg �Ի���

class CBmwhSonDlg : public CDialog
{
	DECLARE_DYNAMIC(CBmwhSonDlg)

public:
	CBmwhSonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBmwhSonDlg();

// �Ի�������
	enum { IDD = IDD_DLG_BMWH_SON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// 0 ְ�Ʊ����   1 ���ű����   2 �Ļ��̶ȱ����
	int m_table;
	virtual BOOL OnInitDialog();
	(CWnd *) m_AddCtrlArr[7];
	(CWnd *) m_EditCtrlArr[11];
	//��ʾ����ӱ��롱����
	void ShowAddFace(void);
	// ���ء���ӱ��롱����
	void HideAddFace(void);
	// ��ʾ���޸ı��롱����
	void ShowEditFace(void);
	// ���ء��޸ı��롱����
	void HideEditFace(void);

	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
	// ˢ�¶Ի���������ʾ�����б�
	void ReOpen(void);
	CListCtrl m_list;
	_RecordsetPtr m_pRecordset;
	// ��ʾ��ǰ���ڱ༭״̬��m_pRecordset��λ�ò�Ӧ���ı䡣
	bool m_lock;
	CString m_columnName1;
	CString m_columnName2;
	CString m_tableName;
	// ���ñ���������
	void ResetColumnName(void);
	afx_msg void OnBnClickedBtnQrtj();
	afx_msg void OnBnClickedBtnQrxg();
	afx_msg void OnBnClickedBtnCancle1();
	afx_msg void OnBnClickedBtnCancle2();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
