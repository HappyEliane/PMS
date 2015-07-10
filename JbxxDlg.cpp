// JbxxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "JbxxDlg.h"


// CJbxxDlg �Ի���

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


// CJbxxDlg ��Ϣ�������

void CJbxxDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CJbxxDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

BOOL CJbxxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
			m_BoxWH.AddString(str1);//���ַ������뵽ָ����ָ��CListBox�ؼ���ȥ
			pRecordset->MoveNext();
		}
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
	}
	m_BoxWH.SetCurSel(0);
	m_BoxXB.SetCurSel(0);
	
	// ���ԡ��鿴��ģʽ�򿪸öԻ��򣬻���Ҫ��ʾ��Ա��Ϣ����������Ϣ������Ϊ��ֻ����
	if(m_mode == 1)
	{
		ShowInfo();
		ReadOnlySet();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CJbxxDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CJbxxDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnCancel();
}

void CJbxxDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
}

// ��ʾҪ�鿴����Ա��Ϣ
void CJbxxDlg::ShowInfo(void)
{
	CString str1,str2;
	_RecordsetPtr pRecordset;	//��Ϊ��Ҫ��recordָ��
	_RecordsetPtr p;			//���ڲ�ѯ�Ļ��̶�
	_variant_t   var;			//�����ж��Ƿ�Ϊnull
	COleDateTime date;
	_bstr_t sql;
	int index;					//����Ϊ��Ͽ�ֵ
	sql = "select * from m_dadj where zgbm = " + m_strNB;
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		// ְ������;
		SetDlgItemText(IDC_EDIT_ZGBM,m_strNB);
		// ����
		str1 = (char *)(_bstr_t)pRecordset->GetCollect("xm");
		SetDlgItemText(IDC_EDIT_NAME,str1);
		// �Ա�
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
		// ����
		var = pRecordset->GetCollect("mz");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_MZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_MZ,"");
		}
		// ��������
		var = pRecordset->GetCollect("csny");
		if(var.vt != VT_NULL)
		{
			date = var.date;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_BIRTH))->SetTime(date);
		}else{
			date.m_status = COleDateTime::null;
			((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_BIRTH))->SetTime(date);
			//SetDlgItemText(IDC_DATETIMEPICKER_BIRTH,"");  //����д������
		}
		// ����״��
		var = pRecordset->GetCollect("hyzk");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_HY,str1);
		}else{
			SetDlgItemText(IDC_EDIT_HY,"");
		}
		// ����״��
		var = pRecordset->GetCollect("jkzk");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_JK,str1);
		}else{
			SetDlgItemText(IDC_EDIT_JK,"");
		}
		// �Ļ��̶�
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
		// רҵ�س�
		var = pRecordset->GetCollect("zytc");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ZY,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZY,"");
		}
		// ��ҵѧУ
		var = pRecordset->GetCollect("byxx");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_XX,str1);
		}else{
			SetDlgItemText(IDC_EDIT_XX,"");
		}
		// ������ò
		var = pRecordset->GetCollect("zzmm");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ZZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ZZ,"");
		}
		// ���֤��
		var = pRecordset->GetCollect("sfzh");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_ID,str1);
		}else{
			SetDlgItemText(IDC_EDIT_ID,"");
		}
		// ��������
		var = pRecordset->GetCollect("hkxz");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_HKXZ,str1);
		}else{
			SetDlgItemText(IDC_EDIT_HKXZ,"");
		}
		// �������ڵ�
		var = pRecordset->GetCollect("hkszd");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_HKSZD,str1);
		}else{
			SetDlgItemText(IDC_EDIT_HKSZD,"");
		}
		// ����
		var = pRecordset->GetCollect("jg");
		if(var.vt != VT_NULL)
		{
			str1 = (char *)(_bstr_t)var;
			SetDlgItemText(IDC_EDIT_JG,str1);
		}else{
			SetDlgItemText(IDC_EDIT_JG,"");
		}
		// ��סַ
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

