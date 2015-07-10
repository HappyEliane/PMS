// CxbjDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "CxbjDlg.h"
#include "DalrDlg.h"

// CCxbjDlg �Ի���

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


// CCxbjDlg ��Ϣ�������

BOOL CCxbjDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//Ĭ��Ϊ��������ѯ
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CCxbjDlg::OnBnClickedBtnSearJq()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		strResult = "��ǰ��ѯ��ʽ����ȷ��ѯ������Ϊ " + str + " ��Ա����";
		break;
	case IDC_RADIO2:
		GetDlgItemText(IDC_SEARCH_NB,str);
		str.Trim();
		sql = "select * from m_dadj where zgbm = " + str;
		strResult = "��ǰ��ѯ��ʽ����ȷ��ѯ�����Ϊ " + str + " ��Ա����";
		break;
	}
	m_pRecordset = AdoConn.GetRecordSet(sql);
	strCount.Format("%d",m_pRecordset->RecordCount);
	strResult = strResult + strCount + "��";
	SetDlgItemText(IDC_STATE,strResult);
	ShowInfo();
}

void CCxbjDlg::OnBnClickedBtnSearMh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str,strResult,strCount;
	_bstr_t sql;
	switch (GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2))
	{
	case IDC_RADIO1:
		GetDlgItemText(IDC_SEARCH_NAME,str);
		str.Trim();
		strResult = "��ǰ��ѯ��ʽ��ģ����ѯ�������а��� '" + str + "' ��Ա����";
		str = "'%" + str + "%'";
		sql = "select * from m_dadj where xm like " + str;
		break;
	case IDC_RADIO2:
		MessageBox("ģ����ѯֻ֧�ְ���������");
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
	strResult = strResult + strCount + "��";
	SetDlgItemText(IDC_STATE,strResult);
	ShowInfo();
}

// ��ʾ��ǰ��¼�е�����
void CCxbjDlg::ShowInfo(void)
{
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("δ�ҵ���Ӧ�ļ�¼");
		ClearInfo();
		return;
	}
	if (m_pRecordset->BOF)
	{
		MessageBox("�ѵ����һ����¼");
		return;
	}
	if (m_pRecordset->adoEOF)
	{
		MessageBox("�ѵ������һ����¼");
		return;
	}

	CString str1,str2,nb;
	_RecordsetPtr p;		//���ڲ�ѯ��������ְ����
	_variant_t   var;		//�����ж��Ƿ�Ϊnull
	try
	{
		//ְ������
		nb = (char *)(_bstr_t)m_pRecordset->GetCollect("zgbm");
		SetDlgItemText(IDC_EDIT_NB,nb);
		//����
		str1 = (char *)(_bstr_t)m_pRecordset->GetCollect("xm");
		SetDlgItemText(IDC_EDIT_NAME,str1);
		//�Ա�
		var = m_pRecordset->GetCollect("xb");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_SEX,str1);
		}else{
			SetDlgItemText(IDC_EDIT_SEX,"");
		}
		//����
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
		//ְ��
		var = m_pRecordset->GetCollect("zw");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ZW,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZW,"");
		}
		//ְ��
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
		//����
		var = m_pRecordset->GetCollect("gzm");
		if (var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_GZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_GZ,"");
		}
		//��Ա״̬
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

// ��ո�����Ϣ���������
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

// ��ʾ��һ����¼
void CCxbjDlg::OnBnClickedBtnFirst()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("��ǰû�п���ʾ�ļ�¼");
		ClearInfo();
		return;
	}
	m_pRecordset->MoveFirst();
	ShowInfo();
}

// ��ʾ��һ����¼
void CCxbjDlg::OnBnClickedBtnPre()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("��ǰû�п���ʾ�ļ�¼");
		ClearInfo();
		return;
	}
	if (m_pRecordset->BOF)
	{
		MessageBox("�ѵ����һ����¼");
		return;
	}
	m_pRecordset->MovePrevious();
	ShowInfo();
}

// ��ʾ��һ����¼
void CCxbjDlg::OnBnClickedBtnNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("��ǰû�п���ʾ�ļ�¼");
		ClearInfo();
		return;
	}
	if (m_pRecordset->adoEOF)
	{
		MessageBox("�ѵ������һ����¼");
		return;
	}
	m_pRecordset->MoveNext();
	ShowInfo();
}

//��ʾ���һ����¼
void CCxbjDlg::OnBnClickedBtnLast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("��ǰû�п���ʾ�ļ�¼");
		ClearInfo();
		return;
	}
	m_pRecordset->MoveLast();
	ShowInfo();
}

//�鿴����
void CCxbjDlg::OnBnClickedBtnDetail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_pRecordset == NULL|| m_pRecordset->RecordCount<1)
	{
		MessageBox("��ǰû�п���ʾ�ļ�¼");
		return;
	}
	CDalrDlg dlg;
	dlg.m_mode = 1;	//�鿴ģʽ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
