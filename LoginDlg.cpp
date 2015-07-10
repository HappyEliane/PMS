// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "LoginDlg.h"
#include "MDFive.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_userName(_T(""))
	, m_passWord(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UN, m_userName);
	DDX_Text(pDX, IDC_EDIT_PW, m_passWord);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������

void CLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	CString md5pw, correctPw;
	MDFive md;
	md.SetPlaint(m_passWord);
	md5pw = md.GetCiph();	//������ܺ������

	_RecordsetPtr pRecordset;
	_variant_t var;
	//������ݿ��е�ɢ������Ĳ�ѯ���
	_bstr_t sql = "select userspw from user_table where usersname = '" + m_userName + "'";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);	//ִ�в�ѯ
		if (pRecordset->RecordCount < 1)
		{
			AfxMessageBox("�û�������!");
			return;
		}
		var = pRecordset->GetCollect("userspw");//�������
		if (var.vt = VT_BSTR)
		{
			correctPw = var.bstrVal;
		}
		if (correctPw != md5pw)					//����Ƚ�
		{
			AfxMessageBox("�������!");
			return;
		}
		CurrentUser = m_userName;
		OnOK();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//m_userName = "admin";
	//m_passWord = "123";
	//UpdateData(FALSE);
	GetDlgItem(IDC_EDIT_UN)->GetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
