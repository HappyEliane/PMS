// EditPW.cpp : 实现文件
//

#include "stdafx.h"
#include "pm3.h"
#include "EditPW.h"


// CEditPW 对话框

IMPLEMENT_DYNAMIC(CEditPW, CDialog)

CEditPW::CEditPW(CWnd* pParent /*=NULL*/)
	: CDialog(CEditPW::IDD, pParent)
{

}

CEditPW::~CEditPW()
{
}

void CEditPW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditPW, CDialog)
END_MESSAGE_MAP()


// CEditPW 消息处理程序
