// ShgxEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "ShgxEditDlg.h"


// CShgxEditDlg �Ի���

IMPLEMENT_DYNAMIC(CShgxEditDlg, CDialog)

CShgxEditDlg::CShgxEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShgxEditDlg::IDD, pParent)
	, m_gx(_T(""))
	, m_name(_T(""))
	, m_gz(_T(""))
	, m_mode(0)
{

}

CShgxEditDlg::~CShgxEditDlg()
{
}

void CShgxEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GX, m_gx);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_GZ, m_gz);
}


BEGIN_MESSAGE_MAP(CShgxEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CShgxEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CShgxEditDlg ��Ϣ�������

void CShgxEditDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	OnOK();
}

BOOL CShgxEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(m_mode == 0)
		SetWindowText("�������ϵ");
	else
	{
		SetWindowText("�޸�����ϵ");
		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CShgxEditDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
	return;
}

void CShgxEditDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}
