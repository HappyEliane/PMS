// BmwhDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "BmwhDlg.h"


// CBmwhDlg 对话框

IMPLEMENT_DYNAMIC(CBmwhDlg, CDialog)

CBmwhDlg::CBmwhDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBmwhDlg::IDD, pParent)
{

}

CBmwhDlg::~CBmwhDlg()
{
}

void CBmwhDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CBmwhDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CBmwhDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDOK, &CBmwhDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBmwhDlg 消息处理程序

BOOL CBmwhDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_tab.InsertItem(0,"职称编码");
	m_tab.InsertItem(1,"部门编码");
	m_tab.InsertItem(2,"文化程度编码");
	m_sonDlg.m_table = 0;
	m_sonDlg.Create(IDD_DLG_BMWH_SON,GetDlgItem(IDC_TAB1));
	CRect rect;
	m_tab.GetClientRect(&rect);
	rect.top += 25;
	rect.bottom -= 4;
	rect.left += 4;
	rect.right -= 4;
	m_sonDlg.MoveWindow(&rect);
	m_sonDlg.ShowWindow(SW_SHOW);
	m_sonDlg.ReOpen();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CBmwhDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = m_tab.GetCurSel();
	m_sonDlg.m_table = sel;
	m_sonDlg.ReOpen();

	*pResult = 0;
}

void CBmwhDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}
