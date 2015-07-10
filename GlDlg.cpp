// GlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "GlDlg.h"
#include "EditPwDlg.h"
#include "AddUserDlg.h"
#include "DelUserDlg.h"


// CGlDlg 对话框

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


// CGlDlg 消息处理程序

void CGlDlg::OnBnClickedBtnBackup()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(FALSE, "bak", "*.bak", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "备份文件 (*.bak)|*.bak|All Files (*.*)|*.*||");
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
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, "bak", "*.bak", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "备份文件 (*.bak)|*.bak|All Files (*.*)|*.*||");
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
	// TODO: 在此添加控件通知处理程序代码
	CEditPwDlg dlg;
	dlg.DoModal();
}

BOOL CGlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT_CURRENT, CurrentUser);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGlDlg::OnBnClickedBtnAdduser()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddUserDlg dlg;
	dlg.DoModal();
}

void CGlDlg::OnBnClickedBtnDeluser()
{
	// TODO: 在此添加控件通知处理程序代码
	CDelUserDlg dlg;
	dlg.DoModal();
}
