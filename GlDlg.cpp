// GlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "GlDlg.h"
#include "EditPwDlg.h"
#include "AddUserDlg.h"
#include "DelUserDlg.h"


// CGlDlg �Ի���

IMPLEMENT_DYNAMIC(CGlDlg, CDialog)

CGlDlg::CGlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGlDlg::IDD, pParent)
{

}

CGlDlg::~CGlDlg()
{
}

void CGlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGlDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_BACKUP, &CGlDlg::OnBnClickedBtnBackup)
	ON_BN_CLICKED(IDC_BTN_RECOVERY, &CGlDlg::OnBnClickedBtnRecovery)
	ON_BN_CLICKED(IDC_BTN_EDITPW, &CGlDlg::OnBnClickedBtnEditpw)
	ON_BN_CLICKED(IDC_BTN_ADDUSER, &CGlDlg::OnBnClickedBtnAdduser)
	ON_BN_CLICKED(IDC_BTN_DELUSER, &CGlDlg::OnBnClickedBtnDeluser)
END_MESSAGE_MAP()


// CGlDlg ��Ϣ�������

void CGlDlg::OnBnClickedBtnBackup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(FALSE, "bak", "*.bak", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "�����ļ� (*.bak)|*.bak|All Files (*.*)|*.*||");
	if(IDOK == dlg.DoModal())
	{
	//	AdoConn.ExitConnect();
		CString FilePath = dlg.GetPathName();
		AdoConn.BackUp(FilePath);
	//	AdoConn.OnInitADOConn();
	}
}

void CGlDlg::OnBnClickedBtnRecovery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, "bak", "*.bak", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "�����ļ� (*.bak)|*.bak|All Files (*.*)|*.*||");
	if(IDOK == dlg.DoModal())
	{
		AdoConn.ExitConnect();
		CString FilePath = dlg.GetPathName();
		AdoConn.Recovery(FilePath);
		AdoConn.OnInitADOConn();
	}
}

void CGlDlg::OnBnClickedBtnEditpw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEditPwDlg dlg;
	dlg.DoModal();
}

BOOL CGlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_EDIT_CURRENT, CurrentUser);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CGlDlg::OnBnClickedBtnAdduser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAddUserDlg dlg;
	dlg.DoModal();
}

void CGlDlg::OnBnClickedBtnDeluser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDelUserDlg dlg;
	dlg.DoModal();
}
