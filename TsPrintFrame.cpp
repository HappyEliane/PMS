// TsPrintFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pm3.h"
#include "TsPrintFrame.h"


// CTsPrintFrame

IMPLEMENT_DYNCREATE(CTsPrintFrame, CFrameWnd)

CTsPrintFrame::CTsPrintFrame()
: m_pCallerDlg(NULL)
, m_pView(NULL)
, m_pMainWnd(NULL)
{

}

CTsPrintFrame::~CTsPrintFrame()
{
}

CTsPrintFrame::CTsPrintFrame(CDialog * pCallerDlg)
{
	m_pCallerDlg = pCallerDlg;
	m_pMainWnd = AfxGetApp()->m_pMainWnd;
	AfxGetApp()->m_pMainWnd = this;  //�������ڸ���Ϊ�������Ĵ���
}

BEGIN_MESSAGE_MAP(CTsPrintFrame, CFrameWnd)
		ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTsPrintFrame message handlers

BOOL CTsPrintFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pView = new CTsPrintView();
	m_pView->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,AFX_IDW_PANE_FIRST,pContext);
	return TRUE;
}

void CTsPrintFrame::OnDestroy() 
{
	// TODO: Add your message handler code here
	if(m_pView!=NULL)
	{
		m_pView->DestroyWindow();  //�˺��������Զ������new�����Ĵ���
	}
	CFrameWnd::OnDestroy();
	AfxGetApp()->m_pMainWnd = this->m_pMainWnd; //����ܴ��ڻ�ԭ
}


void CTsPrintFrame::Print()
{
	m_pView->OnTsPrint();
}

void CTsPrintFrame::PreviewPrint()
{
	m_pView->OnTsPrintPreview();
}
