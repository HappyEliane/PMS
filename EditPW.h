#pragma once


// CEditPW �Ի���

class CEditPW : public CDialog
{
	DECLARE_DYNAMIC(CEditPW)

public:
	CEditPW(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditPW();

// �Ի�������
	enum { IDD = IDD_DLG_EDITPW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
