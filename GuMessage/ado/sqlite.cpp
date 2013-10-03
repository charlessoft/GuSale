#include "sqlite.h"
#include "../StdString.h"
#ifdef _LOG4CPLUS_
	#include "../../include/LoggerModule.h" 
#endif
//#include "../../include/StdString.h"
#include <algorithm>
#include <tchar.h>
//////////////////////////////////////////////////////////////////////////
//需要设置连接 sqlite路径
#pragma comment(lib,"../gusale/lib/sqlite/sqlite3.lib")
//////////////////////////////////////////////////////////////////////////


CDataTable* CSqlite::m_pDatatable = NULL;
CSqlite::CSqlite()
{
	m_pdb = NULL;
	pErrMsg = NULL;
	
}

CSqlite::~CSqlite()
{

}

int CSqlite::Open(LPCTSTR sqlData)
{
	string strSqlData = UnicodeToUTF8(sqlData);
	int res = sqlite3_open(strSqlData.c_str(),&m_pdb);
	if ( res != SQLITE_OK )
	{
		//fprintf(stderr, "无法打开数据库: %s", sqlite3_errmsg(db));

#ifdef _LOG4CPLUS_
		g_Logger.Error(__FILE__,__LINE__,_T("无法打开数据库:%s"),sqlite3_errmsg(m_pdb));
#endif
		//return(1);
		return res;
	}
	return res;
}


BOOL CSqlite::Open(LPCTSTR lpstrConnection /*= _T("")*/, LPCTSTR lpstrUserID /*= _T("")*/, LPCTSTR lpstrPassword /*= _T("")*/)
{
	if (IsOpen())
	{
		Close();
	}
	//string strSqlData = UnicodeToUTF8(lpstrConnection);
	m_strConnect = UnicodeToUTF8(lpstrConnection);
	int res = sqlite3_open(m_strConnect.c_str(),&m_pdb);
	if ( res != SQLITE_OK )
	{
#ifdef _LOG4CPLUS_
		g_Logger.Error(__FILE__,__LINE__,_T("无法打开数据库:%s"),sqlite3_errmsg(m_pdb));
		//return(1);
#endif
		return 1;
	}
	return 0;
}

//CDataTable* m_pDatatable = new CDataTable;;
int CSqlite::_sql_callback(void * notused, int argc, char ** argv, char ** szColName)
{
	
	int i;
	CDataRow* pRow = m_pDatatable->NewRow(FALSE);
	
	for ( i=0; i < argc; i++ )
	{
		//printf( "%s = %s\n", szColName[i], argv[i] == 0 ? "NUL" : argv[i] );

	//	strTmp.Format(_T("%s = %s\n"), UTF8ToUnicode(szColName[i]).c_str(), argv[i] == 0 ? _T("NULL") : UTF8ToUnicode(argv[i]).c_str() );
		//strTmp.Format(_T("%s"),UTF8ToUnicode(szColName[i]).c_str());
		//str += strTmp;
		
		CDataColumn* pCol = NULL;
		pCol = pRow->GetColumn(UTF8ToUnicode(szColName[i]));

		if (!pCol)
		{
			pCol = new CDataColumn;
			_tcscpy_s(pCol->m_ColumnName ,32,UTF8ToUnicode(szColName[i]).c_str());
			pRow->AddColumn(pCol);
			
		}
		if(argv[i])
			pRow->m_pColumns[i]->value = UTF8ToUnicode(argv[i]).c_str();

		
		BOOL bFlage = FALSE;
		for (size_t i=0,sz=m_pDatatable->Columns.size();i<sz;i++)
		{
			if (_tcsicmp(pCol->m_ColumnName ,m_pDatatable->Columns[i]->m_ColumnName)==0)
			{
				bFlage  = TRUE;
				break;
			}
		}
		if (bFlage==FALSE)
		{
			m_pDatatable->Columns.push_back(new CDataColumn(*pCol));
			bFlage = FALSE;
		}
		
	}

	m_pDatatable->Rows.push_back(pRow);
	
// 	CDataRow* pDr =NULL;
// 	for(int i=0,sz=argc;i<sz;i++)
// 	{
// 		pDr = m_pDatatable->NewRow();
// 		ASSERT(pDr);
// 		//for (int j=0,sz=GetFieldCount();j<sz;j++)
// 		{
// 			CDataColumn* pColumn=NULL;
// 			pColumn = ((CDataColumn*)pDr->m_pColumns[i]);
// 			//GetFieldValue(i,pColumn->value );
// 			pColumn->value =UTF8ToUnicode(argv[i]).c_str();
// 			int x = 0 ;
// 		}
// 
// 		
// 
// 		//MoveNext();
// 	}
// 	m_pDatatable->Rows.push_back(pDr);
return 0;
}

