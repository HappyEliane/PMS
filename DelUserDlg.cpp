// DelUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "DelUserDlg.h"


// CDelUserDlg �Ի���

IMPLEMENT_DYNAMIC(CDelUserDlg, CDialog)

CDelUserDlg::CDelUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelUserDlg::IDD, pParent)
	, m_un(_T(""))
{

}

CDelUserDlg::~CDelUserDlg()
{
}

void CDelUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_un);
}


BEGIN_MESSAGE_MAP(CDelUserDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CDelUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDelUserDlg ��Ϣ�������

void CDelUserDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_un == CurrentUser)
	{
		AfxMessageBox("������ɾ����ǰ�˻���");
		return;
	}

	_RecordsetPtr pRecordset;
	_variant_t var;
	_bstr_t sql = "select userspw from user_table where usersname = '" + m_un + "'";
	try
	{
		pRecordset = AdoConn.GetRecordSet(sql);
		if (pRecordset->RecordCount <1)
		{
			AfxMessageBox("�û�������!");
			return;
		}
		sql = "delete from user_table where usersname = '" +m_un + "'";
		AdoConn.ExecuteSQL(sql);
		AfxMessageBox("�û�"+ m_un + "ɾ���ɹ�!");
		OnOK();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}
}
