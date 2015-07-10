// GzqkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "GzqkDlg.h"


// CGzqkDlg 对话框

IMPLEMENT_DYNAMIC(CGzqkDlg, CDialog)

CGzqkDlg::CGzqkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGzqkDlg::IDD, pParent)
	, m_mode(0)
	, m_strNB(_T(""))
{

}

CGzqkDlg::~CGzqkDlg()
{
}

void CGzqkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BM, m_BoxBM);
	DDX_Control(pDX, IDC_COMBO_ZC, m_BoxZC);
}


BEGIN_MESSAGE_MAP(CGzqkDlg, CDialog)
END_MESSAGE_MAP()


// CGzqkDlg 消息处理程序

BOOL CGzqkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	_RecordsetPtr pRecordset;
	CString str1,str2;
	_bstr_t sql1,sql2;
	sql1 = "select * from bm_bm";
	sql2 = "select * from bm_zc";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql1);
		while (pRecordset->adoEOF == 0)
		{
			str1 = (char *)(_bstr_t)pRecordset->GetCollect("bmbm");
			str2 = (char *)(_bstr_t)pRecordset->GetCollect("bmm");
			str1 = str1 + " " + str2;
			m_BoxBM.AddString(str1);
			pRecordset->MoveNext();
		}
		pRecordset = AdoConn.GetRecordSet(sql2);
		while (pRecordset->adoEOF == 0)
		{
			str1 = (char *)(_bstr_t)pRecordset->GetCollect("zcbm");
			str2 = (char *)(_bstr_t)pRecordset->GetCollect("zcmc");
			str1 = str1 + " " + str2;
			m_BoxZC.AddString(str1);
			pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
	}
	m_BoxBM.SetCurSel(0);
	m_BoxZC.SetCurSel(0);

	// 若以“查看”模式打开该对话框，还需要显示人员信息，并将各信息框设置为“只读”
	if(m_mode == 1)
	{
		ShowInfo();
		ReadOnlySet();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 显示要查看的人员信息
void CGzqkDlg::ShowInfo(void)
{
	CString str1,str2;
	_RecordsetPtr pRecordset;	// 作为主要的record指针
	_RecordsetPtr p;			// 用于查询二级表格
	_variant_t   var;			// 用于判断是否为null
	COleDateTime date;
	_bstr_t sql;
	int index;					// 用于为组合框赋值
	sql = "select * from m_dadj where zgbm = " + m_strNB;
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		// 部门
		var = pRecordset->GetCollect("bmbm");
		if(var.vt != VT_NULL)
		{
			str2 = (char *)(_bstr_t)var;
			p = AdoConn.GetRecordSet((LPCTSTR)("select bmm from bm_bm where bmbm = " + str2));
			str1 = (char *)(_bstr_t)p->GetCollect("bmm");
			index = m_BoxBM.FindStringExact(-1, str2 + " " + str1);
			m_BoxBM.SetCurSel(index);
			p->Close();
		}else{
			m_BoxBM.SetCurSel(0);
		}
		// 职务
		var = pRecordset->GetCollect("zw");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ZW,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZW,"");
		}
		// 职称
		var = pRecordset->GetCollect("zcbm");
		if(var.vt != VT_NULL)
		{
			str2 = (char *)(_bstr_t)var;
			p = AdoConn.GetRecordSet((LPCTSTR)("select zcmc from bm_zc where zcbm = " + str2));
			str1 = (char *)(_bstr_t)p->GetCollect("zcmc");
			index = m_BoxZC.FindStringExact(-1, str2 + " " + str1);
			m_BoxZC.SetCurSel(index);
			p->Close();
		}else{
			m_BoxZC.SetCurSel(0);
		}
		// 工种名
		var = pRecordset->GetCollect("gzm");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_GZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_GZ,"");
		}
		// 人员性质
		var = pRecordset->GetCollect("ryxz");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_RYXZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_RYXZ,"");
		}
		// 入厂时间
		var = pRecordset->GetCollect("rcsj");
		if(var.vt != VT_NULL)
		{
			date = var.date;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_RCSJ))->SetTime(date);
		}else{
			date.m_status = COleDateTime::null;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_RCSJ))->SetTime(date);
		}
		// 人员状态
		var = pRecordset->GetCollect("ryzt");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_RYZT,str1);
		}else{
			SetDlgItemText(IDC_EDIT_RYZT,"");
		}
		// 审查日期
		var = pRecordset->GetCollect("scrq");
		if(var.vt != VT_NULL)
		{
			date = var.date;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_SCRQ))->SetTime(date);
		}else{
			date.m_status = COleDateTime::null;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_SCRQ))->SetTime(date);
		}
		// 人员状态
		var = pRecordset->GetCollect("ryzt");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_RYZT,str1);
		}else{
			SetDlgItemText(IDC_EDIT_RYZT,"");
		}
		// 说明问题
		var = pRecordset->GetCollect("smwt");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_SMWT,str1);
		}else{
			SetDlgItemText(IDC_EDIT_SMWT,"");
		}
		// 审查意见
		var = pRecordset->GetCollect("gsyj");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_SCYJ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_SCYJ,"");
		}
		// 奖励处分
		var = pRecordset->GetCollect("jlcf");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_JLCF,str1);
		}else{
			SetDlgItemText(IDC_EDIT_JLCF,"");
		}
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
}