// ������Ϣ������Ϊֻ��
void CJbxxDlg::ReadOnlySet(void)
{
	CString str;
	COleDateTime time;
	((CEdit *)GetDlgItem(IDC_EDIT_NAME))->SetReadOnly();//����
	((CEdit *)GetDlgItem(IDC_EDIT_ZGBM))->SetReadOnly();//����
	GetDlgItem(IDC_COMBO_SEX)->ShowWindow(SW_HIDE);		//�Ա�
	GetDlgItem(IDC_EDIT_SEX)->ShowWindow(SW_SHOW);
	GetDlgItemText(IDC_COMBO_SEX,str);
	SetDlgItemText(IDC_EDIT_SEX,str);
	((CEdit *)GetDlgItem(IDC_EDIT_MZ))->SetReadOnly();	//����
	GetDlgItem(IDC_DATETIMEPICKER_BIRTH)->ShowWindow(SW_HIDE);	//��������
	GetDlgItem(IDC_EDIT_BIRTH)->ShowWindow(SW_SHOW);
	((CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_BIRTH))->GetTime(time);
	if(time.GetStatus()==COleDateTime::valid)
		GetDlgItemText(IDC_DATETIMEPICKER_BIRTH,str);
	else
		str = "";
	SetDlgItemText(IDC_EDIT_BIRTH,str);
	((CEdit *)GetDlgItem(IDC_EDIT_HY))->SetReadOnly();	//����״��
	((CEdit *)GetDlgItem(IDC_EDIT_JK))->SetReadOnly();	//����״��
	GetDlgItem(IDC_COMBO_WH)->ShowWindow(SW_HIDE);		//�Ļ��̶�
	GetDlgItem(IDC_EDIT_WH)->ShowWindow(SW_SHOW);
	GetDlgItemText(IDC_COMBO_WH, str);
	SetDlgItemText(IDC_EDIT_WH, str);
	((CEdit *)GetDlgItem(IDC_EDIT_ZY))->SetReadOnly();	//רҵ�س�
	((CEdit *)GetDlgItem(IDC_EDIT_XX))->SetReadOnly();	//��ҵѧУ
	((CEdit *)GetDlgItem(IDC_EDIT_ZZ))->SetReadOnly();	//������ò
	((CEdit *)GetDlgItem(IDC_EDIT_ID))->SetReadOnly();	//���֤��
	((CEdit *)GetDlgItem(IDC_EDIT_HKXZ))->SetReadOnly();//��������
	((CEdit *)GetDlgItem(IDC_EDIT_HKSZD))->SetReadOnly();//�������ڵ�
	((CEdit *)GetDlgItem(IDC_EDIT_JG))->SetReadOnly();	//����
	((CEdit *)GetDlgItem(IDC_EDIT_XZZ))->SetReadOnly();	//��סַ
}

// ȡ������Ϣ���ֻ��״̬
void CJbxxDlg::ReadOnlyCancel(void)
{
	CString str;
	((CEdit *)GetDlgItem(IDC_EDIT_NAME))->SetReadOnly(FALSE);//����
	//((CEdit *)GetDlgItem(IDC_EDIT_ZGBM))->SetReadOnly(FALSE);//���벻�����޸�
	GetDlgItem(IDC_COMBO_SEX)->ShowWindow(SW_SHOW);		//�Ա�
	GetDlgItem(IDC_EDIT_SEX)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_SEX,str);
	SetDlgItemText(IDC_COMBO_SEX,str);
	((CEdit *)GetDlgItem(IDC_EDIT_MZ))->SetReadOnly(FALSE);	//����
	GetDlgItem(IDC_DATETIMEPICKER_BIRTH)->ShowWindow(SW_SHOW);	//��������
	GetDlgItem(IDC_EDIT_BIRTH)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_BIRTH,str);
	SetDlgItemText(IDC_DATETIMEPICKER_BIRTH,str);
	((CEdit *)GetDlgItem(IDC_EDIT_HY))->SetReadOnly(FALSE);	//����״��
	((CEdit *)GetDlgItem(IDC_EDIT_JK))->SetReadOnly(FALSE);	//����״��
	GetDlgItem(IDC_COMBO_WH)->ShowWindow(SW_SHOW);		//�Ļ��̶�
	GetDlgItem(IDC_EDIT_WH)->ShowWindow(SW_HIDE);
	GetDlgItemText(IDC_EDIT_WH, str);
	SetDlgItemText(IDC_COMBO_WH, str);
	((CEdit *)GetDlgItem(IDC_EDIT_ZY))->SetReadOnly(FALSE);	//רҵ�س�
	((CEdit *)GetDlgItem(IDC_EDIT_XX))->SetReadOnly(FALSE);	//��ҵѧУ
	((CEdit *)GetDlgItem(IDC_EDIT_ZZ))->SetReadOnly(FALSE);	//������ò
	((CEdit *)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(FALSE);	//���֤��
	((CEdit *)GetDlgItem(IDC_EDIT_HKXZ))->SetReadOnly(FALSE);//��������
	((CEdit *)GetDlgItem(IDC_EDIT_HKSZD))->SetReadOnly(FALSE);//�������ڵ�
	((CEdit *)GetDlgItem(IDC_EDIT_JG))->SetReadOnly(FALSE);	//����
	((CEdit *)GetDlgItem(IDC_EDIT_XZZ))->SetReadOnly(FALSE);//��סַ
}

void CJbxxDlg::OnCbnSelchangeComboSex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