int CSqlite::Execute(LPCTSTR lpstrExec)
{
	string strSqlExec = UnicodeToUTF8(lpstrExec);
	//sqlite3_exec(m_pdb,strSqlExec.c_str(),0,_sql_callback,)
	char* pErrMsg=0;

	int res = sqlite3_exec( m_pdb, strSqlExec.c_str(), 0, 0, &pErrMsg);
	return res;
}

int CSqlite::Execute(LPCSTR lpstrExec)
{
	//string strSqlExec = UnicodeToUTF8(lpstrExec);
	//sqlite3_exec(m_pdb,strSqlExec.c_str(),0,_sql_callback,)
	char* pErrMsg=0;

	int res = sqlite3_exec( m_pdb, lpstrExec, 0, 0, &pErrMsg);
	return res;
}

BOOL CSqlite::IsOpen()
{
	if (m_pdb)
	{
		return TRUE;
	}
	return FALSE;
}


void CSqlite::Close()
{
	sqlite3_close(m_pdb);
	return;
}


CDataTable* CSqliteRecordset::GetDt(CDataTable* dt)
{
	dt = m_pdata->m_pDatatable;
	return dt;
}

int _sql_callbacka(void * notused, int argc, char ** argv, char ** szColName)
{

	return 1;
}
BOOL CSqliteRecordset::Open(LPCTSTR lpstrExec /*= _T("")*/, int nOption /*= IRecoredset::openUnknown*/,CDataTable* pDt /*= NULL*/)
{
	if (m_pdata->IsOpen())
	{
		m_pdata->Close();
	}
	m_pdata->Open(UTF8ToUnicode(m_pdata->m_strConnect.c_str()).c_str());
	string strSqlExec = UnicodeToUTF8(lpstrExec);
	char* pErrMsg=0;
	m_pdata->m_pDatatable = pDt;//new CDataTable;
	//int res = sqlite3_exec(m_pdata->m_pdb,strSqlExec.c_str(),0,_sql_callbacka,&pErrMsg);
	int res = sqlite3_exec(m_pdata->m_pdb,strSqlExec.c_str(), m_pdata->_sql_callback, 0, &pErrMsg);
	
	return 1;
}

BOOL CSqliteRecordset::Open( LPCSTR lpstrExec /*= ""*/, int nOption /*= IRecoredset::openUnknown*/, CDataTable* pDt /*= NULL*/ )
{
	if (m_pdata->IsOpen())
	{
		m_pdata->Close();
	}
	m_pdata->Open(UTF8ToUnicode(m_pdata->m_strConnect.c_str()).c_str());
	string strSqlExec = lpstrExec;//UnicodeToUTF8(lpstrExec);
	char* pErrMsg=0;
	m_pdata->m_pDatatable = pDt;//new CDataTable;
	//int res = sqlite3_exec(m_pdata->m_pdb,strSqlExec.c_str(),0,_sql_callbacka,&pErrMsg);
	int res = sqlite3_exec(m_pdata->m_pdb,strSqlExec.c_str(), m_pdata->_sql_callback, 0, &pErrMsg);
	return 1;
}