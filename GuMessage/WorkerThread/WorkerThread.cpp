
#include "WorkerThread.h"
#include "../ado/DataOperate.h"

#include "../DICThreadPool/DICThreadPool.h"
#include "../../gusale/include/GuSaleInfo.h"
#include "../ado/ISQLHelper.h"
#include "../ado/DataOperate.h"
#include "../GuMessageDlg.h"
#include "../StdString.h"
#include "../base64.h"

#include <strstream>
#include <iostream>

#include <iostream> 
#include <sstream> 
#include <string> 
using namespace std;
#define THREADTIME 1000
struct tmpFleType 
{
	int nFileType;
	wstring fileExtent;
};

CWorkerThread::CWorkerThread()
{
    m_bAutoDelete = TRUE;
    m_dwLifeTime = 0;
    m_hThreadTaskDialog = NULL;
    m_hEventDlgClosed = NULL;
	m_nIndex = 0;
	//m_pOperateLog = &COperateLog::GetInstance();

}

CWorkerThread::~CWorkerThread()
{
    // 增加你的函数实现
    if ( NULL != m_hThreadTaskDialog )
    {
        SetDlgClosedEvent();

        if ( WAIT_TIMEOUT == WaitForSingleObject( m_hThreadTaskDialog, 30) )
        {
            ::TerminateThread( m_hThreadTaskDialog, 1 );
        }
        
        CloseHandle( m_hThreadTaskDialog );
        m_hThreadTaskDialog = NULL;
    }

    if ( NULL != m_hEventDlgClosed )
    {
        CloseHandle( m_hEventDlgClosed );
        m_hEventDlgClosed = NULL;
    }

}

VOID CWorkerThread::SetAutoDelete( BOOL bAutoDel )
{
    m_bAutoDelete = bAutoDel;
}

BOOL CWorkerThread::AutoDelete()
{
    return m_bAutoDelete;
}

EThreadRoutineExitType CWorkerThread::Run_InTake()
{
	long nOffset = 0;
	long nindex = 0;
	long nfailindex = 0;
	CString strSql;
	CString sDateTime,sTime;
	char szbuf[1024] = {0};
	char szSqlbuf[1024] = {0};
	CGuMessageDlg* pDlg = (CGuMessageDlg*)theApp.m_pMainWnd;
	int nRes = 0;
	stringstream strline;
	USES_CONVERSION;
	while( TRUE )
	{
		EnterCriticalSection( &pDlg->m_lock );
		CGuSaleInfo SaleInfo;
		SaleInfo.GetSaleInfo(INTAKE,nOffset ,10);
		
		
		if ( !SaleInfo.m_pGuSaleData )
		{
			continue;
		}
		nOffset += 10;
		vector<CGuSaleList*>::iterator Iter;
		CGuSaleList* pSaleList = NULL;
		
		for ( Iter = SaleInfo.m_pGuSaleData->m_GuSaleListArr.begin(); Iter != SaleInfo.m_pGuSaleData->m_GuSaleListArr.end(); ++Iter )
		{
			strline.clear();
			strline.str("");
			CTime CurDatetime = CTime::GetCurrentTime();

			sDateTime = CurDatetime.Format("%y-%m-%d %H:%M:%S"); //ex: 12/10/98

			pSaleList = *Iter;

			strline<<pSaleList->m_uid<<pSaleList->m_expert_id<<pSaleList->m_operate<<pSaleList->m_stock<<pSaleList->m_shares<<pSaleList->m_price<<pSaleList->m_operate_time<<pSaleList->m_created_at<<pSaleList->m_updated_at<<pSaleList->m_user_name<<pSaleList->m_uid<<pSaleList->m_avatar<<pSaleList->m_stock_name;
			string strtmp = strline.str();
			string strbase64 = base64_encode( (unsigned char*)strtmp.c_str(), strtmp.length() );
			sprintf(szSqlbuf, ("insert into INTAKE(id, expert_id, operate, stock, shares, price, operate_time, created_at, updated_at, user_name, uid, avatar, stock_name, my_operate_time,basecode) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"),
				pSaleList->m_id.c_str(), pSaleList->m_expert_id.c_str(), pSaleList->m_operate.c_str(), pSaleList->m_stock.c_str(), pSaleList->m_shares.c_str(), pSaleList->m_price.c_str(),
				pSaleList->m_operate_time.c_str(), pSaleList->m_created_at.c_str(), pSaleList->m_updated_at.c_str(), pSaleList->m_user_name.data(), pSaleList->m_uid.c_str(),
				pSaleList->m_avatar.c_str(), pSaleList->m_stock_name.c_str(), W2A(sDateTime.GetBuffer()), strbase64.c_str());


			g_Logger.Debug( __FILE__, __LINE__, _T("%s"), UTF8ToUnicode(szSqlbuf).c_str() );
 			
			sprintf( szbuf, "select count(*) from INTAKE where basecode = '%s'", strbase64.c_str() );
			CDataTable* pDt = g_DbOperate.GetDtTable(szbuf);

			CString strValue;
			CDataRow* pDataRow = pDt->Rows[0];
			pDataRow->GetColumn(0)->GetValue( strValue );
			delete pDt;
 			if ( strValue.CompareNoCase( L"0" ) != 0 )
 			{
 				g_Logger.Error( __FILE__, __LINE__, _T("已经存在sql!!"));
 			}
 			else
			{
				nRes = g_DbOperate.ExecSql( szSqlbuf );
 				if ( nRes != 0 ) //ok
 				{
 					nfailindex++;
 					g_Logger.Debug( __FILE__, __LINE__, _T("%ld,插入失败"), nfailindex );
 				}
 				else
 				{
 					nindex++;
 					g_Logger.Debug( __FILE__, __LINE__, _T("insert into %ld,insert res = %d"), nindex, nRes );
 					PostMessage( pDlg->m_hWnd, WM_UPDATE_MESSAGE, THREAD_TYPE_PULL_INTAKE, nindex );
 				}
			}
		}
		
 		if ( nOffset % 1000 == 0 )
 		{
 			nOffset = 0;
 		}

		LeaveCriticalSection( &pDlg->m_lock );

		Sleep(1000);
	}
	return	OTHERRESON;
}

