// pm3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ADOConn.h"


// Cpm3App:
// �йش����ʵ�֣������ pm3.cpp
//

class Cpm3App : public CWinApp
{
public:
	Cpm3App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cpm3App theApp;
extern ADOConn AdoConn;
extern CString CurrentUser;