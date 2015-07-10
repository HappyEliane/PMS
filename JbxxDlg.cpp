// JbxxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "JbxxDlg.h"


// CJbxxDlg 对话框

IMPLEMENT_DYNAMIC(CJbxxDlg, CDialog)

CJbxxDlg::CJbxxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJbxxDlg::IDD, pParent)
	, m_mode(0)
	, m_strNB(_T(""))
{

}

CJbxxDlg::~CJbxxDlg()
{
}

void CJbxxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WH, m_BoxWH);
	DDX_Control(pDX, IDC_COMBO_SEX, m_BoxXB);
}


BEGIN_MESSAGE_MAP(CJbxxDlg, CDialog)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_BIRTH, &CJbxxDlg::OnDtnDatetimechangeDatetimepicker1)
//	ON_EN_CHANGE(IDC_EDIT4, &CJbxxDlg::OnEnChangeEdit4)
ON_BN_CLICKED(IDOK, &CJbxxDlg::OnBnClickedOk)
ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CJbxxDlg::OnCbnSelchangeComboSex)
END_MESSAGE_MAP()


// CJbxxDlg 消息处理程序

void CJbxxDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CJbxxDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

BOOL CJbxxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
// 	CDateTimeCtrl* pCtrl = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_BIRTH);
// 	pCtrl-> SetFormat("yyyy-MM ");
	_RecordsetPtr pRecordset;
	CString str1,str2;
	_bstr_t sql;
	sql = "select * from bm_wh";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		while (pRecordset->adoEOF == 0)
		{
			str1 = (LPCTSTR )(_bstr_t)pRecordset->GetCollect("whbm");
			str2 = (LPCTSTR )(_bstr_t)pRecordset->GetCollect("whcd");
			str1 = str1 + " " + str2;
			m_BoxWH.AddString(str1);//将字符串加入到指针所指的CListBox控件中去
			pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
	}
	m_BoxWH.SetCurSel(0);
	m_BoxXB.SetCurSel(0);
	
	// 若以“查看”模式打开该对话框，还需要显示人员信息，并将各信息框设置为“只读”
	if(m_mode == 1)
	{
		ShowInfo();
		ReadOnlySet();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CJbxxDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CJbxxDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CJbxxDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}

// 显示要查看的人员信息
void CJbxxDlg::ShowInfo(void)
{
	CString str1,str2;
	_RecordsetPtr pRecordset;	//作为主要的record指针
	_RecordsetPtr p;			//用于查询文化程度
	_variant_t   var;			//用于判断是否为null
	COleDateTime date;
	_bstr_t sql;
	int index;					//用于为组合框赋值
	sql = "select * from m_dadj where zgbm = " + m_strNB;
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		// 职工编码;
		SetDlgItemText(IDC_EDIT_ZGBM,m_strNB);
		// 姓名
		str1 = (char *)(_bstr_t)pRecordset->GetCollect("xm");
		SetDlgItemText(IDC_EDIT_NAME,str1);
		// 性别
		var = pRecordset->GetCollect("xb");
		if (var.vt != VT_NULL)
		{
		str1 = (char *)(_bstr_t)var;
		index = m_BoxXB.FindString(-1, str1);
		if (index>=0)
		{
			m_BoxXB.SetCurSel(index);
		}else{
			m_BoxXB.SetCurSel(0);
		}
		}
		// 民族
		var = pRecordset->GetCollect("mz");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_MZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_MZ,"");
		}
		// 出生日期
		var = pRecordset->GetCollect("csny");
		if(var.vt != VT_NULL)
		{
			date = var.date;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_BIRTH))->SetTime(date);
		}else{
			date.m_status = COleDateTime::null;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_BIRTH))->SetTime(date);
			//SetDlgItemText(IDC_DATETIMEPICKER_BIRTH,"");  //这种写法错误
		}
		// 婚姻状况
		var = pRecordset->GetCollect("hyzk");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_HY,str1);
		}else{
			SetDlgItemText(IDC_EDIT_HY,"");
		}
		// 健康状况
		var = pRecordset->GetCollect("jkzk");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_JK,str1);
		}else{
			SetDlgItemText(IDC_EDIT_JK,"");
		}
		// 文化程度
		var = pRecordset->GetCollect("whbm");
		if(var.vt != VT_NULL)
		{
			str2 = (char *)(_bstr_t)var;
			p = AdoConn.GetRecordSet((LPCTSTR)("select whcd from bm_wh where whbm = " + str2));
			str1 = (char *)(_bstr_t)p->GetCollect("whcd");
			index = m_BoxWH.FindStringExact(-1, str2 + " " + str1);
			m_BoxWH.SetCurSel(index);
			p->Close();
		}else{
			SetDlgItemText(IDC_EDIT_WH,"");
		}
		// 专业特长
		var = pRecordset->GetCollect("zytc");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ZY,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZY,"");
		}
		// 毕业学校
		var = pRecordset->GetCollect("byxx");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_XX,str1);
		}else{
			SetDlgItemText(IDC_EDIT_XX,"");
		}
		// 政治面貌
		var = pRecordset->GetCollect("zzmm");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ZZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZZ,"");
		}
		// 身份证号
		var = pRecordset->GetCollect("sfzh");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ID,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ID,"");
		}
		// 户口性质
		var = pRecordset->GetCollect("hkxz");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_HKXZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_HKXZ,"");
		}
		// 户口所在地
		var = pRecordset->GetCollect("hkszd");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_HKSZD,str1);
		}else{
			SetDlgItemText(IDC_EDIT_HKSZD,"");
		}
		// 籍贯
		var = pRecordset->GetCollect("jg");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_JG,str1);
		}else{
			SetDlgItemText(IDC_EDIT_JG,"");
		}
		// 现住址
		var = pRecordset->GetCollect("xzz");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_XZZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_XZZ,"");
		}
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
}

