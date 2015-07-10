// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "LoginDlg.h"
#include "MDFive.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_userName(_T(""))
	, m_passWord(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UN, m_userName);
	DDX_Text(pDX, IDC_EDIT_PW, m_passWord);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	CString md5pw, correctPw;
	MDFive md;
	md.SetPlaint(m_passWord);
	md5pw = md.GetCiph();	//计算加密后的密码

	_RecordsetPtr pRecordset;
	_variant_t var;
	//获得数据库中的散列密码的查询语句
	_bstr_t sql = "select userspw from user_table where usersname = '" + m_userName + "'";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);	//执行查询
		if (pRecordset->RecordCount < 1)
		{
			AfxMessageBox("用户名错误!");
			return;
		}
		var = pRecordset->GetCollect("userspw");//获得密码
		if (var.vt = VT_BSTR)
		{
			correctPw = var.bstrVal;
		}
		if (correctPw != md5pw)					//密码比较
		{
			AfxMessageBox("密码错误!");
			return;
		}
		CurrentUser = m_userName;
		OnOK();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_userName = "admin";
	//m_passWord = "123";
	//UpdateData(FALSE);
	GetDlgItem(IDC_EDIT_UN)->GetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
