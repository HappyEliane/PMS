// ShgxEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "ShgxEditDlg.h"


// CShgxEditDlg 对话框

IMPLEMENT_DYNAMIC(CShgxEditDlg, CDialog)

CShgxEditDlg::CShgxEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShgxEditDlg::IDD, pParent)
	, m_gx(_T(""))
	, m_name(_T(""))
	, m_gz(_T(""))
	, m_mode(0)
{

}

CShgxEditDlg::~CShgxEditDlg()
{
}

void CShgxEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GX, m_gx);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_GZ, m_gz);
}


BEGIN_MESSAGE_MAP(CShgxEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CShgxEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CShgxEditDlg 消息处理程序

void CShgxEditDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	OnOK();
}

BOOL CShgxEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(m_mode == 0)
		SetWindowText("添加社会关系");
	else
	{
		SetWindowText("修改社会关系");
		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShgxEditDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
	return;
}

void CShgxEditDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}