// 将各信息框设置为只读
void CJbxxDlg::ReadOnlySet(void)
{
	CString str;
	COleDateTime time;
	((CEdit *)GetDlgItem(IDC_EDIT_NAME))->SetReadOnly();//姓名
	((CEdit *)GetDlgItem(IDC_EDIT_ZGBM))->SetReadOnly();//编码
	GetDlgItem(IDC_COMBO_SEX)->ShowWindow(SW_HIDE);		//性别
	GetDlgItem(IDC_EDIT_SEX)->ShowWindow(SW_SHOW);
	GetDlgItemText(IDC_COMBO_SEX,str);
	SetDlgItemText(IDC_EDIT_SEX,str);
	((CEdit *)GetDlgItem(IDC_EDIT_MZ))->SetReadOnly();	//民族
	GetDlgItem(IDC_DATETIMEPICKER_BIRTH)->ShowWindow(SW_HIDE);	//出生日期
	GetDlgItem(IDC_EDIT_BIRTH)->ShowWindow(SW_SHOW);
	((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_BIRTH))->GetTime(time);
	if(time.GetStatus()==COleDateTime::valid)
		GetDlgItemText(IDC_DATETIMEPICKER_BIRTH,str);
	else
		str = "";
	SetDlgItemText(IDC_EDIT_BIRTH,str);
	((CEdit *)GetDlgItem(IDC_EDIT_HY))->SetReadOnly();	//婚姻状况
	((CEdit *)GetDlgItem(IDC_EDIT_JK))->SetReadOnly();	//健康状况
	GetDlgItem(IDC_COMBO_WH)->ShowWindow(SW_HIDE);		//文化程度
	GetDlgItem(IDC_EDIT_WH)->ShowWindow(SW_SHOW);
	GetDlgItemText(IDC_COMBO_WH, str);
	SetDlgItemText(IDC_EDIT_WH, str);
	((CEdit *)GetDlgItem(IDC_EDIT_ZY))->SetReadOnly();	//专业特长
	((CEdit *)GetDlgItem(IDC_EDIT_XX))->SetReadOnly();	//毕业学校
	((CEdit *)GetDlgItem(IDC_EDIT_ZZ))->SetReadOnly();	//政治面貌
	((CEdit *)GetDlgItem(IDC_EDIT_ID))->SetReadOnly();	//身份证号
	((CEdit *)GetDlgItem(IDC_EDIT_HKXZ))->SetReadOnly();//户口性质
	((CEdit *)GetDlgItem(IDC_EDIT_HKSZD))->SetReadOnly();//户口所在地
	((CEdit *)GetDlgItem(IDC_EDIT_JG))->SetReadOnly();	//籍贯
	((CEdit *)GetDlgItem(IDC_EDIT_XZZ))->SetReadOnly();	//现住址
}

// 取消各信息框的只读状态
void CJbxxDlg::ReadOnlyCancel(void)
{
	CString str;
	((CEdit *)GetDlgItem(IDC_EDIT_NAME))->SetReadOnly(FALSE);//姓名
	//((CEdit *)GetDlgItem(IDC_EDIT_ZGBM))->SetReadOnly(FALSE);//编码不允许修改
	GetDlgItem(IDC_COMBO_SEX)->ShowWindow(SW_SHOW);		//性别
	GetDlgItem(IDC_EDIT_SEX)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_SEX,str);
	SetDlgItemText(IDC_COMBO_SEX,str);
	((CEdit *)GetDlgItem(IDC_EDIT_MZ))->SetReadOnly(FALSE);	//民族
	GetDlgItem(IDC_DATETIMEPICKER_BIRTH)->ShowWindow(SW_SHOW);	//出生日期
	GetDlgItem(IDC_EDIT_BIRTH)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_BIRTH,str);
	SetDlgItemText(IDC_DATETIMEPICKER_BIRTH,str);
	((CEdit *)GetDlgItem(IDC_EDIT_HY))->SetReadOnly(FALSE);	//婚姻状况
	((CEdit *)GetDlgItem(IDC_EDIT_JK))->SetReadOnly(FALSE);	//健康状况
	GetDlgItem(IDC_COMBO_WH)->ShowWindow(SW_SHOW);		//文化程度
	GetDlgItem(IDC_EDIT_WH)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_WH, str);
	SetDlgItemText(IDC_COMBO_WH, str);
	((CEdit *)GetDlgItem(IDC_EDIT_ZY))->SetReadOnly(FALSE);	//专业特长
	((CEdit *)GetDlgItem(IDC_EDIT_XX))->SetReadOnly(FALSE);	//毕业学校
	((CEdit *)GetDlgItem(IDC_EDIT_ZZ))->SetReadOnly(FALSE);	//政治面貌
	((CEdit *)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(FALSE);	//身份证号
	((CEdit *)GetDlgItem(IDC_EDIT_HKXZ))->SetReadOnly(FALSE);//户口性质
	((CEdit *)GetDlgItem(IDC_EDIT_HKSZD))->SetReadOnly(FALSE);//户口所在地
	((CEdit *)GetDlgItem(IDC_EDIT_JG))->SetReadOnly(FALSE);	//籍贯
	((CEdit *)GetDlgItem(IDC_EDIT_XZZ))->SetReadOnly(FALSE);//现住址
}

void CJbxxDlg::OnCbnSelchangeComboSex()
{
	// TODO: 在此添加控件通知处理程序代码
}
