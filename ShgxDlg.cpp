// ShgxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "ShgxDlg.h"
#include "ShgxEditDlg.h"


// CShgxDlg 对话框

IMPLEMENT_DYNAMIC(CShgxDlg, CDialog)

CShgxDlg::CShgxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShgxDlg::IDD, pParent)
	, m_mode(0)
	, m_strNB(_T(""))
{

}

CShgxDlg::~CShgxDlg()
{
}

void CShgxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CShgxDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CShgxDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BTN_ADD, &CShgxDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CShgxDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, &CShgxDlg::OnBnClickedBtnDel)
END_MESSAGE_MAP()


// CShgxDlg 消息处理程序

void CShgxDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

BOOL CShgxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.SetExtendedStyle(LVS_EX_FLATSB 
		| LVS_EX_FULLROWSELECT 
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,"关系",LVCFMT_CENTER,100,0);
	m_list.InsertColumn(1,"姓名",LVCFMT_CENTER,100,0);
	m_list.InsertColumn(2,"工作",LVCFMT_CENTER,250,0);

	// 若以“查看”模式打开该对话框，还需要显示人员信息，并将信息框设置为“只读”
	if(m_mode == 1)
	{
		ShowInfo();
		ReadOnlySet();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShgxDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CShgxEditDlg dlg;
	int nCount;
	dlg.m_mode = 0;
	if(IDOK == dlg.DoModal())
	{
		nCount = m_list.GetItemCount();
		m_list.InsertItem(nCount, 0);
		m_list.SetItemText(nCount,0,dlg.m_gx);
		m_list.SetItemText(nCount,1,dlg.m_name);
		m_list.SetItemText(nCount,2,dlg.m_gz);
	}
}

void CShgxDlg::OnBnClickedBtnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	CShgxEditDlg dlg;
	CString str;
	int index = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (index == -1)
	{
		MessageBox("请选择要修改的项");
		return;
	}
	dlg.m_gx = m_list.GetItemText(index, 0);
	dlg.m_name = m_list.GetItemText(index, 1);
	dlg.m_gz = m_list.GetItemText(index, 2);
	dlg.m_mode = 1;
	if(IDOK == dlg.DoModal())
	{
		m_list.SetItemText(index,0,dlg.m_gx);
		m_list.SetItemText(index,1,dlg.m_name);
		m_list.SetItemText(index,2,dlg.m_gz);
	}
}

void CShgxDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CShgxDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CShgxEditDlg dlg;
	CString str;
	int index = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (index == -1)
	{
		MessageBox("请选择要删除的项");
		return;
	}
	if(IDOK == MessageBox("确认删除吗?"))
	{
		m_list.DeleteItem(index);
	}
}

// 显示要查看的人员信息
void CShgxDlg::ShowInfo(void)
{
	// 清除已有的记录
	m_list.DeleteAllItems();

	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
	sql = "select * from cygx where zgbm = " + m_strNB;
	try
	{
		//打开记录集
	m_pRecordset = AdoConn.GetRecordSet(sql);
	//遍历记录集
	while(AdoConn.m_pRecordset->adoEOF==0)
	{
		m_list.InsertItem(0, "");
		//将记录集字段中的记录添加到列表视图控件中
		m_list.SetItemText(0,0,(char *)(_bstr_t)m_pRecordset->GetCollect("brgx"));
		m_list.SetItemText(0,1,(char *)(_bstr_t)m_pRecordset->GetCollect("xm"));
		m_list.SetItemText(0,2,(char *)(_bstr_t)m_pRecordset->GetCollect("hzgz"));
		//指向下一条记录
		m_pRecordset->MoveNext();
	}
	m_pRecordset->Close();
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
}

// 将信息框设置为只读（隐藏三个编辑按钮）
void CShgxDlg::ReadOnlySet(void)
{
	GetDlgItem(IDC_BTN_ADD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_EDIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_HIDE);
}

// 取消信息框的只读状态（显示三个编辑按钮）
void CShgxDlg::ReadOnlyCancel(void)
{
	GetDlgItem(IDC_BTN_ADD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_EDIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_SHOW);
}

void CShgxDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

//	CDialog::OnOK();
}