EThreadRoutineExitType CWorkerThread::Run_OffTake()
{
	long nOffset = 0;
	long nindex = 0;
	long nfailindex = 0;
	CString strSql;
	CString sDateTime,sTime;
	char szbuf[1024] = {0};
	char szSqlbuf[1024] = {0};
	CGuMessageDlg* pDlg = (CGuMessageDlg*)theApp.m_pMainWnd;
	int nRes = 0 ;
	stringstream strline;
	USES_CONVERSION;
	while( TRUE )
	{
		EnterCriticalSection( &pDlg->m_lock );
		CGuSaleInfo SaleInfo;
		SaleInfo.GetSaleInfo( OFFTAKE, nOffset, 10 );
		nOffset += 10;

		if ( !SaleInfo.m_pGuSaleData )
		{
			continue;
		}
		vector<CGuSaleList*>::iterator Iter;
		CGuSaleList* pSaleList = NULL;
		for ( Iter = SaleInfo.m_pGuSaleData->m_GuSaleListArr.begin(); Iter != SaleInfo.m_pGuSaleData->m_GuSaleListArr.end(); ++Iter )
		{
			strline.clear();
			strline.str("");
			CTime CurDatetime = CTime::GetCurrentTime();

			sDateTime = CurDatetime.Format("%y-%m-%d %H:%M:%S"); //ex: 12/10/98
			pSaleList = *Iter;

			

			strline<<pSaleList->m_id<<pSaleList->m_user_id<<pSaleList->m_stock<<pSaleList->m_count<<pSaleList->m_buy_price<<pSaleList->m_buy_time<<pSaleList->m_sell_time<<pSaleList->m_trans_earn<<pSaleList->m_rate<<pSaleList->m_time_type<<pSaleList->m_opp_id<<pSaleList->m_sell_price<<pSaleList->m_user_name<<pSaleList->m_uid<<pSaleList->m_avatar<<pSaleList->m_stock_name;
			string strtmp = strline.str();
			string strbase64 = base64_encode( (unsigned char*)strtmp.c_str(), strtmp.length() );

			sprintf( szSqlbuf, "insert into OFFTAKE(id, user_id, stock, count, buy_price, buy_time, sell_time, trans_earn, rate, time_type, opp_id, sell_price, user_name, uid, avatar, stock_name,my_operate_time,basecode) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",
				pSaleList->m_id.c_str(), pSaleList->m_user_id.c_str(),pSaleList->m_stock.c_str(),pSaleList->m_count.c_str(),
				pSaleList->m_buy_price.c_str(),pSaleList->m_buy_time.c_str(),pSaleList->m_sell_time.c_str(),pSaleList->m_trans_earn.c_str(),
				pSaleList->m_rate.c_str(),pSaleList->m_time_type.c_str(),pSaleList->m_opp_id.c_str(),pSaleList->m_sell_price.c_str(),
				pSaleList->m_user_name.c_str(),pSaleList->m_uid.c_str(),pSaleList->m_avatar.c_str(),pSaleList->m_stock_name.c_str(),W2A(sDateTime.GetBuffer()),strbase64.c_str());

			
			g_Logger.Debug( __FILE__, __LINE__, _T("%s"), UTF8ToUnicode(szSqlbuf).c_str() );

			sprintf( szbuf, "select count(*) from OFFTAKE where basecode = '%s'", strbase64.c_str() );
			CDataTable* pDt = g_DbOperate.GetDtTable(szbuf);

			CString strValue;
			CDataRow* pDataRow = pDt->Rows[0];
			pDataRow->GetColumn(0)->GetValue( strValue );
			delete pDt;
 			if ( strValue.CompareNoCase( L"0" ) != 0 )
 			{
 				g_Logger.Error( __FILE__, __LINE__, _T("已经存在sql!!"));
 			}
 			else
 			{
 				nRes = g_DbOperate.ExecSql( szSqlbuf );
 				if ( nRes != 0 ) //ok
 				{
 					nfailindex++;
 					g_Logger.Debug( __FILE__, __LINE__, _T("%ld,插入失败"), nfailindex );
 				}
 				nindex++;
 				g_Logger.Debug( __FILE__, __LINE__, _T("insert into %ld,insert res = %d"), nindex, nRes );
				PostMessage( pDlg->m_hWnd, WM_UPDATE_MESSAGE, THREAD_TYPE_PULL_OFFTAKE, nindex );
			}

			
// 			nRes = g_DbOperate.ExecSql( szSqlbuf );
// 			if ( nRes != 0 ) //ok
// 			{
// 				nfailindex++;
// 				g_Logger.Debug( __FILE__, __LINE__, _T("%ld,插入失败"), nfailindex );
// 			}
// 			else
// 			{
// 				nindex++;
// 				g_Logger.Debug( __FILE__, __LINE__, _T("insert into %ld,insert res = %d"), nindex, nRes );
// 			}


		}

 		if ( nOffset % 1000 == 0 )
 		{
 			nOffset = 0;
 		}

		

		LeaveCriticalSection( &pDlg->m_lock );

		Sleep(1000);
	}
	return	OTHERRESON;
}

