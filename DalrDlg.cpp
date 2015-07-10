// DalrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "DalrDlg.h"
#include "TsPrintFrame.h"

// CDalrDlg �Ի���

IMPLEMENT_DYNAMIC(CDalrDlg, CDialog)

CDalrDlg::CDalrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDalrDlg::IDD, pParent)
	, m_mode(0)
	, strNB(_T(""))
	, m_Del(0)
{

}

CDalrDlg::~CDalrDlg()
{
}

void CDalrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CDalrDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDalrDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDOK, &CDalrDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CDalrDlg::OnBnClickedBtnEdit)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDalrDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_DEL, &CDalrDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_PRINT_VIEW, &CDalrDlg::OnBnClickedBtnPrintView)
	ON_BN_CLICKED(IDC_BTN_PRINT, &CDalrDlg::OnBnClickedBtnPrint)

	ON_MESSAGE(UM_TS_BEGIN_PRINTING,OnBeginPrinting)
	ON_MESSAGE(UM_TS_END_PRINTING,OnEndPrinting)
	ON_MESSAGE(UM_TS_PRINT,OnMyPrint)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDalrDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


LRESULT CDalrDlg::OnBeginPrinting(WPARAM wParam,LPARAM lParam)
{	
	//�ڴ˺����н���DC�ĸ������� ���� ��ӡ���о� ��
	CDC* pDC =(CDC*)wParam;
	CPrintInfo* pInfo = (CPrintInfo *)lParam; 
	return TRUE;
}

LRESULT CDalrDlg::OnEndPrinting(WPARAM wParam,LPARAM lParam)
{
	if(m_fontPrinter.m_hObject!=NULL) //��ӡ���� �ͷŴ�ӡ������
		m_fontPrinter.DeleteObject ();
	return TRUE;
}

