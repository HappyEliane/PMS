// AddUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "AddUserDlg.h"
#include "MDFive.h"


// CAddUserDlg �Ի���

IMPLEMENT_DYNAMIC(CAddUserDlg, CDialog)

CAddUserDlg::CAddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddUserDlg::IDD, pParent)
	, m_un(_T(""))
	, m_pw(_T(""))
	, m_pw2(_T(""))
{

}

CAddUserDlg::~CAddUserDlg()
{
}

void CAddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UN, m_un);
	DDX_Text(pDX, IDC_EDIT_PW, m_pw);
	DDX_Text(pDX, IDC_EDIT_PW2, m_pw2);
}


BEGIN_MESSAGE_MAP(CAddUserDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddUserDlg ��Ϣ�������

void CAddUserDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_un.Trim();
	if (m_un.GetLength() == 0)
	{
		AfxMessageBox("�������û���");
		return;
	}
	if (m_pw.GetLength() == 0)
	{
		AfxMessageBox("����������");
		return;
	}
	if (m_pw != m_pw2)
	{
		AfxMessageBox("������������벻һ��");
		return;
	}

	CString md5pw;
	MDFive md;
	md.SetPlaint(m_pw);
	md5pw = md.GetCiph();	//������ܺ�ľ�����


	_RecordsetPtr pRecordset;
	_variant_t var;
	_bstr_t sql = "select userspw from user_table where usersname = '" + m_un + "'";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		if (pRecordset->RecordCount >0)
		{
			AfxMessageBox("�û����Ѵ���!");
			return;
		}
		sql = "insert into user_table values('" +m_un + "', '" + md5pw + "')";
		AdoConn.ExecuteSQL(sql);
		AfxMessageBox("�û��ɹ����!");
		OnOK();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}
}
