// AddUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "AddUserDlg.h"
#include "MDFive.h"


// CAddUserDlg 对话框

IMPLEMENT_DYNAMIC(CAddUserDlg, CDialog)

CAddUserDlg::CAddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddUserDlg::IDD, pParent)
	, m_un(_T(""))
	, m_pw(_T(""))
	, m_pw2(_T(""))
{

}

CAddUserDlg::~CAddUserDlg()
{
}

void CAddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UN, m_un);
	DDX_Text(pDX, IDC_EDIT_PW, m_pw);
	DDX_Text(pDX, IDC_EDIT_PW2, m_pw2);
}


BEGIN_MESSAGE_MAP(CAddUserDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddUserDlg 消息处理程序

void CAddUserDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_un.Trim();
	if (m_un.GetLength() == 0)
	{
		AfxMessageBox("请输入用户名");
		return;
	}
	if (m_pw.GetLength() == 0)
	{
		AfxMessageBox("请输入密码");
		return;
	}
	if (m_pw != m_pw2)
	{
		AfxMessageBox("两次输入的密码不一致");
		return;
	}

	CString md5pw;
	MDFive md;
	md.SetPlaint(m_pw);
	md5pw = md.GetCiph();	//计算加密后的旧密码


	_RecordsetPtr pRecordset;
	_variant_t var;
	_bstr_t sql = "select userspw from user_table where usersname = '" + m_un + "'";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		if (pRecordset->RecordCount >0)
		{
			AfxMessageBox("用户名已存在!");
			return;
		}
		sql = "insert into user_table values('" +m_un + "', '" + md5pw + "')";
		AdoConn.ExecuteSQL(sql);
		AfxMessageBox("用户成功添加!");
		OnOK();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}
}
