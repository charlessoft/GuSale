
#include "DataOperate.h"
CDataOperate* CDataOperate::m_pInstance = NULL;
CDataOperate::CDataOperate(void)
{
//	m_strConnection = _T("Provider=MSDAORA.1;User ID=dms2;Password=dms2;Data Source=10.142.49.234:1521;Persist Security Info=False");
	//m_strConnection = _T("")
	 //m_strConnection =_T("Provider=OraOLEDB.Oracle;User ID=dms2;Password=dms2;Data Source=10.142.49.234;");
	//m_strConnection =_T("Provider=MSDAORA.1;User ID=dms2;Password=dms2;Data Source=10.142.49.234:1521;Persist Security Info=False");
	/*m_strConnection.Format(_T("Provider=OraOLEDB.Oracle.1;User ID=%s;Password=%s;Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=%s)(PORT=%s))(CONNECT_DATA=(SERVICE_NAME=%s)));Persist Security Info=False"),\
		_T("dms2"),_T("dms2"),_T("10.142.49.37"),_T("1521"),_T("ecm"));*/

	CDataOperate::m_pInstance = NULL;
// 	m_strUid.Empty();
// 	m_strPwd.Empty();
// 	m_strIp.Empty();
// 	m_strPort.Empty();
// 	m_strInstance.Empty();
// 	m_strSqlTemp.Empty();
// 	m_strSqlMuliTemp.Empty();
// 	m_nLimit=100;
// 	m_pRes = NULL;
// 	m_pDatabase = NULL;
	



}

void CDataOperate::InitConnstring()
{
	if (m_pCurDbMgr)
	{
		m_pCurDbMgr->InitConnstring(m_pCurDbMgr->m_nDbType);
	}
	//m_strConnection.Format(_T("Provider=OraOLEDB.Oracle.1;User ID=%s;Password=%s;Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=%s)(PORT=%s))(CONNECT_DATA=(SERVICE_NAME=%s)));Persist Security Info=False"),\
	//	m_strUid,m_strPwd,m_strIp,m_strPort,m_strInstance);
		//_T("dms"),_T("dms"),_T("10.142.49.234"),_T("1521"),_T("orcl"));
	//m_strConnection = _T("Provider=OraOLEDB.Oracle.1;User ID=dms3;Password=dms3;Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=10.142.49.183)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=uds.yirong.com)));Persist Security Info=False");
}



BOOL CDataOperate::ExecSql(CString strSql)
{

	if (m_pCurDbMgr && m_pCurDbMgr->m_pDataBase)
	{
		if (!m_pCurDbMgr->m_pDataBase->IsOpen())
			m_pCurDbMgr->m_pDataBase->Open(m_pCurDbMgr->m_strConnection.c_str(),m_pCurDbMgr->m_strUid.c_str(),m_pCurDbMgr->m_strPwd.c_str());
		return 	m_pCurDbMgr->m_pDataBase->Execute(strSql);


	}
	return  FALSE ;
}

int CDataOperate::ExecSql(char* strSql)
{

	if (m_pCurDbMgr && m_pCurDbMgr->m_pDataBase)
	{
		if (!m_pCurDbMgr->m_pDataBase->IsOpen())
			m_pCurDbMgr->m_pDataBase->Open(m_pCurDbMgr->m_strConnection.c_str(),m_pCurDbMgr->m_strUid.c_str(),m_pCurDbMgr->m_strPwd.c_str());
		return 	m_pCurDbMgr->m_pDataBase->Execute(strSql);


	}
	return  FALSE ;
}

CDataTable* CDataOperate::GetDtTable(wchar_t* strSql)
{
	if(m_pCurDbMgr)
	{
		CDataTable* pTable=new CDataTable;
		//memset(pTable,0,sizeof(CDataTable));
		int nRes = m_pCurDbMgr->m_pDataBase->Open(m_pCurDbMgr->m_strConnection.c_str(),m_pCurDbMgr->m_strUid.c_str(),m_pCurDbMgr->m_strPwd.c_str());
		//int nRes = m_pCurDbMgr->m_pDataBase->Open(L"Provider=OraOLEDB.Oracle.1;User ID=dms3;Password=dms3;Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=10.142.49.183)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=uds.yirong.com)));Persist Security Info=False",m_strUid,m_strPwd);
 		if (m_pCurDbMgr->m_pRes->Open(strSql,IRecoredset::openQuery,pTable))
 		{
 			pTable = m_pCurDbMgr->m_pRes->GetDt(pTable);
 		}
		
		return pTable;
	}
	return NULL;
}



