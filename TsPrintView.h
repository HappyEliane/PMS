#pragma once


// CTsPrintView 视图

class CTsPrintView : public CView
{
	DECLARE_DYNCREATE(CTsPrintView)

protected:
//	CTsPrintView();           // 动态创建所使用的受保护的构造函数
//	virtual ~CTsPrintView();

// Attributes
public:
	void OnTsPrint();  //打印
	void OnTsPrintPreview(); //打印预览

private:
	BOOL m_bPrint;  //TRUE 为打印  FALSE 为打印预览

// Operations
public:
	CTsPrintView();
	virtual ~CTsPrintView();


public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);



#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