EThreadRoutineExitType CWorkerThread::Run()
{
    if ( NULL != m_hThreadTaskDialog )
    {
        return OTHERRESON;
    }
	switch( m_nType )
	{
	case THREAD_TYPE_PULL_INTAKE:
		return Run_InTake();
	case THREAD_TYPE_PULL_OFFTAKE:
		return Run_OffTake();
	}
// 	switch(m_nType)
// 	{
// 	case THREAD_TYPE_CUSTOM:
// 		return Run_Consumer();
// 	case THREAD_TYPE_PRODUCE:
// 		{
// #ifdef _GET_URL_DATA_
// 			return Run_Producer_http();
// #else
// 			return Run_Producer();
// #endif
// 		}
//}

  	
    // 增加你的函数实现
    
	EThreadRoutineExitType eExitType = OTHERRESON;

    return eExitType;
}

// 增加你自己的函数实现
VOID CWorkerThread::SetLifeTime( DWORD dwtime )
{
    m_dwLifeTime = dwtime;
}

DWORD CWorkerThread::GetLifeTime()
{
    return m_dwLifeTime;
}

DWORD WINAPI CWorkerThread::ThreadRoutine( LPVOID lpParam )
{
    if ( NULL == lpParam )
    {
        return 0;
    }

    CWorkerThread* pThis = (CWorkerThread*)lpParam;
    pThis->TaskDialog();
    
    pThis->SetDlgClosedEvent();

    return 0;
}


INT_PTR CWorkerThread::TaskDialog()
{
    if ( NULL == m_hEventDlgClosed )
    {
        m_hEventDlgClosed = CreateEvent( NULL, TRUE, FALSE, NULL );
    }

    return 1;
}

VOID CWorkerThread::SetDlgClosedEvent()
{
    SetEvent( m_hEventDlgClosed ); 
}




void CWorkerThread::SetType(int nType)
{
	
	m_nType = nType;
}


void CWorkerThread::SetIndex(int nIndex)
{	
	m_nIndex = nIndex;
}