LRESULT CDalrDlg::OnMyPrint(WPARAM wParam,LPARAM lParam)
{
	CDC* pDC			= (CDC*)wParam;
 	CPrintInfo* pInfo	= (CPrintInfo *)lParam;
 	CFont *font_old, font_Title, font_print, font_write;
 	int y[24];
 	int x[9] = {500,1000, 1470, 1870, 2450,2850, 3420, 3820 ,4400};
	int xx[9],yy[24];
 	int i;
 	for (i = 0; i < 24; i++)
 	{
 		y[i] = 700 + i * (6500-700)/23;
		yy[i] = y[i] + 80;
 	}
	for (i = 0; i < 9; i++)
	{
		xx[i] = x[i] + 50;
	}
 	font_Title.CreateFont(250,   //   nHeight   
 		0,   //   nWidth   
 		0,   //   nEscapement   
 		0,   //   nOrientation   
 		FW_BOLD,   //   nWeight   
 		FALSE,   //   bItalic   
 		FALSE,   //   bUnderline   
 		0,   //   cStrikeOut   
 		ANSI_CHARSET,   //   nCharSet   
 		OUT_DEFAULT_PRECIS,   //   nOutPrecision   
 		CLIP_DEFAULT_PRECIS,   //   nClipPrecision   
 		DEFAULT_QUALITY,   //   nQuality   
 		DEFAULT_PITCH   |   FF_SWISS,   //   nPitchAndFamily   
 		_T( "����"));
 	font_print.CreateFont(100,   //   nHeight   
 		0,   //   nWidth   
 		0,   //   nEscapement   
 		0,   //   nOrientation   
 		FW_BLACK,   //   nWeight   
 		FALSE,   //   bItalic   
 		FALSE,   //   bUnderline   
 		0,   //   cStrikeOut   
 		ANSI_CHARSET,   //   nCharSet   
 		OUT_DEFAULT_PRECIS,   //   nOutPrecision   
 		CLIP_DEFAULT_PRECIS,   //   nClipPrecision   
 		DEFAULT_QUALITY,   //   nQuality   
 		DEFAULT_PITCH   |   FF_SWISS,   //   nPitchAndFamily   
 		_T( "����"));
 	font_write.CreateFont(90,   //   nHeight   
 		0,   //   nWidth   
 		0,   //   nEscapement   
 		0,   //   nOrientation   
 		FW_THIN,   //   nWeight   
 		FALSE,   //   bItalic   
 		FALSE,   //   bUnderline   
 		0,   //   cStrikeOut   
 		ANSI_CHARSET,   //   nCharSet   
 		OUT_DEFAULT_PRECIS,   //   nOutPrecision   
 		CLIP_DEFAULT_PRECIS,   //   nClipPrecision   
 		DEFAULT_QUALITY,   //   nQuality   
 		DEFAULT_PITCH   |   FF_SWISS,   //   nPitchAndFamily   
 		_T( "����"));
	font_old = pDC->SelectObject(&font_Title);	
	pDC->TextOut(1800,200,"Ա����Ϣ��");

	pDC->SelectObject(&font_print);
	pDC->TextOut(650,550,"ְ������");

	//���
 	for (i = 0; i < 7; i++)
 	{
 		pDC->MoveTo(x[0],y[i]);	pDC->LineTo(x[8],y[i]);
 	}
	for (; i < 10; i++)
	{
		pDC->MoveTo(x[1],y[i]); pDC->LineTo(x[8],y[i]);
	}
	for (i = 9; i < 16; i+=2)
	{
		pDC->MoveTo(x[1],y[i]); pDC->LineTo(x[8],y[i]);
	}
	pDC->MoveTo(x[0],y[15]); pDC->LineTo(x[8],y[15]);
	for (i = 16; i < 19; i+=1)
	{
		pDC->MoveTo(x[1],y[i]);	pDC->LineTo(x[8],y[i]);
	}
	for (i = 19; i < 24; i+=2)
	{
		pDC->MoveTo(500,y[i]);	pDC->LineTo(4400,y[i]);
	}
	//����
	pDC->MoveTo(x[0],y[0]); pDC->LineTo(x[0],y[23]);

	pDC->MoveTo(x[1],y[0]); pDC->LineTo(x[1],y[4]);
	pDC->MoveTo(x[1],y[5]); pDC->LineTo(x[1],y[23]);

	pDC->MoveTo(x[2],y[0] ); pDC->LineTo(x[2],y[1]);
	pDC->MoveTo(x[2],y[3] ); pDC->LineTo(x[2],y[5]);
	pDC->MoveTo(x[2],y[6] ); pDC->LineTo(x[2],y[19]);
	pDC->MoveTo(x[2],y[21] ); pDC->LineTo(x[2],y[23]);

	pDC->MoveTo(x[3],y[0] ); pDC->LineTo(x[3],y[2]);
	pDC->MoveTo(x[3]+80,y[3] ); pDC->LineTo(x[3]+80,y[4]);//��ҵѧУ
	pDC->MoveTo(x[3],y[6] ); pDC->LineTo(x[3],y[7]);
	pDC->MoveTo(x[3],y[15] ); pDC->LineTo(x[3],y[19]);
	pDC->MoveTo(x[3],y[21] ); pDC->LineTo(x[3],y[23]);

	pDC->MoveTo(x[4],y[0] ); pDC->LineTo(x[4],y[2]);
	pDC->MoveTo(x[4],y[6] ); pDC->LineTo(x[4],y[9]);
	pDC->MoveTo(x[4],y[15] ); pDC->LineTo(x[4],y[19]);
	pDC->MoveTo(x[4],y[21] ); pDC->LineTo(x[4],y[23]);

	pDC->MoveTo(x[5],y[0] ); pDC->LineTo(x[5],y[3]);
	pDC->MoveTo(x[5],y[4] ); pDC->LineTo(x[5],y[5]);
	pDC->MoveTo(x[5],y[6] ); pDC->LineTo(x[5],y[9]);
	pDC->MoveTo(x[5],y[15] ); pDC->LineTo(x[5],y[19]);

	pDC->MoveTo(x[6],y[0] ); pDC->LineTo(x[6],y[5]);
	pDC->MoveTo(x[6],y[6] ); pDC->LineTo(x[6],y[7]);
	pDC->MoveTo(x[6],y[15] ); pDC->LineTo(x[6],y[19]);
	pDC->MoveTo(x[6],y[21] ); pDC->LineTo(x[6],y[23]);

	pDC->MoveTo(x[7]+80,y[0] ); pDC->LineTo(x[7]+80,y[1]);//������ò
	pDC->MoveTo(x[7],y[3] ); pDC->LineTo(x[7],y[4]);
	pDC->MoveTo(x[7]+80,y[21] ); pDC->LineTo(x[7]+80,y[23]);//�������

	pDC->MoveTo(x[8],y[0] ); pDC->LineTo(x[8],y[23]);

	pDC->SelectObject(&font_print);

	pDC->TextOut(xx[0],yy[0],"����");
	pDC->TextOut(xx[2],yy[0],"�Ա�");
	pDC->TextOut(xx[4],yy[0],"����");
	pDC->TextOut(xx[6],yy[0],"������ò");
	pDC->TextOut(xx[0],yy[1],"����");
	pDC->TextOut(xx[3],yy[1],"����״��");
	pDC->TextOut(xx[5],yy[1],"����״��");
	pDC->TextOut(xx[0],yy[2],"���֤��");
	pDC->TextOut(xx[5],yy[2],"����");
	pDC->TextOut(xx[0],yy[3],"�Ļ��̶�");
	pDC->TextOut(xx[2],yy[3],"��ҵѧУ");
	pDC->TextOut(xx[6],yy[3],"�س�");
	pDC->TextOut(xx[0],yy[4],"�������ڵ�");
	pDC->TextOut(xx[5],yy[4],"��������");
	pDC->TextOut(xx[0],yy[5],"��סַ");
	pDC->TextOut(xx[1],yy[6],"����");
	pDC->TextOut(xx[3],yy[6],"ְ��");
	pDC->TextOut(xx[5],yy[6],"ְ��");
	pDC->TextOut(xx[1],yy[7],"����");
	pDC->TextOut(xx[4],yy[7],"����");
	pDC->TextOut(xx[1],yy[8],"״̬");
	pDC->TextOut(xx[4],yy[8],"�볧ʱ��");
	pDC->TextOut(xx[1],yy[9],"��ʱ");
	pDC->TextOut(xx[1],yy[10],"������ѵ");
	pDC->TextOut(xx[1],yy[11],"��ʱ");
	pDC->TextOut(xx[1],yy[12],"��������");
	pDC->TextOut(xx[1],yy[13],"��Ҫ");
	pDC->TextOut(xx[1],yy[14],"˵������");
	pDC->TextOut(xx[0],yy[9],"����");
	pDC->TextOut(xx[0],yy[11],"���");
	pDC->TextOut(xx[0],yy[16],"���");
	pDC->TextOut(xx[0],yy[17],"��ϵ");
	for (i = 15;i<=18;i++)
	{
		pDC->TextOut(xx[1],yy[i],"��ϵ");
		pDC->TextOut(xx[3],yy[i],"����");
		pDC->TextOut(xx[5],yy[i],"����");
	}
	pDC->TextOut(xx[0],(yy[19]+yy[20])/2,"��ע");
	pDC->TextOut(xx[0],yy[21],"�����");
	pDC->TextOut(xx[0],yy[22],"ǩ��");
	pDC->TextOut(xx[3],(yy[21]+yy[22])/2,"��λ���");
	pDC->TextOut(xx[6],(yy[21]+yy[22])/2,"�������");


	pDC->SelectObject(&font_write);
	CString str;
	//����
	jbxxDlg.GetDlgItemText(IDC_EDIT_NAME,str);
	pDC->TextOut(xx[1],yy[0],str);
	//����
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZGBM,str);
	pDC->TextOut(1850,550,str);
	//�Ա�
	jbxxDlg.GetDlgItemText(IDC_EDIT_SEX,str);
	pDC->TextOut(xx[3],yy[0],str);
	//����
	jbxxDlg.GetDlgItemText(IDC_EDIT_MZ,str);
	pDC->TextOut(xx[5],yy[0],str);
	//��������
	jbxxDlg.GetDlgItemText(IDC_EDIT_BIRTH,str);
	pDC->TextOut(xx[1],yy[1],str);
	//����״��
	jbxxDlg.GetDlgItemText(IDC_EDIT_HY,str);
	pDC->TextOut(xx[4],yy[1],str);
	//����״��
	jbxxDlg.GetDlgItemText(IDC_EDIT_JK,str);
	pDC->TextOut(xx[6],yy[1],str);
	//�Ļ��̶�
	jbxxDlg.GetDlgItemText(IDC_EDIT_WH,str);
	pDC->TextOut(xx[1],yy[3],str);
	//רҵ�س�
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZY,str);
	pDC->TextOut(xx[7],yy[3],str);		
	//��ҵѧУ
	jbxxDlg.GetDlgItemText(IDC_EDIT_XX,str);
	pDC->TextOut(xx[3]+80,yy[3],str);	
	//������ò
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZZ,str);
	pDC->TextOut(xx[7]+80,yy[0],str);	
	//���֤��
	jbxxDlg.GetDlgItemText(IDC_EDIT_ID,str);
	pDC->TextOut(xx[1],yy[2],str);	
	//��������
	jbxxDlg.GetDlgItemText(IDC_EDIT_HKXZ,str);
	pDC->TextOut(xx[6],yy[4],str);	
	//�������ڵ�
	jbxxDlg.GetDlgItemText(IDC_EDIT_HKSZD,str);
	pDC->TextOut(xx[2],yy[4],str);	
	//����
	jbxxDlg.GetDlgItemText(IDC_EDIT_JG,str);
	pDC->TextOut(xx[6],yy[2],str);	
	//��סַ
	jbxxDlg.GetDlgItemText(IDC_EDIT_XZZ,str);
	pDC->TextOut(xx[1],yy[5],str);	

	//���������
	//����
	gzqkDlg.GetDlgItemText(IDC_EDITBM,str);
	pDC->TextOut(xx[2],yy[6],str);	
	//ְ��
	gzqkDlg.GetDlgItemText(IDC_EDIT_ZW,str);
	pDC->TextOut(xx[4],yy[6],str);	
	//ְ��
	gzqkDlg.GetDlgItemText(IDC_EDITZC,str);
	pDC->TextOut(xx[6],yy[6],str);	
	//������
	gzqkDlg.GetDlgItemText(IDC_EDIT_GZ,str);
	pDC->TextOut(xx[2],yy[7],str);	
	//��Ա����
	gzqkDlg.GetDlgItemText(IDC_EDIT_RYXZ,str);
	pDC->TextOut(xx[5],yy[7],str);
	//�볧ʱ��
	gzqkDlg.GetDlgItemText(IDC_EDIT_RCSJ,str);
	pDC->TextOut(xx[5]+80,yy[8],str);
	//��Ա״̬
	gzqkDlg.GetDlgItemText(IDC_EDIT_RYZT,str);
	pDC->TextOut(xx[2],yy[8],str);
	//�������
	gzqkDlg.GetDlgItemText(IDC_EDIT_SCRQ,str);
	pDC->TextOut(xx[7]+80,(yy[21]+yy[22])/2,str);
	//������ѵ
	gzqkDlg.GetDlgItemText(IDC_EDIT_JSPX, str);
	pDC->TextOut(xx[2],yy[9],str);
	//˵������
	gzqkDlg.GetDlgItemText(IDC_EDIT_SMWT, str);
	pDC->TextOut(xx[2],yy[13],str);
	//������
	gzqkDlg.GetDlgItemText(IDC_EDIT_SCYJ, str);
	pDC->TextOut(xx[4],(yy[21]+yy[22])/2,str);
	//��������
	gzqkDlg.GetDlgItemText(IDC_EDIT_JLCF, str);
	pDC->TextOut(xx[2],yy[11],str);
	//��ע
	bzDlg.GetDlgItemText(IDC_EDIT_BZ, str);
	pDC->TextOut(xx[1],yy[19],str);

	//�������ϵ
	CListCtrl *pList = &(shgxDlg.m_list);
	int nItemCount = pList->GetItemCount();
	int n = 0;
	i = 0;
	while (n < nItemCount && n <4)
	{
		str = pList->GetItemText(n,0);
		pDC->TextOut(xx[2],yy[15+i],str);
		str = pList->GetItemText(n,1);
		pDC->TextOut(xx[4],yy[15+i],str);
		str = pList->GetItemText(n,2);
		pDC->TextOut(xx[6],yy[15+i],str);
		n++;
		i++;
	}

	return TRUE;
}

