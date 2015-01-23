// gh0stView.h : interface of the CGh0stView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GH0STVIEW_H__14553897_2664_48B4_A82B_6D6F8F789ED3__INCLUDED_)
#define AFX_GH0STVIEW_H__14553897_2664_48B4_A82B_6D6F8F789ED3__INCLUDED_

#include "gh0stDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGh0stView : public CView
{
protected: // create from serialization only

	DECLARE_DYNCREATE(CGh0stView)

// Attributes
public:
	CGh0stView();
	CGh0stDoc* GetDocument();

	//CXTPTabControl m_wndTabControl;
	CTabCtrl m_wndTabControl;
	BOOL	UpDateNumber();
	void	UpdateDocTitle();
	BOOL	AddGroup( LPCTSTR lpszTitle );

	HWND	TCItem_GetHandle(int index);			//返回指定页的句柄
	HWND    TCItemSel_GetHandle();					//返回选中页的句柄
	void    TCItem_SetText(int index, LPSTR tit);	//设置指定页标题
	LPSTR	TCItem_GetText(int index);				//返回指定页标题
	LPSTR	TCItemSel_GetText();					//返回选中页标题
	
	//listCWnd list_wnd;
	LONG l_Botton;
	LONG l_Split_C;
	int  TabIndex;
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGh0stView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
//	int m_nCount;
	virtual ~CGh0stView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int					m_iHitTest;
// Generated message map functions
protected:
	//{{AFX_MSG(CGh0stView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSelectedChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
private:
	BOOL AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle);
	afx_msg LRESULT OnAddFindGroup(WPARAM, LPARAM);
};

#ifndef _DEBUG  // debug version in gh0stView.cpp
inline CGh0stDoc* CGh0stView::GetDocument()
   { return (CGh0stDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GH0STVIEW_H__14553897_2664_48B4_A82B_6D6F8F789ED3__INCLUDED_)
