// BzDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "BzDlg.h"


// CBzDlg �Ի���

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ���ԡ��鿴��ģʽ�򿪸öԻ��򣬻���Ҫ��ʾ��Ա��Ϣ��������Ϣ������Ϊ��ֻ����
	if(m_mode == 1)
	{
		ShowInfo();
		ReadOnlySet();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


// ��ʾҪ�鿴����Ա��Ϣ
void CBzDlg::ShowInfo(void)
{
	CString str1;
	_RecordsetPtr m_pRecordset;
	_variant_t   var;			// �����ж��Ƿ�Ϊnull
	_bstr_t sql;
	sql = "select bz from m_dadj where zgbm = " + m_strNB;
	try
	{
		//�򿪼�¼��
		m_pRecordset = AdoConn.GetRecordSet(sql);
		//�����Ϣ
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

// ����Ϣ������Ϊֻ��
void CBzDlg::ReadOnlySet(void)
{
	((CEdit *)GetDlgItem(IDC_EDIT_BZ))->SetReadOnly();		//��ע
}

// ȡ����Ϣ���ֻ��״̬
void CBzDlg::ReadOnlyCancel(void)
{
	((CEdit *)GetDlgItem(IDC_EDIT_BZ))->SetReadOnly(FALSE);	//��ע
}


void CBzDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CBzDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnCancel();
}
