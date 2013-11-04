// GetUserData.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GetUserData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;
#include "CService.h"
using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		//http://www.gu360.com/home/2310185
		string strurl = "http://www.baidu.com";
		Service CService;
		int nRes = CService.HttpRequest("GET",strurl);
		int x = 0;
		
		string resp_header = CService.m_resp_header;
		string resp_buffer = CService.m_resp_buffer;
		printf("------------\r\n");
		printf("resp_buff=%s",resp_header.c_str());
		int y = 0;
	}

	return nRetCode;
}
