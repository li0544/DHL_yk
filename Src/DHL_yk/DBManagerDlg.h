#if !defined(AFX_DBMANAGERDLG_H__5708BB4E_2FE1_447C_BBEE_B96F9DACF047__INCLUDED_)
#define AFX_DBMANAGERDLG_H__5708BB4E_2FE1_447C_BBEE_B96F9DACF047__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBManagerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBManagerDlg dialog

class CDBManagerDlg : public CDialog
{
// Construction
public:
	void OnReceiveComplete();
	//CDBManagerDlg(CWnd* pParent = NULL);   // standard constructor
	CDBManagerDlg(CWnd* pParent = NULL, CIOCPServer* pIOCPServer = NULL, ClientContext *pContext = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBManagerDlg)
	enum { IDD = IDD_DATABASE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	HICON m_hIcon;
	ClientContext* m_pContext;
	CIOCPServer* m_iocpServer;
	UINT m_nCurSel;
	UINT m_nReceiveLength;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDBManagerDlg)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBMANAGERDLG_H__5708BB4E_2FE1_447C_BBEE_B96F9DACF047__INCLUDED_)
