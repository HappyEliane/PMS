// TsPrintView.cpp : ʵ���ļ�
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


// CTsPrintView ��ͼ

void CTsPrintView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CTsPrintView ���

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



// CTsPrintView ��Ϣ�������

/////////////////////////////////////////////////////////////////////////////
// CTsPrintView message handlers

//��ӡ
void CTsPrintView::OnTsPrint()
{
	GetParent()->ShowWindow(SW_SHOWMINNOACTIVE);
	m_bPrint=TRUE;
	CView::OnFilePrint();
}

//��ӡԤ��
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
	if(m_bPrint) //ֱ�Ӵ�ӡ�͹ر���������
		GetParent()->DestroyWindow();
}

void CTsPrintView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	//���ﱾ����DestroyWindow�����Ǳ����ˡ�ʹ��ShowWindowֻ��Ϊ�˲�����
//	GetParent()->DestroyWindow();
	GetParent()->ShowWindow(SW_HIDE);
}

