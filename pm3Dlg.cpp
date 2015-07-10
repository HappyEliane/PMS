// pm3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "pm3Dlg.h"
#include "BmwhDlg.h"
#include "DalrDlg.h"
#include "CxbjDlg.h"
//#include "TjDlg.h"
#include "GlDlg.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cpm3Dlg �Ի���




Cpm3Dlg::Cpm3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cpm3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDB_BITMAP4);
}

void Cpm3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cpm3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_BMWH, &Cpm3Dlg::OnBnClickedBtnBmwh)
	ON_BN_CLICKED(IDC_BTN_DALR, &Cpm3Dlg::OnBnClickedBtnDalr)
	ON_BN_CLICKED(IDC_BTN_CXBJ, &Cpm3Dlg::OnBnClickedBtnCxbj)
	ON_BN_CLICKED(IDC_BTN_TJ, &Cpm3Dlg::OnBnClickedBtnTj)
	ON_BN_CLICKED(IDC_BTN_GL, &Cpm3Dlg::OnBnClickedBtnGl)
	ON_BN_CLICKED(IDOK, &Cpm3Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Cpm3Dlg ��Ϣ�������

BOOL Cpm3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// �û���¼
	CLoginDlg dlg;
	if (dlg.DoModal() != IDOK)
	{
		exit(0);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cpm3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cpm3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
			CDC *dc,dcMem;
			dc=GetDC();
			CBitmap card1;
			dcMem.CreateCompatibleDC(dc);
			card1.LoadBitmap(IDB_BITMAP1);
			dcMem.SelectObject(&card1);
			dc->BitBlt(150,0,770,550,&dcMem,0,0,SRCCOPY);
			DeleteObject(&card1);
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cpm3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cpm3Dlg::OnBnClickedBtnBmwh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CBmwhDlg dlg;
	dlg.DoModal();
}

void Cpm3Dlg::OnBnClickedBtnDalr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDalrDlg dlg;
	dlg.m_mode = 0;//�½�Ա������
	dlg.DoModal();
}

void Cpm3Dlg::OnBnClickedBtnCxbj()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCxbjDlg dlg;
	dlg.DoModal();
}

void Cpm3Dlg::OnBnClickedBtnTj()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CTjDlg dlg;
	dlg.DoModal();*/
}

void Cpm3Dlg::OnBnClickedBtnGl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CGlDlg dlg;
	dlg.DoModal();
}

void Cpm3Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
	OnCancel();
}
