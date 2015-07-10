// BzDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "BzDlg.h"


// CBzDlg 对话框

IMPLEMENT_DYNAMIC(CBzDlg, CDialog)

CBzDlg::CBzDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBzDlg::IDD, pParent)
	, m_mode(0)
	, m_strNB(_T(""))
{

}

CBzDlg::~CBzDlg()
{
}

void CBzDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBzDlg, CDialog)
END_MESSAGE_MAP()


BOOL CBzDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 若以“查看”模式打开该对话框，还需要显示人员信息，并将信息框设置为“只读”
	if(m_mode == 1)
	{
		ShowInfo();
		ReadOnlySet();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


// 显示要查看的人员信息
void CBzDlg::ShowInfo(void)
{
	CString str1;
	_RecordsetPtr m_pRecordset;
	_variant_t   var;			// 用于判断是否为null
	_bstr_t sql;
	sql = "select bz from m_dadj where zgbm = " + m_strNB;
	try
	{
		//打开记录集
		m_pRecordset = AdoConn.GetRecordSet(sql);
		//获得信息
		var = m_pRecordset->GetCollect("bz");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_BZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_BZ,"");
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
}

// 将信息框设置为只读
void CBzDlg::ReadOnlySet(void)
{
	((CEdit *)GetDlgItem(IDC_EDIT_BZ))->SetReadOnly();		//备注
}

// 取消信息框的只读状态
void CBzDlg::ReadOnlyCancel(void)
{
	((CEdit *)GetDlgItem(IDC_EDIT_BZ))->SetReadOnly(FALSE);	//备注
}


void CBzDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CBzDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}