// 将各信息框设置为只读
void CGzqkDlg::ReadOnlySet(void)
{
	CString str;
	COleDateTime time;	//用于对日期选择控件的转换

	GetDlgItem(IDC_COMBO_BM)->ShowWindow(SW_HIDE);		//部门
	GetDlgItem(IDC_EDITBM)->ShowWindow(SW_SHOW);
	GetDlgItemText(IDC_COMBO_BM, str);
	SetDlgItemText(IDC_EDITBM, str);

	((CEdit *)GetDlgItem(IDC_EDIT_ZW))->SetReadOnly();	//职务

	GetDlgItem(IDC_COMBO_ZC)->ShowWindow(SW_HIDE);		//职称
	GetDlgItem(IDC_EDITZC)->ShowWindow(SW_SHOW);
	GetDlgItemText(IDC_COMBO_ZC, str);
	SetDlgItemText(IDC_EDITZC, str);

	((CEdit *)GetDlgItem(IDC_EDIT_GZ))->SetReadOnly();	//工种名
	((CEdit *)GetDlgItem(IDC_EDIT_RYXZ))->SetReadOnly();//人员性质

	GetDlgItem(IDC_DATETIMEPICKER_RCSJ)->ShowWindow(SW_HIDE);	//入厂时间
	GetDlgItem(IDC_EDIT_RCSJ)->ShowWindow(SW_SHOW);
	((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_RCSJ))->GetTime(time);
	if(time.GetStatus()==COleDateTime::valid)
		GetDlgItemText(IDC_DATETIMEPICKER_RCSJ,str);
	else
		str = "";
	SetDlgItemText(IDC_EDIT_RCSJ,str);

	((CEdit *)GetDlgItem(IDC_EDIT_RYZT))->SetReadOnly();		//人员状态

	GetDlgItem(IDC_DATETIMEPICKER_SCRQ)->ShowWindow(SW_HIDE);	//审查日期
	GetDlgItem(IDC_EDIT_SCRQ)->ShowWindow(SW_SHOW);
	((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_SCRQ))->GetTime(time);
	if(time.GetStatus()==COleDateTime::valid)
		GetDlgItemText(IDC_DATETIMEPICKER_SCRQ,str);
	else
		str = "";
	SetDlgItemText(IDC_EDIT_SCRQ,str);

	((CEdit *)GetDlgItem(IDC_EDIT_JSPX))->SetReadOnly();	//技术培训
	((CEdit *)GetDlgItem(IDC_EDIT_SMWT))->SetReadOnly();	//说明问题
	((CEdit *)GetDlgItem(IDC_EDIT_SCYJ))->SetReadOnly();	//审查意见
	((CEdit *)GetDlgItem(IDC_EDIT_JLCF))->SetReadOnly();	//奖励处分

}

// 取消各信息框的只读状态
void CGzqkDlg::ReadOnlyCancel(void)
{
	CString str;

	GetDlgItem(IDC_COMBO_BM)->ShowWindow(SW_SHOW);			//部门
	GetDlgItem(IDC_EDITBM)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDITBM, str);
	SetDlgItemText(IDC_COMBO_BM, str);

	((CEdit *)GetDlgItem(IDC_EDIT_ZW))->SetReadOnly(FALSE);	//职务

	GetDlgItem(IDC_COMBO_ZC)->ShowWindow(SW_SHOW);			//职称
	GetDlgItem(IDC_EDITZC)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDITZC, str);
	SetDlgItemText(IDC_COMBO_ZC, str);

	((CEdit *)GetDlgItem(IDC_EDIT_GZ))->SetReadOnly(FALSE);		//工种
	((CEdit *)GetDlgItem(IDC_EDIT_RYXZ))->SetReadOnly(FALSE);	//人员性质

	GetDlgItem(IDC_DATETIMEPICKER_RCSJ)->ShowWindow(SW_SHOW);	//入厂时间
	GetDlgItem(IDC_EDIT_RCSJ)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_RCSJ,str);
	SetDlgItemText(IDC_DATETIMEPICKER_RCSJ,str);

	((CEdit *)GetDlgItem(IDC_EDIT_RYZT))->SetReadOnly(FALSE);	//人员状态

	GetDlgItem(IDC_DATETIMEPICKER_SCRQ)->ShowWindow(SW_SHOW);	//审查日期
	GetDlgItem(IDC_EDIT_SCRQ)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_SCRQ,str);
	SetDlgItemText(IDC_DATETIMEPICKER_SCRQ,str);

	((CEdit *)GetDlgItem(IDC_EDIT_JSPX))->SetReadOnly(FALSE);	//技术培训
	((CEdit *)GetDlgItem(IDC_EDIT_SMWT))->SetReadOnly(FALSE);	//说明问题
	((CEdit *)GetDlgItem(IDC_EDIT_JSPX))->SetReadOnly(FALSE);	//技术培训
	((CEdit *)GetDlgItem(IDC_EDIT_SCYJ))->SetReadOnly(FALSE);	//审查意见
	((CEdit *)GetDlgItem(IDC_EDIT_JLCF))->SetReadOnly(FALSE);	//奖励处分
}

void CGzqkDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CGzqkDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}
