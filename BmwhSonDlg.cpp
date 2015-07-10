// BmwhSonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "BmwhSonDlg.h"


// CBmwhSonDlg �Ի���

IMPLEMENT_DYNAMIC(CBmwhSonDlg, CDialog)

CBmwhSonDlg::CBmwhSonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBmwhSonDlg::IDD, pParent)
	, m_table(0)
	, m_lock(false)
	, m_columnName1(_T(""))
	, m_columnName2(_T(""))
	, m_tableName(_T(""))
{
	m_table = 0;
}

CBmwhSonDlg::~CBmwhSonDlg()
{
}

void CBmwhSonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CBmwhSonDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_ADD, &CBmwhSonDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CBmwhSonDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_QRTJ, &CBmwhSonDlg::OnBnClickedBtnQrtj)
	ON_BN_CLICKED(IDC_BTN_QRXG, &CBmwhSonDlg::OnBnClickedBtnQrxg)
	ON_BN_CLICKED(IDC_BTN_CANCLE1, &CBmwhSonDlg::OnBnClickedBtnCancle1)
	ON_BN_CLICKED(IDC_BTN_CANCLE2, &CBmwhSonDlg::OnBnClickedBtnCancle2)
	ON_BN_CLICKED(IDC_BTN_DEL, &CBmwhSonDlg::OnBnClickedBtnDel)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CBmwhSonDlg::OnHdnItemclickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CBmwhSonDlg::OnNMClickList1)
	ON_BN_CLICKED(IDOK, &CBmwhSonDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CBmwhSonDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CBmwhSonDlg ��Ϣ�������

BOOL CBmwhSonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//Ϊ�б���ͼ�ؼ����÷��
	m_list.SetExtendedStyle(LVS_EX_FLATSB 
		| LVS_EX_FULLROWSELECT 
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_ONECLICKACTIVATE
		| LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,"����",LVCFMT_CENTER,100,-1);
	m_list.InsertColumn(1,"����",LVCFMT_CENTER,100,-1);


	m_AddCtrlArr[0] = (CWnd *)GetDlgItem(IDC_TEXT_CZ);
	m_AddCtrlArr[1] = (CWnd *)GetDlgItem(IDC_TEXT_BM1);
	m_AddCtrlArr[2] = (CWnd *)GetDlgItem(IDC_TEXT_NR1);
	m_AddCtrlArr[3] = (CWnd *)GetDlgItem(IDC_EDIT_BM1);
	m_AddCtrlArr[4] = (CWnd *)GetDlgItem(IDC_EDIT_NR1);
	m_AddCtrlArr[5] = (CWnd *)GetDlgItem(IDC_BTN_QRTJ);
	m_AddCtrlArr[6] = (CWnd *)GetDlgItem(IDC_BTN_CANCLE1);


	m_EditCtrlArr[0] = (CWnd *)GetDlgItem(IDC_TEXT_CZ);
	m_EditCtrlArr[1] = (CWnd *)GetDlgItem(IDC_TEXT_BM1);
	m_EditCtrlArr[2] = (CWnd *)GetDlgItem(IDC_TEXT_NR1);
	m_EditCtrlArr[3] = (CWnd *)GetDlgItem(IDC_EDIT_BM1);
	m_EditCtrlArr[4] = (CWnd *)GetDlgItem(IDC_EDIT_NR1);
	m_EditCtrlArr[5] = (CWnd *)GetDlgItem(IDC_BTN_QRXG);
	m_EditCtrlArr[6] = (CWnd *)GetDlgItem(IDC_BTN_CANCLE2);
	m_EditCtrlArr[7] = (CWnd *)GetDlgItem(IDC_TEXT_BM2);
	m_EditCtrlArr[8] = (CWnd *)GetDlgItem(IDC_TEXT_NR2);
	m_EditCtrlArr[9] = (CWnd *)GetDlgItem(IDC_EDIT_BM2);
	m_EditCtrlArr[10] = (CWnd *)GetDlgItem(IDC_EDIT_NR2);

	ReOpen();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
//��ʾ����ӱ��롱����
void CBmwhSonDlg::ShowAddFace(void)
{
	GetDlgItem(IDC_TEXT_CZ)->SetWindowText("��ӱ���");
	((CEdit *)GetDlgItem(IDC_EDIT_BM1))->SetReadOnly(FALSE);
	GetDlgItem(IDC_EDIT_BM1)->SetWindowText("");
	((CEdit *)GetDlgItem(IDC_EDIT_NR1))->SetReadOnly(FALSE);
	GetDlgItem(IDC_EDIT_NR1)->SetWindowText("");
	int i;
	for (i = 0; i < 7; i++)
	{
		m_AddCtrlArr[i]->ShowWindow(SW_SHOW);
	}
}

// ���ء���ӱ��롱����
void CBmwhSonDlg::HideAddFace(void)
{
	int i;

	for (i = 0; i < 7; i++)
	{
		m_AddCtrlArr[i]->ShowWindow(SW_HIDE);
	}
}

// ��ʾ���޸ı��롱����
void CBmwhSonDlg::ShowEditFace(void)
{
	GetDlgItem(IDC_TEXT_CZ)->SetWindowText("�޸ı���");
	((CEdit *)GetDlgItem(IDC_EDIT_BM1))->SetReadOnly(TRUE);
	GetDlgItem(IDC_EDIT_BM1)->SetWindowText("");
	((CEdit *)GetDlgItem(IDC_EDIT_NR1))->SetReadOnly(TRUE);
	GetDlgItem(IDC_EDIT_NR1)->SetWindowText("");
	GetDlgItem(IDC_EDIT_NR2)->SetWindowText("");
	int i;
	for (i = 0; i < 11; i++)
	{
		m_EditCtrlArr[i]->ShowWindow(SW_SHOW);
	}
	m_lock = true;
}

// ���ء��޸ı��롱����
void CBmwhSonDlg::HideEditFace(void)
{
	int i;
	for (i = 0; i < 11; i++)
	{
		m_EditCtrlArr[i]->ShowWindow(SW_HIDE);
	}
	m_lock = false;
}


// ��������ӡ���ť֮��Ķ���
void CBmwhSonDlg::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HideEditFace();
	ShowAddFace();
	GetDlgItem(IDC_EDIT_BM1)->GetFocus();
}