// CDalrDlg ��Ϣ�������

BOOL CDalrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_tab.InsertItem(0,"������Ϣ");
	m_tab.InsertItem(1,"�������");
	m_tab.InsertItem(2,"����ϵ");
	m_tab.InsertItem(3,"��ע");
	//�����ڹ�����ʽ�����½������鿴�������͸��Ӵ���,Ȼ���ٽ�������
	jbxxDlg.m_mode = this->m_mode;
	jbxxDlg.m_strNB = this->strNB;
	jbxxDlg.Create(IDD_DLG_JBXX,GetDlgItem(IDC_TAB1));
	gzqkDlg.m_mode = this->m_mode;
	gzqkDlg.m_strNB = this->strNB;
	gzqkDlg.Create(IDD_DLG_GZQK,GetDlgItem(IDC_TAB1));
	shgxDlg.m_mode = this->m_mode;
	shgxDlg.m_strNB = this->strNB;
	shgxDlg.Create(IDD_DLG_SHGX,GetDlgItem(IDC_TAB1));
	bzDlg.m_mode = this->m_mode;
	bzDlg.m_strNB = this->strNB;
	bzDlg.Create(IDD_DLG_BZ,GetDlgItem(IDC_TAB1));
	CRect rect;
	m_tab.GetClientRect(&rect);
	rect.top += 22;
	rect.bottom -= 4;
	rect.left += 3;
	rect.right -= 4;
	jbxxDlg.MoveWindow(&rect);
	gzqkDlg.MoveWindow(&rect);
	shgxDlg.MoveWindow(&rect);
	bzDlg.MoveWindow(&rect);
	jbxxDlg.ShowWindow(SW_SHOW);
	//���ڵ�Ĭ�ϱ���Ϊ������¼�롱��Ĭ�����ء��༭�������桱��ť	
	if (m_mode == 1)
	//���ԡ��鿴����ʽʹ�øô���ʱ����Ҫ���ı��⣬����ʾ���༭������ӡ������ӡԤ������ť
	{
		SetWindowText("���˵�������");
		GetDlgItem(IDC_BTN_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_PRINT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_PRINT_VIEW)->ShowWindow(SW_SHOW);
		SetDlgItemText(IDC_BTN_EXIT,"�˳�");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDalrDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int sel = m_tab.GetCurSel();
	switch (sel)
	{
	case 0: 
		gzqkDlg.ShowWindow(SW_HIDE);
		shgxDlg.ShowWindow(SW_HIDE);
		bzDlg.ShowWindow(SW_HIDE);
		jbxxDlg.ShowWindow(SW_SHOW);
		break;
	case 1:
		shgxDlg.ShowWindow(SW_HIDE);
		bzDlg.ShowWindow(SW_HIDE);
		jbxxDlg.ShowWindow(SW_HIDE);
		gzqkDlg.ShowWindow(SW_SHOW);
		break;
	case 2:
		gzqkDlg.ShowWindow(SW_HIDE);
		bzDlg.ShowWindow(SW_HIDE);
		jbxxDlg.ShowWindow(SW_HIDE);
		shgxDlg.ShowWindow(SW_SHOW);
		break;
	case 3:
		gzqkDlg.ShowWindow(SW_HIDE);
		shgxDlg.ShowWindow(SW_HIDE);
		jbxxDlg.ShowWindow(SW_HIDE);
		bzDlg.ShowWindow(SW_SHOW);
		break;
	}
}

void CDalrDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString name, number;
	jbxxDlg.GetDlgItemText(IDC_EDIT_NAME, name);
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZGBM,number);
	name.Trim();
	number.Trim();
	if (0 == name.GetLength())
	{
		MessageBox("������ְ������!");
		return;
	}
	if (0 == number.GetLength())
	{
		MessageBox("������ְ�����");
		return;
	}
	AddInfo();
	OnOK();
}
// ���¼��������µ���Ա��¼
void CDalrDlg::AddInfo(void)
{
	CString str, number;
	//int num;
	try
	{
		m_pRecordset = AdoConn.GetRecordSet("select * from m_dadj");
		m_pRecordset->AddNew();	//�ڵ��������������
		SetData();
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
	MessageBox("��ӳɹ�");
}

void CDalrDlg::OnBnClickedBtnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_EDIT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_PRINT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_PRINT_VIEW)->ShowWindow(SW_HIDE);
	
	jbxxDlg.ReadOnlyCancel();
	gzqkDlg.ReadOnlyCancel();
	shgxDlg.ReadOnlyCancel();
	bzDlg.ReadOnlyCancel();
}

// �����桱��ť����Ӧ����
void CDalrDlg::OnBnClickedBtnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str, number;
	//int num;
	jbxxDlg.ReadOnlySet();
	gzqkDlg.ReadOnlySet();
	shgxDlg.ReadOnlySet();
	bzDlg.ReadOnlySet();
	GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_DEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_EDIT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_PRINT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_PRINT_VIEW)->ShowWindow(SW_SHOW);
	try
	{
		_bstr_t sql;
		sql = "delete from m_dadj where zgbm = '"+strNB+"'";
		AdoConn.ExecuteSQL(sql);
		m_pRecordset = AdoConn.GetRecordSet("select * from m_dadj");
		m_pRecordset->AddNew();
		SetData();
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
	MessageBox("�޸��ѱ���");
}

