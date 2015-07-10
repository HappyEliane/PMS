// pm3Dlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Cpm3Dlg 对话框




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


// Cpm3Dlg 消息处理程序

BOOL Cpm3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 用户登录
	CLoginDlg dlg;
	if (dlg.DoModal() != IDOK)
	{
		exit(0);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cpm3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cpm3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cpm3Dlg::OnBnClickedBtnBmwh()
{
	// TODO: 在此添加控件通知处理程序代码
	CBmwhDlg dlg;
	dlg.DoModal();
}

void Cpm3Dlg::OnBnClickedBtnDalr()
{
	// TODO: 在此添加控件通知处理程序代码
	CDalrDlg dlg;
	dlg.m_mode = 0;//新建员工档案
	dlg.DoModal();
}

void Cpm3Dlg::OnBnClickedBtnCxbj()
{
	// TODO: 在此添加控件通知处理程序代码
	CCxbjDlg dlg;
	dlg.DoModal();
}

void Cpm3Dlg::OnBnClickedBtnTj()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CTjDlg dlg;
	dlg.DoModal();*/
}

void Cpm3Dlg::OnBnClickedBtnGl()
{
	// TODO: 在此添加控件通知处理程序代码
	CGlDlg dlg;
	dlg.DoModal();
}

void Cpm3Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	OnCancel();
}
