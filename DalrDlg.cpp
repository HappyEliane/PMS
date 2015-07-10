// DalrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "DalrDlg.h"
#include "TsPrintFrame.h"

// CDalrDlg 对话框

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
	//在此函数中进行DC的各种设置 字体 打印机行距 等
	CDC* pDC =(CDC*)wParam;
	CPrintInfo* pInfo = (CPrintInfo *)lParam; 
	return TRUE;
}

LRESULT CDalrDlg::OnEndPrinting(WPARAM wParam,LPARAM lParam)
{
	if(m_fontPrinter.m_hObject!=NULL) //打印结束 释放打印机字体
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
 		_T( "黑体"));
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
 		_T( "宋体"));
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
 		_T( "楷体"));
	font_old = pDC->SelectObject(&font_Title);	
	pDC->TextOut(1800,200,"员工信息表");

	pDC->SelectObject(&font_print);
	pDC->TextOut(650,550,"职工编码");

	//横格
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
	//竖格
	pDC->MoveTo(x[0],y[0]); pDC->LineTo(x[0],y[23]);

	pDC->MoveTo(x[1],y[0]); pDC->LineTo(x[1],y[4]);
	pDC->MoveTo(x[1],y[5]); pDC->LineTo(x[1],y[23]);

	pDC->MoveTo(x[2],y[0] ); pDC->LineTo(x[2],y[1]);
	pDC->MoveTo(x[2],y[3] ); pDC->LineTo(x[2],y[5]);
	pDC->MoveTo(x[2],y[6] ); pDC->LineTo(x[2],y[19]);
	pDC->MoveTo(x[2],y[21] ); pDC->LineTo(x[2],y[23]);

	pDC->MoveTo(x[3],y[0] ); pDC->LineTo(x[3],y[2]);
	pDC->MoveTo(x[3]+80,y[3] ); pDC->LineTo(x[3]+80,y[4]);//毕业学校
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

	pDC->MoveTo(x[7]+80,y[0] ); pDC->LineTo(x[7]+80,y[1]);//政治面貌
	pDC->MoveTo(x[7],y[3] ); pDC->LineTo(x[7],y[4]);
	pDC->MoveTo(x[7]+80,y[21] ); pDC->LineTo(x[7]+80,y[23]);//审查日期

	pDC->MoveTo(x[8],y[0] ); pDC->LineTo(x[8],y[23]);

	pDC->SelectObject(&font_print);

	pDC->TextOut(xx[0],yy[0],"姓名");
	pDC->TextOut(xx[2],yy[0],"性别");
	pDC->TextOut(xx[4],yy[0],"民族");
	pDC->TextOut(xx[6],yy[0],"政治面貌");
	pDC->TextOut(xx[0],yy[1],"生日");
	pDC->TextOut(xx[3],yy[1],"婚姻状况");
	pDC->TextOut(xx[5],yy[1],"健康状况");
	pDC->TextOut(xx[0],yy[2],"身份证号");
	pDC->TextOut(xx[5],yy[2],"籍贯");
	pDC->TextOut(xx[0],yy[3],"文化程度");
	pDC->TextOut(xx[2],yy[3],"毕业学校");
	pDC->TextOut(xx[6],yy[3],"特长");
	pDC->TextOut(xx[0],yy[4],"户口所在地");
	pDC->TextOut(xx[5],yy[4],"户口性质");
	pDC->TextOut(xx[0],yy[5],"现住址");
	pDC->TextOut(xx[1],yy[6],"部门");
	pDC->TextOut(xx[3],yy[6],"职务");
	pDC->TextOut(xx[5],yy[6],"职称");
	pDC->TextOut(xx[1],yy[7],"工种");
	pDC->TextOut(xx[4],yy[7],"性质");
	pDC->TextOut(xx[1],yy[8],"状态");
	pDC->TextOut(xx[4],yy[8],"入厂时间");
	pDC->TextOut(xx[1],yy[9],"何时");
	pDC->TextOut(xx[1],yy[10],"技术培训");
	pDC->TextOut(xx[1],yy[11],"何时");
	pDC->TextOut(xx[1],yy[12],"奖励处分");
	pDC->TextOut(xx[1],yy[13],"需要");
	pDC->TextOut(xx[1],yy[14],"说明问题");
	pDC->TextOut(xx[0],yy[9],"工作");
	pDC->TextOut(xx[0],yy[11],"情况");
	pDC->TextOut(xx[0],yy[16],"社会");
	pDC->TextOut(xx[0],yy[17],"关系");
	for (i = 15;i<=18;i++)
	{
		pDC->TextOut(xx[1],yy[i],"关系");
		pDC->TextOut(xx[3],yy[i],"姓名");
		pDC->TextOut(xx[5],yy[i],"工作");
	}
	pDC->TextOut(xx[0],(yy[19]+yy[20])/2,"备注");
	pDC->TextOut(xx[0],yy[21],"填表人");
	pDC->TextOut(xx[0],yy[22],"签名");
	pDC->TextOut(xx[3],(yy[21]+yy[22])/2,"单位意见");
	pDC->TextOut(xx[6],(yy[21]+yy[22])/2,"审查日期");


	pDC->SelectObject(&font_write);
	CString str;
	//姓名
	jbxxDlg.GetDlgItemText(IDC_EDIT_NAME,str);
	pDC->TextOut(xx[1],yy[0],str);
	//编码
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZGBM,str);
	pDC->TextOut(1850,550,str);
	//性别
	jbxxDlg.GetDlgItemText(IDC_EDIT_SEX,str);
	pDC->TextOut(xx[3],yy[0],str);
	//民族
	jbxxDlg.GetDlgItemText(IDC_EDIT_MZ,str);
	pDC->TextOut(xx[5],yy[0],str);
	//出生日期
	jbxxDlg.GetDlgItemText(IDC_EDIT_BIRTH,str);
	pDC->TextOut(xx[1],yy[1],str);
	//婚姻状况
	jbxxDlg.GetDlgItemText(IDC_EDIT_HY,str);
	pDC->TextOut(xx[4],yy[1],str);
	//健康状况
	jbxxDlg.GetDlgItemText(IDC_EDIT_JK,str);
	pDC->TextOut(xx[6],yy[1],str);
	//文化程度
	jbxxDlg.GetDlgItemText(IDC_EDIT_WH,str);
	pDC->TextOut(xx[1],yy[3],str);
	//专业特长
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZY,str);
	pDC->TextOut(xx[7],yy[3],str);		
	//毕业学校
	jbxxDlg.GetDlgItemText(IDC_EDIT_XX,str);
	pDC->TextOut(xx[3]+80,yy[3],str);	
	//政治面貌
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZZ,str);
	pDC->TextOut(xx[7]+80,yy[0],str);	
	//身份证号
	jbxxDlg.GetDlgItemText(IDC_EDIT_ID,str);
	pDC->TextOut(xx[1],yy[2],str);	
	//户口性质
	jbxxDlg.GetDlgItemText(IDC_EDIT_HKXZ,str);
	pDC->TextOut(xx[6],yy[4],str);	
	//户口所在地
	jbxxDlg.GetDlgItemText(IDC_EDIT_HKSZD,str);
	pDC->TextOut(xx[2],yy[4],str);	
	//籍贯
	jbxxDlg.GetDlgItemText(IDC_EDIT_JG,str);
	pDC->TextOut(xx[6],yy[2],str);	
	//现住址
	jbxxDlg.GetDlgItemText(IDC_EDIT_XZZ,str);
	pDC->TextOut(xx[1],yy[5],str);	

	//工作情况表
	//部门
	gzqkDlg.GetDlgItemText(IDC_EDITBM,str);
	pDC->TextOut(xx[2],yy[6],str);	
	//职务
	gzqkDlg.GetDlgItemText(IDC_EDIT_ZW,str);
	pDC->TextOut(xx[4],yy[6],str);	
	//职称
	gzqkDlg.GetDlgItemText(IDC_EDITZC,str);
	pDC->TextOut(xx[6],yy[6],str);	
	//工种名
	gzqkDlg.GetDlgItemText(IDC_EDIT_GZ,str);
	pDC->TextOut(xx[2],yy[7],str);	
	//人员性质
	gzqkDlg.GetDlgItemText(IDC_EDIT_RYXZ,str);
	pDC->TextOut(xx[5],yy[7],str);
	//入厂时间
	gzqkDlg.GetDlgItemText(IDC_EDIT_RCSJ,str);
	pDC->TextOut(xx[5]+80,yy[8],str);
	//人员状态
	gzqkDlg.GetDlgItemText(IDC_EDIT_RYZT,str);
	pDC->TextOut(xx[2],yy[8],str);
	//审查日期
	gzqkDlg.GetDlgItemText(IDC_EDIT_SCRQ,str);
	pDC->TextOut(xx[7]+80,(yy[21]+yy[22])/2,str);
	//技术培训
	gzqkDlg.GetDlgItemText(IDC_EDIT_JSPX, str);
	pDC->TextOut(xx[2],yy[9],str);
	//说明问题
	gzqkDlg.GetDlgItemText(IDC_EDIT_SMWT, str);
	pDC->TextOut(xx[2],yy[13],str);
	//审查意见
	gzqkDlg.GetDlgItemText(IDC_EDIT_SCYJ, str);
	pDC->TextOut(xx[4],(yy[21]+yy[22])/2,str);
	//奖励处分
	gzqkDlg.GetDlgItemText(IDC_EDIT_JLCF, str);
	pDC->TextOut(xx[2],yy[11],str);
	//备注
	bzDlg.GetDlgItemText(IDC_EDIT_BZ, str);
	pDC->TextOut(xx[1],yy[19],str);

	//添加社会关系
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

