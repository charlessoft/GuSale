// GuMessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GuMessage.h"
#include "GuMessageDlg.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream> 
#include "StdString.h"
#include "ado/DataOperate.h"
#include "ado/ISQLHelper.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGuMessageDlg dialog




CGuMessageDlg::CGuMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGuMessageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CGuMessageDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGuMessageDlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_UPDATE_MESSAGE, OnUpdateMsg) 
END_MESSAGE_MAP()


// CGuMessageDlg message handlers

BOOL CGuMessageDlg::OnInitDialog()
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
	
	InitData();
 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGuMessageDlg::InitData()
{
	std::locale::global(std::locale("chs"));
	g_Logger.StartSystem(_T("log4cplus._properties"));
	g_Logger.Debug(__FILE__, __LINE__, _T("Init"));
	m_ThreadPool.Create( POOL_SIZE, 1, 1, 1);

	g_DbOperate.AdddDbMgr( _T("Sqlite") );
	g_DbOperate.SetDBType( CDataOperate::DATABASE_TYPE::SQLITE );
	g_DbOperate.SetInstance( _T("saledb.db") );
	g_DbOperate.InitConnstring();
	

	InitializeCriticalSection( &m_lock );

}

void CGuMessageDlg::BeginPullData()
{

  	CWorkerThread* pWorkInTakeThread = new CWorkerThread();
  	pWorkInTakeThread->SetIndex( 0 );
  	pWorkInTakeThread->SetType( THREAD_TYPE_PULL_INTAKE );
  	pWorkInTakeThread->SetAutoDelete( TRUE );
  	if ( FALSE == m_ThreadPool.Run( pWorkInTakeThread ))
  	{
  		g_Logger.Debug( __FILE__, __LINE__, _T("获取买入线程失败!") );
  	}


//    	CWorkerThread* pWorkOffTakeThread = new CWorkerThread();
//    	pWorkOffTakeThread->SetIndex( 0 );
//    	pWorkOffTakeThread->SetType( THREAD_TYPE_PULL_OFFTAKE );
//    	pWorkOffTakeThread->SetAutoDelete( TRUE );
//    	if ( FALSE == m_ThreadPool.Run( pWorkOffTakeThread ))
//    	{
//    		g_Logger.Debug( __FILE__, __LINE__, _T("获取卖出线程失败!") );
//    	}




}

void CGuMessageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGuMessageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuMessageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

const int UNICODE_TXT_FLG = 0xFEFF;  //UNICODE文本标示  
void CGuMessageDlg::OnBnClickedOk()
{
	BeginPullData();

// 	CGuSalePersonInfo GuSalePersonInfo;
// 	GuSalePersonInfo.GetPersonInfo("1915042",12,0,21);
	// TODO: Add your control notification handler code here
	//OnOK();
// 	g_Logger.StartSystem(_T("log4cplus._properties"));
// 	g_Logger.Debug(__FILE__, __LINE__, _T("111"));
// 	UpdateData();
//  	CGuSaleInfo SaleInfo;
//  	SaleInfo.GetSaleInfo(INTAKE,1,m_nview_cnt);
// 	Service CService;
// 	CService.HttpRequest("GET","1");
#if 0	
stringstream strStream;

CString strtmp;
//1947
	for (int i=1947;i<2900000;i++)
	{
		
		strStream.clear();
		strStream.str("");
		strStream << "http://www.gu360.com/home/" << i;
		//strStream << "http://www.gu360.com/home/1915042";// << i;
		  	string strurl = strStream.str();//"http://www.gu360.com/home/1915042";
		   	Service CService;
			strtmp.Format(_T("%d------------------\r\n"),i);
			OutputDebugString(strtmp);
		   	CService.HttpRequest("GET",strurl);
		   	string buffer = CService.m_resp_buffer;
			wstring wzbuf = UTF8ToUnicode(buffer);
			OutputDebugString(wzbuf.data());
			CString strfile;
			  			strfile.Format(_T("C:\\tmp\\%d.txt"),i);
			CFile WriteF;

			WriteF.Open(strfile,CFile::modeCreate | CFile::modeWrite);  
			if(WriteF)  
			{  
				WriteF.Write(&UNICODE_TXT_FLG,2);  
				WriteF.Write(wzbuf.c_str(),wzbuf.length()*2);  
				WriteF.Flush();  
				WriteF.Close();         
			}  
		   	string header = CService.m_resp_header;
	}
#endif
// 	UpdateData(FALSE);
// 	CString str;
// 	str.Format(_T("%d"),SaleInfo.m_pGuSaleData->m_GuSaleListArr.size());
// 	AfxMessageBox(str);
//  	string strurl = "http://www.gu360.com/performance/tradinglist";
//   	Service CService;
//   	string strPostData = "trade_type=1&offset=0&view_cnt=11";
//   	vector<string> custom_header;
//   	custom_header.push_back("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
//   	custom_header.push_back("X-Requested-With: XMLHttpRequest");
//   	custom_header.push_back("Referer: http://www.gu360.com/performance/trading");
//   	PutData putdata;
//   	putdata.data = (char*)strPostData.c_str();
//   	putdata.datalen = strPostData.length();
//   	CService.HttpRequest("POST",strurl,custom_header, &putdata,&CService);
//   	string buffer = CService.m_resp_buffer;
//   	string header = CService.m_resp_header;
//  	int x = 0 ;

}

void CGuMessageDlg::OnDestroy()
{
	CDialog::OnDestroy();

	DeleteCriticalSection( &m_lock );
	// TODO: Add your message handler code here
}


LRESULT CGuMessageDlg::OnUpdateMsg( WPARAM wParam, LPARAM lParam )
{
	int nType = (int)wParam;
	CString strCount;
	strCount.Format( _T("%d个"), (int)lParam );
	if ( nType == THREAD_TYPE_PULL_OFFTAKE )
	{
		SetDlgItemText(IDC_OFFTAKE_LAB, strCount.GetBuffer() );
		
	}
	else
	{
		SetDlgItemText(IDC_INTAKE_LAB, strCount.GetBuffer() );

	}
	return 1;
}
