// EditPwDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "EditPwDlg.h"
#include "MDFive.h"

// CEditPwDlg 对话框

IMPLEMENT_DYNAMIC(CEditPwDlg, CDialog)

CEditPwDlg::CEditPwDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPwDlg::IDD, pParent)
	, m_oldpw(_T(""))
	, m_newpw(_T(""))
	, m_newpw2(_T(""))
{

}

CEditPwDlg::~CEditPwDlg()
{
}

void CEditPwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_oldpw);
	DDX_Text(pDX, IDC_EDIT3, m_newpw);
	DDX_Text(pDX, IDC_EDIT4, m_newpw2);
}


BEGIN_MESSAGE_MAP(CEditPwDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CEditPwDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditPwDlg 消息处理程序

void CEditPwDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//检查两次输入的新密码是否一致
	if (m_newpw != m_newpw2)
	{
		AfxMessageBox("两次输入的新密码不一致!");
		return;
	}

	CString md5oldpw, md5newpw, correctPw;
	MDFive md;
	md.SetPlaint(m_oldpw);
	md5oldpw = md.GetCiph();	//计算加密后的旧密码
	md.SetPlaint(m_newpw);
	md5newpw = md.GetCiph();	//计算加密后的新密码

	_RecordsetPtr pRecordset;
	_variant_t var;
	_bstr_t sql = "select userspw from user_table where usersname = '" + CurrentUser + "'";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		if (pRecordset->RecordCount < 1)
		{
			AfxMessageBox("用户名错误!");
			return;
		}
		var = pRecordset->GetCollect("userspw");
		correctPw = var.bstrVal;
		if (correctPw != md5oldpw)
		{
			AfxMessageBox("旧密码输入错误!");
			return;
		}
		sql = "update user_table set userspw = '" +md5newpw + "' where usersname = '" + CurrentUser + "'";
		AdoConn.ExecuteSQL(sql);
		AfxMessageBox("密码修改成功!");
		OnOK();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}
}