// ��ɾ������ť����Ӧ����
void CDalrDlg::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	try
	{
		_bstr_t sql;
		sql = "delete from m_dadj where zgbm = '"+strNB+"'";
		AdoConn.ExecuteSQL(sql);
		m_pRecordset = AdoConn.GetRecordSet("select * from m_dadj");
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
	MessageBox(strNB + " ��Ա���ѱ�ɾ��");
	m_Del = 1;
	OnOK();
}

// ��m_pRecordset�еĸ����ֶ������Ϣ
void CDalrDlg::SetData(void)
{
	CString str, number;
	int num;
	//�����ֶ�����
	//����
	jbxxDlg.GetDlgItemText(IDC_EDIT_NAME,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("xm", (_bstr_t)str);
	//����
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZGBM,number);
	number.Trim();
	if(number.GetLength()) m_pRecordset->PutCollect("zgbm", (_bstr_t)number);
	//�Ա�
	jbxxDlg.GetDlgItemText(IDC_COMBO_SEX,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("xb", (_bstr_t)str);
	//����
	jbxxDlg.GetDlgItemText(IDC_EDIT_MZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("mz", (_bstr_t)str);
	//��������
	{
		CDateTimeCtrl* p = (CDateTimeCtrl *)jbxxDlg.GetDlgItem(IDC_DATETIMEPICKER_BIRTH);
		COleDateTime time;
		p->GetTime(time);
		str = time.Format("%Y-%m-%d");
		if (str.GetLength())
		{
			m_pRecordset->PutCollect("csny",(_bstr_t)str);;
		}
	}
	//����״��
	jbxxDlg.GetDlgItemText(IDC_EDIT_HY,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("hyzk", (_bstr_t)str);
	//����״��
	jbxxDlg.GetDlgItemText(IDC_EDIT_JK,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("jkzk", (_bstr_t)str);
	//�Ļ��̶�
	{
		jbxxDlg.GetDlgItemText(IDC_COMBO_WH,str);
		str.Trim();
		num = atoi((LPCSTR)(LPCTSTR)str);
		if(str.GetLength()) m_pRecordset->PutCollect("whbm", (_bstr_t)(long)num);
	}
	//רҵ�س�
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZY,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("zytc", (_bstr_t)str);		
	//��ҵѧУ
	jbxxDlg.GetDlgItemText(IDC_EDIT_XX,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("byxx", (_bstr_t)str);
	//������ò
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("zzmm", (_bstr_t)str);
	//���֤��
	jbxxDlg.GetDlgItemText(IDC_EDIT_ID,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("sfzh", (_bstr_t)str);
	//��������
	jbxxDlg.GetDlgItemText(IDC_EDIT_HKXZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("hkxz", (_bstr_t)str);
	//�������ڵ�
	jbxxDlg.GetDlgItemText(IDC_EDIT_HKSZD,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("hkszd", (_bstr_t)str);
	//����
	jbxxDlg.GetDlgItemText(IDC_EDIT_JG,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("jg", (_bstr_t)str);
	//��סַ
	jbxxDlg.GetDlgItemText(IDC_EDIT_XZZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("xzz", (_bstr_t)str);

	//���������
	//����
	{
		gzqkDlg.GetDlgItemText(IDC_COMBO_BM,str);
		str.Trim();
		num = atoi((LPCSTR)(LPCTSTR)str);
		if(str.GetLength()) m_pRecordset->PutCollect("bmbm", (_bstr_t)(long)num);
	}
	//ְ��
	gzqkDlg.GetDlgItemText(IDC_EDIT_ZW,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("zw", (_bstr_t)str);
	//ְ��
	{
		gzqkDlg.GetDlgItemText(IDC_COMBO_ZC,str);
		str.Trim();
		num = atoi((LPCSTR)(LPCTSTR)str);
		if(str.GetLength()) m_pRecordset->PutCollect("zcbm", (_bstr_t)(long)num);
	}
	//������
	gzqkDlg.GetDlgItemText(IDC_EDIT_GZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("gzm", (_bstr_t)str);
	//��Ա����
	gzqkDlg.GetDlgItemText(IDC_EDIT_RYXZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("ryxz", (_bstr_t)str);
	//�볧ʱ��
	{
		CDateTimeCtrl* p = (CDateTimeCtrl *)gzqkDlg.GetDlgItem(IDC_DATETIMEPICKER_RCSJ);
		COleDateTime time;
		p->GetTime(time);
		str = time.Format("%Y-%m-%d");
		if (str.GetLength())
		{
			m_pRecordset->PutCollect("rcsj",(_bstr_t)str);
		}
	}
	//��Ա״̬
	gzqkDlg.GetDlgItemText(IDC_EDIT_RYZT,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("ryzt", (_bstr_t)str);
	//�������
	{
		CDateTimeCtrl* p = (CDateTimeCtrl *)gzqkDlg.GetDlgItem(IDC_DATETIMEPICKER_SCRQ);
		COleDateTime time;
		p->GetTime(time);
		str = time.Format("%Y-%m-%d");
		if (str.GetLength())
		{
			m_pRecordset->PutCollect("scrq",(_bstr_t)str);
		}
	}
	//������ѵ
	gzqkDlg.GetDlgItemText(IDC_EDIT_JSPX, str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("jspx", (_bstr_t)str);
	//˵������
	gzqkDlg.GetDlgItemText(IDC_EDIT_SMWT, str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("smwt", (_bstr_t)str);
	//������
	gzqkDlg.GetDlgItemText(IDC_EDIT_SCYJ, str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("gsyj", (_bstr_t)str);
	//��������
	gzqkDlg.GetDlgItemText(IDC_EDIT_JLCF, str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("jlcf", (_bstr_t)str);
	//��ע
	bzDlg.GetDlgItemText(IDC_EDIT_BZ, str);
	str.Trim();
	m_pRecordset->PutCollect("bz", (_bstr_t)str);
	//���»�����Ϣ��
	m_pRecordset->Update();	

	//�������ϵ
	CListCtrl *pList = &(shgxDlg.m_list);
	m_pRecordset = AdoConn.GetRecordSet("select * from cygx");
	int nItemCount = pList->GetItemCount();
	int n = 0;
	while (n < nItemCount)
	{
		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("zgbm", (_bstr_t)number);
		m_pRecordset->PutCollect("brgx", (_bstr_t)pList->GetItemText(n,0));
		m_pRecordset->PutCollect("xm", (_bstr_t)pList->GetItemText(n,1));
		m_pRecordset->PutCollect("hzgz", (_bstr_t)pList->GetItemText(n,2));
		m_pRecordset->Update();
		n++;
	}
}


void CDalrDlg::OnBnClickedBtnPrintView()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTsPrintFrame *pFrame = new CTsPrintFrame(this);
	pFrame->Create(NULL,_T("��ӡԤ��"),WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
	pFrame->PreviewPrint();
}

void CDalrDlg::OnBnClickedBtnPrint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTsPrintFrame *pFrame = new CTsPrintFrame(this);
	pFrame->Create(NULL,"��ӡ",WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
	pFrame->Print();
}

void CDalrDlg::OnBnClickedBtnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