// CDalrDlg 消息处理程序

BOOL CDalrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_tab.InsertItem(0,"基本信息");
	m_tab.InsertItem(1,"工作情况");
	m_tab.InsertItem(2,"社会关系");
	m_tab.InsertItem(3,"备注");
	//将窗口工作方式（“新建”“查看”）传送给子窗口,然后再建立窗体
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
	//窗口的默认标题为“档案录入”。默认隐藏“编辑”“保存”按钮	
	if (m_mode == 1)
	//当以“查看”方式使用该窗口时，需要更改标题，并显示“编辑”“打印”“打印预览”按钮
	{
		SetWindowText("个人档案详情");
		GetDlgItem(IDC_BTN_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_PRINT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_PRINT_VIEW)->ShowWindow(SW_SHOW);
		SetDlgItemText(IDC_BTN_EXIT,"退出");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDalrDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CString name, number;
	jbxxDlg.GetDlgItemText(IDC_EDIT_NAME, name);
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZGBM,number);
	name.Trim();
	number.Trim();
	if (0 == name.GetLength())
	{
		MessageBox("请输入职工姓名!");
		return;
	}
	if (0 == number.GetLength())
	{
		MessageBox("请输入职工编号");
		return;
	}
	AddInfo();
	OnOK();
}
// 向记录表中添加新的人员记录
void CDalrDlg::AddInfo(void)
{
	CString str, number;
	//int num;
	try
	{
		m_pRecordset = AdoConn.GetRecordSet("select * from m_dadj");
		m_pRecordset->AddNew();	//在档案表中添加新行
		SetData();
	}
	catch(_com_error e)
	{
		MessageBox(e.Description());
		return;
	}
	MessageBox("添加成功");
}

