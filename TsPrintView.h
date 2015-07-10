#pragma once


// CTsPrintView ��ͼ

class CTsPrintView : public CView
{
	DECLARE_DYNCREATE(CTsPrintView)

protected:
//	CTsPrintView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
//	virtual ~CTsPrintView();

// Attributes
public:
	void OnTsPrint();  //��ӡ
	void OnTsPrintPreview(); //��ӡԤ��

private:
	BOOL m_bPrint;  //TRUE Ϊ��ӡ  FALSE Ϊ��ӡԤ��

// Operations
public:
	CTsPrintView();
	virtual ~CTsPrintView();


public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
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


