#ifndef _ISQLHELPER_H_
#define _ISQLHELPER_H_
#include <afx.h>
#include <afxdisp.h>
#include <math.h>

#include <string>
#include <vector>
#include <map>

#include <comdef.h>	 // Com define
#include <comutil.h>	 // Com 

using namespace std;
class CDataTable;
class ISqlHelper
{
public:
protected:
private:
};

class IDatabase
{
public:
	virtual BOOL Open(LPCTSTR lpstrConnection /*= _T("")*/, LPCTSTR lpstrUserID /*= _T("")*/, LPCTSTR lpstrPassword /*= _T("")*/) = 0;
	
	virtual int Open(LPCTSTR sqlData){return 1;}

	virtual int Execute(LPCTSTR lpstrExec) = 0;
	
	virtual int Execute(LPCSTR lpstrExec) = 0;

	virtual BOOL IsOpen() = 0;

	virtual void Close() = 0;

	virtual ~IDatabase(){}
protected:
private:
};

class IRecoredset
{
public:
	enum cadoOpenEnum
	{
		openUnknown = 0,
		openQuery = 1,
		openTable = 2,
		openStoredProc = 3
	};
	
	virtual BOOL Open( LPCTSTR lpstrExec = _T(""), int nOption = IRecoredset::openUnknown, CDataTable* pDt = NULL ) = 0;
	
	virtual BOOL Open( LPCSTR lpstrExec = "", int nOption = IRecoredset::openUnknown, CDataTable* pDt = NULL ) = 0;
	
	virtual CDataTable* GetDt(CDataTable* dt) = 0;
	
	virtual ~IRecoredset(){}
};




//获取列指针
#define GET_COLUMN(pTable,RowIndex,ColumnIndex) ((*pTable->Rows[RowIndex])[ColumnIndex])
class CDataColumn;
class CDataRow;
class CDataRow
{
public:
	enum
	{	STATUE_NORMAL = 0, 
		STATUE_DELETE
	};
	CDataRow(){m_status=STATUE_NORMAL;}
	~CDataRow();
	//	CDataRow();
	//CDataRow(int )
	vector<CDataColumn*> m_pColumns;

	size_t m_nColCount; //一行有几列
	int m_status;
	CDataColumn* GetColumn(int ColIndex);
	CDataColumn* GetColumn(char* ColName);
	CDataColumn* GetColumn(wstring ColName);

	CDataColumn* operator [](int nIndex)
	{
		return GetColumn(nIndex);
	}

	CDataColumn* operator [](char* colName)
	{
		return GetColumn(colName);
	}

	CDataColumn* operator [](wstring colName)
	{
		return GetColumn(colName);
	}

	//适用于 sqlite
	void AddColumn(CDataColumn* pColumn);
	
	void DeleteRow();

	
private:	
	map<wstring,int> m_ColMap;
	friend class CDataTable;
};

class CDataColumn
{
public:
	//	VARIANT m_type;
	CDataColumn(){m_bShow=TRUE;}
	CDataColumn(const CDataColumn& C);
	int m_nType;
	TCHAR m_ColumnName[32];
	_variant_t value;
	void GetValue(CString& value);
	BOOL m_bShow;


};

class CDataTable
{
public:
	CDataTable();
	vector<CDataRow*> Rows;
	//新行,是否复制列结构 bCopyColumn适合用于sqllite
	CDataRow* NewRow(BOOL bCopyColumn=TRUE);
	vector<CDataColumn*> Columns;
	map<wstring,int> m_ColMap;
	void SetDs(IRecoredset* ds);
	~CDataTable();
	void clone(CDataTable* pDt); //复制表结构
	void copy(CDataTable* pDt); //复制数据
	
private:
	IRecoredset* m_recordset;

};

#endif