void CDalrDlg::OnBnClickedBtnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
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

// “保存”按钮的响应函数
void CDalrDlg::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
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
	MessageBox("修改已保存");
}

// “删除”按钮的响应函数
void CDalrDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码	
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
	MessageBox(strNB + " 号员工已被删除");
	m_Del = 1;
	OnOK();
}

// 向m_pRecordset中的各个字段添加信息
void CDalrDlg::SetData(void)
{
	CString str, number;
	int num;
	//设置字段数据
	//姓名
	jbxxDlg.GetDlgItemText(IDC_EDIT_NAME,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("xm", (_bstr_t)str);
	//编码
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZGBM,number);
	number.Trim();
	if(number.GetLength()) m_pRecordset->PutCollect("zgbm", (_bstr_t)number);
	//性别
	jbxxDlg.GetDlgItemText(IDC_COMBO_SEX,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("xb", (_bstr_t)str);
	//民族
	jbxxDlg.GetDlgItemText(IDC_EDIT_MZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("mz", (_bstr_t)str);
	//出生日期
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
	//婚姻状况
	jbxxDlg.GetDlgItemText(IDC_EDIT_HY,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("hyzk", (_bstr_t)str);
	//健康状况
	jbxxDlg.GetDlgItemText(IDC_EDIT_JK,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("jkzk", (_bstr_t)str);
	//文化程度
	{
		jbxxDlg.GetDlgItemText(IDC_COMBO_WH,str);
		str.Trim();
		num = atoi((LPCSTR)(LPCTSTR)str);
		if(str.GetLength()) m_pRecordset->PutCollect("whbm", (_bstr_t)(long)num);
	}
	//专业特长
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZY,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("zytc", (_bstr_t)str);		
	//毕业学校
	jbxxDlg.GetDlgItemText(IDC_EDIT_XX,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("byxx", (_bstr_t)str);
	//政治面貌
	jbxxDlg.GetDlgItemText(IDC_EDIT_ZZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("zzmm", (_bstr_t)str);
	//身份证号
	jbxxDlg.GetDlgItemText(IDC_EDIT_ID,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("sfzh", (_bstr_t)str);
	//户口性质
	jbxxDlg.GetDlgItemText(IDC_EDIT_HKXZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("hkxz", (_bstr_t)str);
	//户口所在地
	jbxxDlg.GetDlgItemText(IDC_EDIT_HKSZD,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("hkszd", (_bstr_t)str);
	//籍贯
	jbxxDlg.GetDlgItemText(IDC_EDIT_JG,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("jg", (_bstr_t)str);
	//现住址
	jbxxDlg.GetDlgItemText(IDC_EDIT_XZZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("xzz", (_bstr_t)str);

	//工作情况表
	//部门
	{
		gzqkDlg.GetDlgItemText(IDC_COMBO_BM,str);
		str.Trim();
		num = atoi((LPCSTR)(LPCTSTR)str);
		if(str.GetLength()) m_pRecordset->PutCollect("bmbm", (_bstr_t)(long)num);
	}
	//职务
	gzqkDlg.GetDlgItemText(IDC_EDIT_ZW,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("zw", (_bstr_t)str);
	//职称
	{
		gzqkDlg.GetDlgItemText(IDC_COMBO_ZC,str);
		str.Trim();
		num = atoi((LPCSTR)(LPCTSTR)str);
		if(str.GetLength()) m_pRecordset->PutCollect("zcbm", (_bstr_t)(long)num);
	}
	//工种名
	gzqkDlg.GetDlgItemText(IDC_EDIT_GZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("gzm", (_bstr_t)str);
	//人员性质
	gzqkDlg.GetDlgItemText(IDC_EDIT_RYXZ,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("ryxz", (_bstr_t)str);
	//入厂时间
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
	//人员状态
	gzqkDlg.GetDlgItemText(IDC_EDIT_RYZT,str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("ryzt", (_bstr_t)str);
	//审查日期
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
	//技术培训
	gzqkDlg.GetDlgItemText(IDC_EDIT_JSPX, str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("jspx", (_bstr_t)str);
	//说明问题
	gzqkDlg.GetDlgItemText(IDC_EDIT_SMWT, str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("smwt", (_bstr_t)str);
	//审查意见
	gzqkDlg.GetDlgItemText(IDC_EDIT_SCYJ, str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("gsyj", (_bstr_t)str);
	//奖励处分
	gzqkDlg.GetDlgItemText(IDC_EDIT_JLCF, str);
	str.Trim();
	if(str.GetLength()) m_pRecordset->PutCollect("jlcf", (_bstr_t)str);
	//备注
	bzDlg.GetDlgItemText(IDC_EDIT_BZ, str);
	str.Trim();
	m_pRecordset->PutCollect("bz", (_bstr_t)str);
	//更新基本信息表
	m_pRecordset->Update();	

	//添加社会关系
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
	// TODO: 在此添加控件通知处理程序代码
	CTsPrintFrame *pFrame = new CTsPrintFrame(this);
	pFrame->Create(NULL,_T("打印预览"),WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
	pFrame->PreviewPrint();
}

void CDalrDlg::OnBnClickedBtnPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	CTsPrintFrame *pFrame = new CTsPrintFrame(this);
	pFrame->Create(NULL,"打印",WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
	pFrame->Print();
}

void CDalrDlg::OnBnClickedBtnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