// �������༭����ť֮��Ķ���
void CBmwhSonDlg::OnBnClickedBtnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HideAddFace();
	ShowEditFace();
	int index = m_list.GetNextItem(-1, LVNI_SELECTED);//����ɹ��򷵻���һ����ľ�������򷵻�NULL
	if (index == -1)
	{
		MessageBox("��ѡ��Ҫ�༭����");
		OnBnClickedBtnCancle2();
		return;
	}
	CString temp = m_list.GetItemText(index, 0);	//���ѡ���ı���
	SetDlgItemText(IDC_EDIT_BM1,temp);
	SetDlgItemText(IDC_EDIT_BM2,temp);
	temp = m_list.GetItemText(index, 1);
	SetDlgItemText(IDC_EDIT_NR1,temp);
}

// ˢ�¶Ի���������ʾ�����б�
void CBmwhSonDlg::ReOpen(void)
{
	CString title;
	_bstr_t sql;
	ResetColumnName();
	switch (m_table)
	{
	case 0: 
		title = "ְ�Ʊ����";
		sql = "select * from bm_zc order by zcbm desc";
		break;
	case 1: 
		title = "���ű����";
		sql = "select * from bm_bm order by bmbm desc";
		break;
	case 2:
		title = "�Ļ��̶ȱ����";
		sql = "select * from bm_wh order by whbm desc";
		break;
	}
	
	GetDlgItem(IDC_TEXT_LX)->SetWindowText("");
	m_list.DeleteAllItems();
	if(m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pRecordset = AdoConn.GetRecordSet(sql);	//�򿪼�¼��
	while(AdoConn.m_pRecordset->adoEOF==0)		//������¼��
	{
		m_list.InsertItem(0, "");
		//����¼���ֶ��еļ�¼��ӵ��б���ͼ�ؼ���
		m_list.SetItemText(0,0,(char *)(_bstr_t)m_pRecordset->GetCollect((LPCSTR)(LPCTSTR)m_columnName1));
		m_list.SetItemText(0,1,(char *)(_bstr_t)m_pRecordset->GetCollect((LPCSTR)(LPCTSTR)m_columnName2));
		//ָ����һ����¼
		m_pRecordset->MoveNext();
	}
	HideAddFace();
	HideEditFace();
}

// ���ñ���������
void CBmwhSonDlg::ResetColumnName(void)
{
	switch (m_table)
	{
	case 0: 
		m_tableName = "bm_zc";
		m_columnName1 = "zcbm";
		m_columnName2 = "zcmc";
		break;
	case 1: 
		m_tableName = "bm_bm";
		m_columnName1 = "bmbm";
		m_columnName2 = "bmm";
		break;
	case 2:
		m_tableName = "bm_wh";
		m_columnName1 = "whbm";
		m_columnName2 = "whcd";
		break;
	}
}

void CBmwhSonDlg::OnBnClickedBtnQrtj()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str1, str2;
	GetDlgItemText(IDC_EDIT_BM1, str1);
	GetDlgItemText(IDC_EDIT_NR1, str2);
	str1.Trim();
	str2.Trim();
	try
	{
		m_pRecordset->AddNew();	//�������
		//�����ֶ�����
		m_pRecordset->PutCollect((_variant_t)m_columnName1, (_bstr_t)str1);
		m_pRecordset->PutCollect((_variant_t)m_columnName2, (_bstr_t)str2);
		m_pRecordset->Update();	//�����ֶ�
	}
	catch(...)
	{
		MessageBox("����ʧ�ܣ�");
		return;
	}
	MessageBox("��ӳɹ�");
	ReOpen();
}

