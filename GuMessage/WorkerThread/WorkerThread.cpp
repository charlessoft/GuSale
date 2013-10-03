
#include "WorkerThread.h"
#include "../ado/DataOperate.h"

#include "../DICThreadPool/DICThreadPool.h"
#include "../../gusale/include/GuSaleInfo.h"
#include "../ado/ISQLHelper.h"
#include "../ado/DataOperate.h"
#include "../GuMessageDlg.h"
#include "../StdString.h"

#include <strstream>
#include <iostream>
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
	int nOffset = 0;
	CString strSql;
	CString sDateTime,sTime;
	char szbuf[1024] = {0};
	char szSqlbuf[1024] = {0};
	CGuMessageDlg* pDlg = (CGuMessageDlg*)theApp.m_pMainWnd;
	USES_CONVERSION;
	while( TRUE )
	{
		CGuSaleInfo SaleInfo;
		SaleInfo.GetSaleInfo(INTAKE,nOffset ,10);
		nOffset += 10;
		
		
		EnterCriticalSection( &pDlg->m_lock );
		vector<CGuSaleList*>::iterator Iter;
		CGuSaleList* pSaleList = NULL;
		for ( Iter = SaleInfo.m_pGuSaleData->m_GuSaleListArr.begin(); Iter != SaleInfo.m_pGuSaleData->m_GuSaleListArr.end(); ++Iter )
		{
			CTime CurDatetime = CTime::GetCurrentTime();

			sDateTime = CurDatetime.Format("%y-%d-%m %H:%M:%S"); //ex: 12/10/98
			pSaleList = *Iter;

			sprintf(szSqlbuf, ("insert into INTAKE(id, expert_id, operate, stock, shares, price, operate_time, created_at, updated_at, user_name, uid, avatar, stock_name, my_operate_time) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"),
				pSaleList->m_id.c_str(), pSaleList->m_expert_id.c_str(), pSaleList->m_operate.c_str(), pSaleList->m_stock.c_str(), pSaleList->m_shares.c_str(), pSaleList->m_price.c_str(),
				pSaleList->m_operate_time.c_str(), pSaleList->m_created_at.c_str(), pSaleList->m_updated_at.c_str(), pSaleList->m_user_name.data(), pSaleList->m_user_id.c_str(),
				pSaleList->m_avatar.c_str(), pSaleList->m_stock_name.c_str(), W2A(sDateTime.GetBuffer()));


			g_Logger.Debug( __FILE__, __LINE__, _T("%s"), UTF8ToUnicode(szSqlbuf).c_str() );
 			

			sprintf( szbuf, "select count(*) from INTAKE where id = '%s'", pSaleList->m_id.c_str() );
			CDataTable* pDt = g_DbOperate.GetDtTable(szbuf);

			CString strValue;
			CDataRow* pDataRow = pDt->Rows[0];
			pDataRow->GetColumn(0)->GetValue( strValue );

			if ( strValue.CompareNoCase( L"0" ) != 0 )
			{
				g_Logger.Error( __FILE__, __LINE__, _T("已经存在sql!!"));
			}
			else
			{
				int nRes = g_DbOperate.ExecSql( szSqlbuf );
				if ( nRes != 0 ) //ok
				{
					g_Logger.Debug( __FILE__, __LINE__, _T("插入失败"));
				}

			}

		
		}
		LeaveCriticalSection( &pDlg->m_lock );
		
		
		Sleep(2000);
	}
	return	OTHERRESON;
}

EThreadRoutineExitType CWorkerThread::Run_OffTake()
{
	int nOffset = 0;
	CString strSql;
	CString sDateTime,sTime;
	char szbuf[1024] = {0};
	char szSqlbuf[1024] = {0};
	CGuMessageDlg* pDlg = (CGuMessageDlg*)theApp.m_pMainWnd;
	USES_CONVERSION;
	while( TRUE )
	{
		CGuSaleInfo SaleInfo;
		SaleInfo.GetSaleInfo( OFFTAKE, nOffset, 10 );
		nOffset += 10;


		EnterCriticalSection( &pDlg->m_lock );
		vector<CGuSaleList*>::iterator Iter;
		CGuSaleList* pSaleList = NULL;
		for ( Iter = SaleInfo.m_pGuSaleData->m_GuSaleListArr.begin(); Iter != SaleInfo.m_pGuSaleData->m_GuSaleListArr.end(); ++Iter )
		{
			CTime CurDatetime = CTime::GetCurrentTime();

			sDateTime = CurDatetime.Format("%y-%d-%m %H:%M:%S"); //ex: 12/10/98
			pSaleList = *Iter;

			sprintf(szSqlbuf, ("insert into INTAKE(id, expert_id, operate, stock, shares, price, operate_time, created_at, updated_at, user_name, uid, avatar, stock_name, my_operate_time) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"),
				pSaleList->m_id.c_str(), pSaleList->m_expert_id.c_str(), pSaleList->m_operate.c_str(), pSaleList->m_stock.c_str(), pSaleList->m_shares.c_str(), pSaleList->m_price.c_str(),
				pSaleList->m_operate_time.c_str(), pSaleList->m_created_at.c_str(), pSaleList->m_updated_at.c_str(), pSaleList->m_user_name.data(), pSaleList->m_user_id.c_str(),
				pSaleList->m_avatar.c_str(), pSaleList->m_stock_name.c_str(), W2A(sDateTime.GetBuffer()));


			g_Logger.Debug( __FILE__, __LINE__, _T("%s"), UTF8ToUnicode(szSqlbuf).c_str() );


			sprintf( szbuf, "select count(*) from INTAKE where id = '%s'", pSaleList->m_id.c_str() );
			CDataTable* pDt = g_DbOperate.GetDtTable(szbuf);

			CString strValue;
			CDataRow* pDataRow = pDt->Rows[0];
			pDataRow->GetColumn(0)->GetValue( strValue );

			if ( strValue.CompareNoCase( L"0" ) != 0 )
			{
				g_Logger.Error( __FILE__, __LINE__, _T("已经存在sql!!"));
			}
			else
			{
				int nRes = g_DbOperate.ExecSql( szSqlbuf );
				if ( nRes != 0 ) //ok
				{
					g_Logger.Debug( __FILE__, __LINE__, _T("插入失败"));
				}

			}


		}
		LeaveCriticalSection( &pDlg->m_lock );


		Sleep(2000);
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

//    m_ThreadDialog.SetStopEvent( m_hStopEvent );

 //   INT_PTR nRet = m_ThreadDialog.DoModal();

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



