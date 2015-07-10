// TsPrintView.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "TsPrintView.h"
#include "TsPrintFrame.h"


// CTsPrintView

IMPLEMENT_DYNCREATE(CTsPrintView, CView)

CTsPrintView::CTsPrintView()
{

}

CTsPrintView::~CTsPrintView()
{
}

BEGIN_MESSAGE_MAP(CTsPrintView, CView)
END_MESSAGE_MAP()


// CTsPrintView 绘图

void CTsPrintView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CTsPrintView 诊断

#ifdef _DEBUG
void CTsPrintView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CTsPrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG



// CTsPrintView 消息处理程序

/////////////////////////////////////////////////////////////////////////////
// CTsPrintView message handlers

//打印
void CTsPrintView::OnTsPrint()
{
	GetParent()->ShowWindow(SW_SHOWMINNOACTIVE);
	m_bPrint=TRUE;
	CView::OnFilePrint();
}

//打印预览
void CTsPrintView::OnTsPrintPreview()
{
	GetParent()->ShowWindow(SW_SHOWMAXIMIZED);
	m_bPrint=FALSE;
	CView::OnFilePrintPreview();
}


BOOL CTsPrintView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	if(DoPreparePrinting(pInfo))
		return TRUE;
	else
	{
		GetParent()->DestroyWindow();
		return FALSE;
	}
}

void CTsPrintView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnBeginPrinting(pDC, pInfo);
	CTsPrintFrame *pFrame =(CTsPrintFrame *)GetParent();
	pFrame->m_pCallerDlg->SendMessage(UM_TS_BEGIN_PRINTING,(WPARAM) pDC, (LPARAM) pInfo);
}

void CTsPrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnPrint(pDC,pInfo);
	CTsPrintFrame *pFrame =(CTsPrintFrame *)GetParent();
	pFrame->m_pCallerDlg->SendMessage(UM_TS_PRINT,(WPARAM) pDC, (LPARAM) pInfo) ;
}

void CTsPrintView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnEndPrinting(pDC, pInfo);
	CTsPrintFrame *pFrame =(CTsPrintFrame *)GetParent();
	pFrame->m_pCallerDlg->SendMessage(UM_TS_END_PRINTING,(WPARAM) pDC, (LPARAM) pInfo);
	if(m_bPrint) //直接打印就关闭整个窗口
		GetParent()->DestroyWindow();
}

void CTsPrintView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	//这里本该用DestroyWindow，但是崩溃了。使用ShowWindow只是为了不崩溃
//	GetParent()->DestroyWindow();
	GetParent()->ShowWindow(SW_HIDE);
}