void CBmwhSonDlg::OnBnClickedBtnQrxg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str1, str2,oldno;
	BOOL b;
	GetDlgItemText(IDC_EDIT_BM1,oldno);
	GetDlgItemText(IDC_EDIT_BM2, str1);
	GetDlgItemText(IDC_EDIT_NR2, str2);
	str1.Trim();
	str2.Trim();
	str2 = "'" + str2 + "'";
	_bstr_t sql;
	sql = "update "+m_tableName+" set " + m_columnName1 + " = " + str1 +"," + m_columnName2 + " = " +str2+" where "+m_columnName1+" = "+oldno;
	try
	{
		b=AdoConn.ExecuteSQL(sql);
	}
	catch(...)
	{
		MessageBox("����ʧ�ܣ�");
		return;
	}
	if(b) MessageBox("�޸ĳɹ�");
	else MessageBox("�޸�ʧ��");
	ReOpen();
}

void CBmwhSonDlg::OnBnClickedBtnCancle1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HideAddFace();
}

void CBmwhSonDlg::OnBnClickedBtnCancle2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HideEditFace();
}

void CBmwhSonDlg::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (index == -1)
	{
		MessageBox("��ѡ��Ҫɾ������");
	}
	if(IDNO == MessageBox("ȷ��Ҫɾ�����⽫ɾ�����ݿ�����ص���Ա��Ϣ!","����",MB_YESNO))
	{
		return;
	}
	CString bm = m_list.GetItemText(index, 0);	//���ѡ���ı���
	_bstr_t sql;
	sql = "update m_dadj set "+m_columnName1+" = null where "+m_columnName1+" = "+bm;
	AdoConn.ExecuteSQL(sql);
	sql = "delete from "+m_tableName+" where "+m_columnName1+" = "+bm;
	AdoConn.ExecuteSQL(sql);
	MessageBox("ɾ���ɹ�!");
	ReOpen();
}

void CBmwhSonDlg::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
// 	if (!m_lock) return;
// 	OnBnClickedBtnEdit();
}

void CBmwhSonDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	////LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	//// TODO: �ڴ���ӿؼ�֪ͨ����������
	//*pResult = 0;
	//if (!m_lock) return;
	//OnBnClickedBtnEdit();
}

void CBmwhSonDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
	GetParent()->GetParent()->SendMessage(WM_CLOSE);//ģ�ⰴ�¸������е�IDCANCEL��ť
}

void CBmwhSonDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//// TODO: �ڴ���ӿؼ�֪ͨ����������
	//*pResult = 0;
}