CDataTable* CDataOperate::GetDtTable(char* strSql)
{
	if(m_pCurDbMgr)
	{
		CDataTable* pTable=new CDataTable;
		//memset(pTable,0,sizeof(CDataTable));
		int nRes = m_pCurDbMgr->m_pDataBase->Open(m_pCurDbMgr->m_strConnection.c_str(),m_pCurDbMgr->m_strUid.c_str(),m_pCurDbMgr->m_strPwd.c_str());
		//int nRes = m_pCurDbMgr->m_pDataBase->Open(L"Provider=OraOLEDB.Oracle.1;User ID=dms3;Password=dms3;Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=10.142.49.183)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=uds.yirong.com)));Persist Security Info=False",m_strUid,m_strPwd);
		if (m_pCurDbMgr->m_pRes->Open(strSql,IRecoredset::openQuery,pTable))
		{
			pTable = m_pCurDbMgr->m_pRes->GetDt(pTable);
		}

		return pTable;
	}
	return NULL;
}


CDataOperate::~CDataOperate(void)
{
	//::CoUninitialize();
	map<wstring,CDataBaseMgr*>::iterator Iter;
	for (Iter = m_DbArr.begin();Iter != m_DbArr.end();++Iter)
	{
		delete Iter->second;
	}
	m_DbArr.clear();
	
}

CDataTable* CDataOperate::GetAllDataBase(wchar_t* strSql)
{
	//return NULL;
	CString szStrSql;
	szStrSql.Format(_T("%s"),strSql);
	return GetDtTable(szStrSql.GetBuffer(0));

}

CDataTable* CDataOperate::GetAllDataBase(char* strSql)
{
	//return NULL;
// 	CString szStrSql;
// 	szStrSql.Format(_T("%s"),strSql);
	return GetDtTable(strSql);

}


void CDataOperate::AdddDbMgr(wstring strDatabase)
{
	CDataBaseMgr* pDbMgr = new CDataBaseMgr;
	m_DbArr.insert(pair<wstring,CDataBaseMgr*>(strDatabase,pDbMgr));
	m_pCurDbMgr = pDbMgr;
}

BOOL CDataOperate::ChangeDbMgr(wstring strDatabase)
{
	map<wstring,CDataBaseMgr*>::iterator Iter;
	Iter = m_DbArr.find(strDatabase);
	if (Iter != m_DbArr.end())
	{
		//ÕÒµ½
		m_pCurDbMgr = m_DbArr[strDatabase];
		return TRUE;
	}
	return FALSE;
}

void CDataOperate::SetDBType(int nDbType)
{
	if (m_pCurDbMgr)
	{
		m_pCurDbMgr->m_nDbType = nDbType;
	}
}

void CDataOperate::SetUserId(wstring strUid)
{
	if (m_pCurDbMgr)
	{
		m_pCurDbMgr->m_strUid = strUid;
	}
}

void CDataOperate::SetUserPwd(wstring strPwd)
{
	if (m_pCurDbMgr)
	{
		m_pCurDbMgr->m_strPwd = strPwd;
	}
}

void CDataOperate::SetIp(wstring strIp)
{
	if (m_pCurDbMgr)
	{
		m_pCurDbMgr->m_strIp = strIp;
	}
}

void CDataOperate::SetPort(wstring strPort)
{
	if (m_pCurDbMgr)
	{
		m_pCurDbMgr->m_strPort = strPort;
	}
}

void CDataOperate::SetInstance(wstring strInstance)
{
	if (m_pCurDbMgr)
	{
		m_pCurDbMgr->m_strInstance = strInstance;
	}
}




void CDataOperate::CDataBaseMgr::InitConnstring(int nType)
{
	if (m_pDataBase)
	{
		delete m_pDataBase;
		m_pDataBase = NULL;
	}

	if (m_pRes)
	{
		delete m_pRes;
		m_pRes = NULL;
	}

	CString strConn;
	switch (nType)
	{
	case ORACLE:
		strConn.Format(_T("Provider=OraOLEDB.Oracle.1;User ID=%s;Password=%s;Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=%s)(PORT=%s))(CONNECT_DATA=(SERVICE_NAME=%s)));Persist Security Info=False"),\
			m_strUid.c_str(),m_strPwd.c_str(),m_strIp.c_str(),m_strPort.c_str(),m_strInstance.c_str());
		m_strConnection = strConn.GetBuffer();
		m_pDataBase = new CADODatabase;
		m_pRes = new CADORecordset((CADODatabase*)m_pDataBase);
		break;
	case SQLITE:
		strConn = m_strInstance.c_str();
		m_strConnection = strConn.GetBuffer();
		m_pDataBase = new CSqlite;
		m_pRes = new CSqliteRecordset((CSqlite*)m_pDataBase);
		break;
	}
}

CDataOperate::CDataBaseMgr::~CDataBaseMgr()
{
	if(m_pDataBase)
	{
		delete m_pDataBase;
		m_pDataBase = NULL;
	}

	if (m_pRes)
	{
		delete m_pRes;
		m_pRes = NULL;
	}
}