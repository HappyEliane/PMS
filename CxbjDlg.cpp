// CxbjDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "CxbjDlg.h"
#include "DalrDlg.h"

// CCxbjDlg 对话框

IMPLEMENT_DYNAMIC(CCxbjDlg, CDialog)

CCxbjDlg::CCxbjDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCxbjDlg::IDD, pParent)
{
	m_pRecordset = NULL;
}

CCxbjDlg::~CCxbjDlg()
{
}

void CCxbjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCxbjDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SEAR_JQ, &CCxbjDlg::OnBnClickedBtnSearJq)
	ON_BN_CLICKED(IDC_BTN_SEAR_MH, &CCxbjDlg::OnBnClickedBtnSearMh)
	ON_BN_CLICKED(IDC_BTN_FIRST, &CCxbjDlg::OnBnClickedBtnFirst)
	ON_BN_CLICKED(IDC_BTN_PRE, &CCxbjDlg::OnBnClickedBtnPre)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CCxbjDlg::OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_LAST, &CCxbjDlg::OnBnClickedBtnLast)
	ON_BN_CLICKED(IDC_BTN_DETAIL, &CCxbjDlg::OnBnClickedBtnDetail)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CCxbjDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CCxbjDlg 消息处理程序

BOOL CCxbjDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//默认为按姓名查询
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCxbjDlg::OnBnClickedBtnSearJq()
{
	// TODO: 在此添加控件通知处理程序代码
	_bstr_t sql;
	CString str,strResult,strCount;
	if (m_pRecordset)
	{
		m_pRecordset->Close();
	}
	switch (GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2))
	{
	case IDC_RADIO1:
		GetDlgItemText(IDC_SEARCH_NAME,str);
		str.Trim();
		str = "'" + str + "'";
		sql = "select * from m_dadj where xm like " + str;
		strResult = "当前查询方式：精确查询。姓名为 " + str + " 的员工共";
		break;
	case IDC_RADIO2:
		GetDlgItemText(IDC_SEARCH_NB,str);
		str.Trim();
		sql = "select * from m_dadj where zgbm = " + str;
		strResult = "当前查询方式：精确查询。编号为 " + str + " 的员工共";
		break;
	}
	m_pRecordset = AdoConn.GetRecordSet(sql);
	strCount.Format("%d",m_pRecordset->RecordCount);
	strResult = strResult + strCount + "人";
	SetDlgItemText(IDC_STATE,strResult);
	ShowInfo();
}

void CCxbjDlg::OnBnClickedBtnSearMh()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str,strResult,strCount;
	_bstr_t sql;
	switch (GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2))
	{
	case IDC_RADIO1:
		GetDlgItemText(IDC_SEARCH_NAME,str);
		str.Trim();
		strResult = "当前查询方式：模糊查询。姓名中包括 '" + str + "' 的员工共";
		str = "'%" + str + "%'";
		sql = "select * from m_dadj where xm like " + str;
		break;
	case IDC_RADIO2:
		MessageBox("模糊查询只支持按姓名查找");
		SetDlgItemText(IDC_STATE,"");
		return;
		break;
	}
	if (m_pRecordset)
	{
		m_pRecordset->Close();
	}
	m_pRecordset = AdoConn.GetRecordSet(sql);
	strCount.Format("%d",m_pRecordset->RecordCount);
	strResult = strResult + strCount + "人";
	SetDlgItemText(IDC_STATE,strResult);
	ShowInfo();
}

