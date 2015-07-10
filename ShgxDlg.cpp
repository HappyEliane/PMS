// ShgxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "ShgxDlg.h"
#include "ShgxEditDlg.h"


// CShgxDlg �Ի���

IMPLEMENT_DYNAMIC(CShgxDlg, CDialog)

CShgxDlg::CShgxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShgxDlg::IDD, pParent)
	, m_mode(0)
	, m_strNB(_T(""))
{

}

CShgxDlg::~CShgxDlg()
{
}

void CShgxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CShgxDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CShgxDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BTN_ADD, &CShgxDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CShgxDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DEL, &CShgxDlg::OnBnClickedBtnDel)
END_MESSAGE_MAP()


// CShgxDlg ��Ϣ�������

void CShgxDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

BOOL CShgxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.SetExtendedStyle(LVS_EX_FLATSB 
		| LVS_EX_FULLROWSELECT 
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,"��ϵ",LVCFMT_CENTER,100,0);
	m_list.InsertColumn(1,"����",LVCFMT_CENTER,100,0);
	m_list.InsertColumn(2,"����",LVCFMT_CENTER,250,0);

	// ���ԡ��鿴��ģʽ�򿪸öԻ��򣬻���Ҫ��ʾ��Ա��Ϣ��������Ϣ������Ϊ��ֻ����
	if(m_mode == 1)
	{
		ShowInfo();
		ReadOnlySet();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CShgxDlg::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CShgxEditDlg dlg;
	int nCount;
	dlg.m_mode = 0;
	if(IDOK == dlg.DoModal())
	{
		nCount = m_list.GetItemCount();
		m_list.InsertItem(nCount, 0);
		m_list.SetItemText(nCount,0,dlg.m_gx);
		m_list.SetItemText(nCount,1,dlg.m_name);
		m_list.SetItemText(nCount,2,dlg.m_gz);
	}
}

void CShgxDlg::OnBnClickedBtnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CShgxEditDlg dlg;
	CString str;
	int index = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (index == -1)
	{
		MessageBox("��ѡ��Ҫ�޸ĵ���");
		return;
	}
	dlg.m_gx = m_list.GetItemText(index, 0);
	dlg.m_name = m_list.GetItemText(index, 1);
	dlg.m_gz = m_list.GetItemText(index, 2);
	dlg.m_mode = 1;
	if(IDOK == dlg.DoModal())
	{
		m_list.SetItemText(index,0,dlg.m_gx);
		m_list.SetItemText(index,1,dlg.m_name);
		m_list.SetItemText(index,2,dlg.m_gz);
	}
}

void CShgxDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnCancel();
}

void CShgxDlg::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CShgxEditDlg dlg;
	CString str;
	int index = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (index == -1)
	{
		MessageBox("��ѡ��Ҫɾ������");
		return;
	}
	if(IDOK == MessageBox("ȷ��ɾ����?"))
	{
		m_list.DeleteItem(index);
	}
}

// ��ʾҪ�鿴����Ա��Ϣ
void CShgxDlg::ShowInfo(void)
{
	// ������еļ�¼
	m_list.DeleteAllItems();

	_RecordsetPtr m_pRecordset;
	_bstr_t sql;
	sql = "select * from cygx where zgbm = " + m_strNB;
	try
	{
		//�򿪼�¼��
	m_pRecordset = AdoConn.GetRecordSet(sql);
	//������¼��
	while(AdoConn.m_pRecordset->adoEOF==0)
	{
		m_list.InsertItem(0, "");
		//����¼���ֶ��еļ�¼��ӵ��б���ͼ�ؼ���
		m_list.SetItemText(0,0,(char *)(_bstr_t)m_pRecordset->GetCollect("brgx"));
		m_list.SetItemText(0,1,(char *)(_bstr_t)m_pRecordset->GetCollect("xm"));
		m_list.SetItemText(0,2,(char *)(_bstr_t)m_pRecordset->GetCollect("hzgz"));
		//ָ����һ����¼
		m_pRecordset->MoveNext();
	}
	m_pRecordset->Close();
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
}

// ����Ϣ������Ϊֻ�������������༭��ť��
void CShgxDlg::ReadOnlySet(void)
{
	GetDlgItem(IDC_BTN_ADD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_EDIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_HIDE);
}

// ȡ����Ϣ���ֻ��״̬����ʾ�����༭��ť��
void CShgxDlg::ReadOnlyCancel(void)
{
	GetDlgItem(IDC_BTN_ADD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_EDIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_SHOW);
}

void CShgxDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

//	CDialog::OnOK();
}
