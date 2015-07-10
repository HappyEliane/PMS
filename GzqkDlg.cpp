// GzqkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "GzqkDlg.h"


// CGzqkDlg �Ի���

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


// CGzqkDlg ��Ϣ�������

BOOL CGzqkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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

	// ���ԡ��鿴��ģʽ�򿪸öԻ��򣬻���Ҫ��ʾ��Ա��Ϣ����������Ϣ������Ϊ��ֻ����
	if(m_mode == 1)
	{
		ShowInfo();
		ReadOnlySet();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ��ʾҪ�鿴����Ա��Ϣ
void CGzqkDlg::ShowInfo(void)
{
	CString str1,str2;
	_RecordsetPtr pRecordset;	// ��Ϊ��Ҫ��recordָ��
	_RecordsetPtr p;			// ���ڲ�ѯ�������
	_variant_t   var;			// �����ж��Ƿ�Ϊnull
	COleDateTime date;
	_bstr_t sql;
	int index;					// ����Ϊ��Ͽ�ֵ
	sql = "select * from m_dadj where zgbm = " + m_strNB;
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		// ����
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
		// ְ��
		var = pRecordset->GetCollect("zw");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ZW,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZW,"");
		}
		// ְ��
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
		// ������
		var = pRecordset->GetCollect("gzm");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_GZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_GZ,"");
		}
		// ��Ա����
		var = pRecordset->GetCollect("ryxz");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_RYXZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_RYXZ,"");
		}
		// �볧ʱ��
		var = pRecordset->GetCollect("rcsj");
		if(var.vt != VT_NULL)
		{
			date = var.date;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_RCSJ))->SetTime(date);
		}else{
			date.m_status = COleDateTime::null;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_RCSJ))->SetTime(date);
		}
		// ��Ա״̬
		var = pRecordset->GetCollect("ryzt");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_RYZT,str1);
		}else{
			SetDlgItemText(IDC_EDIT_RYZT,"");
		}
		// �������
		var = pRecordset->GetCollect("scrq");
		if(var.vt != VT_NULL)
		{
			date = var.date;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_SCRQ))->SetTime(date);
		}else{
			date.m_status = COleDateTime::null;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_SCRQ))->SetTime(date);
		}
		// ��Ա״̬
		var = pRecordset->GetCollect("ryzt");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_RYZT,str1);
		}else{
			SetDlgItemText(IDC_EDIT_RYZT,"");
		}
		// ˵������
		var = pRecordset->GetCollect("smwt");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_SMWT,str1);
		}else{
			SetDlgItemText(IDC_EDIT_SMWT,"");
		}
		// ������
		var = pRecordset->GetCollect("gsyj");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_SCYJ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_SCYJ,"");
		}
		// ��������
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

