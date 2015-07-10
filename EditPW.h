#pragma once


// CEditPW 对话框

class CEditPW : public CDialog
{
	DECLARE_DYNAMIC(CEditPW)

public:
	CEditPW(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditPW();

// 对话框数据
	enum { IDD = IDD_DLG_EDITPW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
