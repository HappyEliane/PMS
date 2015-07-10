// EditPwDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "EditPwDlg.h"
#include "MDFive.h"

// CEditPwDlg �Ի���

IMPLEMENT_DYNAMIC(CEditPwDlg, CDialog)

CEditPwDlg::CEditPwDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPwDlg::IDD, pParent)
	, m_oldpw(_T(""))
	, m_newpw(_T(""))
	, m_newpw2(_T(""))
{

}

CEditPwDlg::~CEditPwDlg()
{
}

void CEditPwDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_oldpw);
	DDX_Text(pDX, IDC_EDIT3, m_newpw);
	DDX_Text(pDX, IDC_EDIT4, m_newpw2);
}


BEGIN_MESSAGE_MAP(CEditPwDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CEditPwDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditPwDlg ��Ϣ�������

void CEditPwDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	//�������������������Ƿ�һ��
	if (m_newpw != m_newpw2)
	{
		AfxMessageBox("��������������벻һ��!");
		return;
	}

	CString md5oldpw, md5newpw, correctPw;
	MDFive md;
	md.SetPlaint(m_oldpw);
	md5oldpw = md.GetCiph();	//������ܺ�ľ�����
	md.SetPlaint(m_newpw);
	md5newpw = md.GetCiph();	//������ܺ��������

	_RecordsetPtr pRecordset;
	_variant_t var;
	_bstr_t sql = "select userspw from user_table where usersname = '" + CurrentUser + "'";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		if (pRecordset->RecordCount < 1)
		{
			AfxMessageBox("�û�������!");
			return;
		}
		var = pRecordset->GetCollect("userspw");
		correctPw = var.bstrVal;
		if (correctPw != md5oldpw)
		{
			AfxMessageBox("�������������!");
			return;
		}
		sql = "update user_table set userspw = '" +md5newpw + "' where usersname = '" + CurrentUser + "'";
		AdoConn.ExecuteSQL(sql);
		AfxMessageBox("�����޸ĳɹ�!");
		OnOK();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}
}