// 显示当前记录中的内容
void CCxbjDlg::ShowInfo(void)
{
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("未找到相应的记录");
		ClearInfo();
		return;
	}
	if (m_pRecordset->BOF)
	{
		MessageBox("已到达第一条记录");
		return;
	}
	if (m_pRecordset->adoEOF)
	{
		MessageBox("已到达最后一条记录");
		return;
	}

	CString str1,str2,nb;
	_RecordsetPtr p;		//用于查询部门名、职称名
	_variant_t   var;		//用于判断是否为null
	try
	{
		//职工编码
		nb = (char *)(_bstr_t)m_pRecordset->GetCollect("zgbm");
		SetDlgItemText(IDC_EDIT_NB,nb);
		//姓名
		str1 = (char *)(_bstr_t)m_pRecordset->GetCollect("xm");
		SetDlgItemText(IDC_EDIT_NAME,str1);
		//性别
		var = m_pRecordset->GetCollect("xb");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_SEX,str1);
		}else{
			SetDlgItemText(IDC_EDIT_SEX,"");
		}
		//部门
		var = m_pRecordset->GetCollect("bmbm");
		if(var.vt != VT_NULL)
		{
			str2 = (char *)(_bstr_t)var;
			p = AdoConn.GetRecordSet((LPCTSTR)("select bmm from bm_bm where bmbm = '" + str2 +"'"));
			str1 = (char *)(_bstr_t)p->GetCollect("bmm");
			SetDlgItemText(IDC_EDIT_BM,str1);
		}else{
			SetDlgItemText(IDC_EDIT_BM,"");
		}
		//职务
		var = m_pRecordset->GetCollect("zw");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ZW,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZW,"");
		}
		//职称
		var = m_pRecordset->GetCollect("zcbm");
		if(var.vt!=VT_NULL)
		{
			str2 = (char *)(_bstr_t)var;
			p = AdoConn.GetRecordSet((LPCTSTR)("select zcmc from bm_zc where zcbm = '" + str2 +"'"));
			str1 = (char *)(_bstr_t)p->GetCollect("zcmc");
			SetDlgItemText(IDC_EDIT_ZC,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZC,"");
		}
		//工种
		var = m_pRecordset->GetCollect("gzm");
		if (var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_GZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_GZ,"");
		}
		//人员状态
		var = m_pRecordset->GetCollect("ryzt");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_RYZT,str1);
		}else{
			SetDlgItemText(IDC_EDIT_RYZT,"");
		}
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
}

// 清空个人信息区域的内容
void CCxbjDlg::ClearInfo(void)
{
	SetDlgItemText(IDC_EDIT_NB,"");
	SetDlgItemText(IDC_EDIT_NAME,"");
	SetDlgItemText(IDC_EDIT_SEX,"");
	SetDlgItemText(IDC_EDIT_BM,"");
	SetDlgItemText(IDC_EDIT_ZW,"");
	SetDlgItemText(IDC_EDIT_ZC,"");
	SetDlgItemText(IDC_EDIT_GZ,"");
	SetDlgItemText(IDC_EDIT_RYZT,"");
}

// 显示第一条记录
void CCxbjDlg::OnBnClickedBtnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("当前没有可显示的记录");
		ClearInfo();
		return;
	}
	m_pRecordset->MoveFirst();
	ShowInfo();
}

// 显示上一条记录
void CCxbjDlg::OnBnClickedBtnPre()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("当前没有可显示的记录");
		ClearInfo();
		return;
	}
	if (m_pRecordset->BOF)
	{
		MessageBox("已到达第一条记录");
		return;
	}
	m_pRecordset->MovePrevious();
	ShowInfo();
}

// 显示下一条记录
void CCxbjDlg::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("当前没有可显示的记录");
		ClearInfo();
		return;
	}
	if (m_pRecordset->adoEOF)
	{
		MessageBox("已到达最后一条记录");
		return;
	}
	m_pRecordset->MoveNext();
	ShowInfo();
}

//显示最后一条记录
void CCxbjDlg::OnBnClickedBtnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("当前没有可显示的记录");
		ClearInfo();
		return;
	}
	m_pRecordset->MoveLast();
	ShowInfo();
}

//查看详情
void CCxbjDlg::OnBnClickedBtnDetail()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("当前没有可显示的记录");
		return;
	}
	CDalrDlg dlg;
	dlg.m_mode = 1;	//查看模式
	GetDlgItemText(IDC_EDIT_NB,dlg.strNB);
	dlg.DoModal();
	if (dlg.m_Del)
	{
		m_pRecordset->Close();
		m_pRecordset = NULL;
	}
	ShowInfo();
}

void CCxbjDlg::OnBnClickedBtnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