// ������Ϣ������Ϊֻ��
void CGzqkDlg::ReadOnlySet(void)
{
	CString str;
	COleDateTime time;	//���ڶ�����ѡ��ؼ���ת��

	GetDlgItem(IDC_COMBO_BM)->ShowWindow(SW_HIDE);		//����
	GetDlgItem(IDC_EDITBM)->ShowWindow(SW_SHOW);
	GetDlgItemText(IDC_COMBO_BM, str);
	SetDlgItemText(IDC_EDITBM, str);

	((CEdit *)GetDlgItem(IDC_EDIT_ZW))->SetReadOnly();	//ְ��

	GetDlgItem(IDC_COMBO_ZC)->ShowWindow(SW_HIDE);		//ְ��
	GetDlgItem(IDC_EDITZC)->ShowWindow(SW_SHOW);
	GetDlgItemText(IDC_COMBO_ZC, str);
	SetDlgItemText(IDC_EDITZC, str);

	((CEdit *)GetDlgItem(IDC_EDIT_GZ))->SetReadOnly();	//������
	((CEdit *)GetDlgItem(IDC_EDIT_RYXZ))->SetReadOnly();//��Ա����

	GetDlgItem(IDC_DATETIMEPICKER_RCSJ)->ShowWindow(SW_HIDE);	//�볧ʱ��
	GetDlgItem(IDC_EDIT_RCSJ)->ShowWindow(SW_SHOW);
	((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_RCSJ))->GetTime(time);
	if(time.GetStatus()==COleDateTime::valid)
		GetDlgItemText(IDC_DATETIMEPICKER_RCSJ,str);
	else
		str = "";
	SetDlgItemText(IDC_EDIT_RCSJ,str);

	((CEdit *)GetDlgItem(IDC_EDIT_RYZT))->SetReadOnly();		//��Ա״̬

	GetDlgItem(IDC_DATETIMEPICKER_SCRQ)->ShowWindow(SW_HIDE);	//�������
	GetDlgItem(IDC_EDIT_SCRQ)->ShowWindow(SW_SHOW);
	((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_SCRQ))->GetTime(time);
	if(time.GetStatus()==COleDateTime::valid)
		GetDlgItemText(IDC_DATETIMEPICKER_SCRQ,str);
	else
		str = "";
	SetDlgItemText(IDC_EDIT_SCRQ,str);

	((CEdit *)GetDlgItem(IDC_EDIT_JSPX))->SetReadOnly();	//������ѵ
	((CEdit *)GetDlgItem(IDC_EDIT_SMWT))->SetReadOnly();	//˵������
	((CEdit *)GetDlgItem(IDC_EDIT_SCYJ))->SetReadOnly();	//������
	((CEdit *)GetDlgItem(IDC_EDIT_JLCF))->SetReadOnly();	//��������

}

// ȡ������Ϣ���ֻ��״̬
void CGzqkDlg::ReadOnlyCancel(void)
{
	CString str;

	GetDlgItem(IDC_COMBO_BM)->ShowWindow(SW_SHOW);			//����
	GetDlgItem(IDC_EDITBM)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDITBM, str);
	SetDlgItemText(IDC_COMBO_BM, str);

	((CEdit *)GetDlgItem(IDC_EDIT_ZW))->SetReadOnly(FALSE);	//ְ��

	GetDlgItem(IDC_COMBO_ZC)->ShowWindow(SW_SHOW);			//ְ��
	GetDlgItem(IDC_EDITZC)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDITZC, str);
	SetDlgItemText(IDC_COMBO_ZC, str);

	((CEdit *)GetDlgItem(IDC_EDIT_GZ))->SetReadOnly(FALSE);		//����
	((CEdit *)GetDlgItem(IDC_EDIT_RYXZ))->SetReadOnly(FALSE);	//��Ա����

	GetDlgItem(IDC_DATETIMEPICKER_RCSJ)->ShowWindow(SW_SHOW);	//�볧ʱ��
	GetDlgItem(IDC_EDIT_RCSJ)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_RCSJ,str);
	SetDlgItemText(IDC_DATETIMEPICKER_RCSJ,str);

	((CEdit *)GetDlgItem(IDC_EDIT_RYZT))->SetReadOnly(FALSE);	//��Ա״̬

	GetDlgItem(IDC_DATETIMEPICKER_SCRQ)->ShowWindow(SW_SHOW);	//�������
	GetDlgItem(IDC_EDIT_SCRQ)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_SCRQ,str);
	SetDlgItemText(IDC_DATETIMEPICKER_SCRQ,str);

	((CEdit *)GetDlgItem(IDC_EDIT_JSPX))->SetReadOnly(FALSE);	//������ѵ
	((CEdit *)GetDlgItem(IDC_EDIT_SMWT))->SetReadOnly(FALSE);	//˵������
	((CEdit *)GetDlgItem(IDC_EDIT_JSPX))->SetReadOnly(FALSE);	//������ѵ
	((CEdit *)GetDlgItem(IDC_EDIT_SCYJ))->SetReadOnly(FALSE);	//������
	((CEdit *)GetDlgItem(IDC_EDIT_JLCF))->SetReadOnly(FALSE);	//��������
}

void CGzqkDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CGzqkDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnCancel();
}
