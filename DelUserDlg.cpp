// DelUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "DelUserDlg.h"


// CDelUserDlg 对话框

IMPLEMENT_DYNAMIC(CDelUserDlg, CDialog)

CDelUserDlg::CDelUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelUserDlg::IDD, pParent)
	, m_un(_T(""))
{

}

CDelUserDlg::~CDelUserDlg()
{
}

void CDelUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_un);
}


BEGIN_MESSAGE_MAP(CDelUserDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CDelUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDelUserDlg 消息处理程序

void CDelUserDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_un == CurrentUser)
	{
		AfxMessageBox("不允许删除当前账户！");
		return;
	}

	_RecordsetPtr pRecordset;
	_variant_t var;
	_bstr_t sql = "select userspw from user_table where usersname = '" + m_un + "'";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		if (pRecordset->RecordCount <1)
		{
			AfxMessageBox("用户不存在!");
			return;
		}
		sql = "delete from user_table where usersname = '" +m_un + "'";
		AdoConn.ExecuteSQL(sql);
		AfxMessageBox("用户"+ m_un + "删除成功!");
		OnOK();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}
}
