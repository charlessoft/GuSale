#ifndef _SQLITE_H_
#define _SQLITE_H_
#include "ISQLHelper.h"
#include "sqlite3.h"


class CDataTable;
class CSqliteRecordset;
class CSqlite : public IDatabase
{
public:
	CSqlite();
	~CSqlite();
	virtual BOOL Open(LPCTSTR lpstrConnection/* = _T("")*/, LPCTSTR lpstrUserID /*= _T("")*/, LPCTSTR lpstrPassword /*= _T("")*/);
	
	virtual int  Open(LPCTSTR sqlData);

	virtual int Execute(LPCTSTR lpstrExec);

	virtual int Execute(LPCSTR lpstrExec);

	virtual BOOL IsOpen();

	virtual void Close();

	static int _sql_callback(void * notused, int argc, char ** argv, char ** szColName);
	char * pErrMsg;
	string m_strConnect;
private:
	sqlite3 * m_pdb;
	static CDataTable* m_pDatatable;
	friend class CSqliteRecordset;
	

};

class CSqliteRecordset : public IRecoredset
{
public:
	CSqliteRecordset(CSqlite* sqlite){m_pdata = sqlite;}
	virtual CDataTable* GetDt(CDataTable* dt);

	virtual BOOL Open(LPCTSTR lpstrExec = _T(""), int nOption = IRecoredset::openUnknown,CDataTable* pDt = NULL);

	virtual BOOL Open( LPCSTR lpstrExec = "", int nOption = IRecoredset::openUnknown, CDataTable* pDt = NULL );

private:
	CSqlite* m_pdata;
};
#endif