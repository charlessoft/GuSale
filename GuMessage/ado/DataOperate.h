#pragma once
#include "ado2.h"
#include "ISQLHelper.h"
#include "sqlite.h"
class CDataOperate
{
public:
	enum DATABASE_TYPE
	{
		ORACLE =0,
		SQLITE,
	};

	class CDataBaseMgr
	{
	public:
		wstring m_strUid;
		wstring m_strPwd;
		wstring m_strIp;
		wstring m_strInstance;
		wstring m_strPort;
		wstring m_strConnection;
		int m_nDbType;
		IDatabase* m_pDataBase;
		IRecoredset* m_pRes;
		void InitConnstring(int nType);
		friend class CDataOperate;
		~CDataBaseMgr();
		CDataBaseMgr()
		{
			m_strUid = L"";
			m_strPwd = L"";
			m_strIp = L"";
			m_strInstance = L"";
			m_strPort = L"";
			m_strConnection = L"";
			m_nDbType = 0;
			m_pDataBase = NULL;
			m_pRes = NULL;
		}

	};
public:
	//static CDataOperate &GetInstance();
	 static CDataOperate  &GetInstance()
	 {
		 static CDataOperate instance;
		 return instance;
	 }
	CDataTable* GetAllDataBase( wchar_t* strSql );

	CDataTable* GetAllDataBase( char* strSql );

	CDataTable* GetDtTable( char* strSql );

	CDataTable* GetDtTable( wchar_t* strSql );

	void InitConnstring();

	BOOL ExecSql(CString strSql);
	
	int ExecSql(char* strSql);

private:
	static CDataOperate * m_pInstance;
	CDataOperate(void);
//	CDataOperate(const CDataOperate&);
//	CDataOperate & operate = (const CDataOperate&);

public:
	~CDataOperate(void);

// 	CADORecordset m_pRs;
// 	CADODatabase m_pDb;
	CString m_strConnection;
		//_T("dms"),_T("dms"),_T("10.142.49.234"),_T("1521"),_T("orcl"));
// 	CString m_strUid;
// 	CString m_strPwd;
// 	CString m_strIp;
// 	CString m_strPort;
// 	CString m_strInstance;
// 	int		m_nLimit;//最多查询的条数
	
// 	IDatabase* m_pDatabase;
// 	IRecoredset* m_pRes;

private:
	map<wstring,CDataBaseMgr*> m_DbArr; //保存多个数据库信息,例如同时操作oracle,sqlite
	CDataBaseMgr* m_pCurDbMgr;
public:
	void AdddDbMgr(wstring strDatabase);
	BOOL ChangeDbMgr(wstring strDatabase);

	void SetDBType(int nDbType);
	void SetUserId(wstring strUid);
	void SetUserPwd(wstring strPwd);
	void SetIp(wstring strIp);
	void SetPort(wstring strPort);
	void SetInstance(wstring strInstance);
	
private:
// 	class CGarbo // 它的唯一工作就是在析构函数中删除CSingleton的实例  
// 	{  
// 	public:  
// 		~CGarbo()  
// 		{  
// 		if (CDataOperate::m_pInstance)  
// 		delete CDataOperate::m_pInstance;  
// 		}  
// 	};   
// 	static CGarbo Garbo; // 定义一个静态成员，在程序结束时，系统会调用它的析构函数  
};

#define g_DbOperate CDataOperate::GetInstance()
#define g_pDbOpeate &CDataOperate::GetInstance()