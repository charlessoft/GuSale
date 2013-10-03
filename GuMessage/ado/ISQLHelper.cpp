#include "ISQLHelper.h"
#include "../stdafx.h"
#include "../StdString.h"


CDataRow* CDataTable::NewRow(BOOL bCopyColumn/*=TRUE*/)
{
	CDataRow* pRow = new CDataRow();
	if (bCopyColumn)
	{
		pRow->m_nColCount = this->Columns.size();
		for (int i=0;i<pRow->m_nColCount;i++)
		{
			CDataColumn* pColumn = new CDataColumn();
			_tcscpy_s(pColumn->m_ColumnName,32,((CDataColumn*)this->Columns[i])->m_ColumnName);
			pRow->m_ColMap.insert(pair<wstring, int>(pColumn->m_ColumnName, i));
			pRow->m_pColumns.push_back(pColumn);
		}
	}
	

	return pRow;
}


CDataColumn* CDataRow::GetColumn(int ColIndex)
{
	return this->m_pColumns[ColIndex];
}

CDataColumn* CDataRow::GetColumn(char* ColName)
{
	wstring szColName(s2ws(ColName));
	return GetColumn(szColName);

}

CDataColumn* CDataRow::GetColumn(wstring ColName)
{
	map<wstring,int>::iterator iter;
	iter = this->m_ColMap.find(ColName);
	if (iter != m_ColMap.end())
	{
		int nColIndex = this->m_ColMap[ColName];
		return this->m_pColumns[nColIndex];
	}
	return NULL;

}

void CDataRow::AddColumn(CDataColumn* pColumn)
{
	map<wstring,int>::iterator Iter;
	Iter = m_ColMap.find(pColumn->m_ColumnName);
	if(Iter != m_ColMap.end())
	{
		//已经存在
		return;
	}
	m_ColMap.insert(pair<wstring,int>(pColumn->m_ColumnName,m_ColMap.size()));
	m_pColumns.push_back(pColumn);
}

void CDataRow::DeleteRow()
{
	delete this;
}


CDataRow::~CDataRow()
{
	for (size_t i=0,sz=m_pColumns.size();i<sz;i++)
	{
		CDataColumn* pCol = (CDataColumn*)m_pColumns[i];
		if (pCol)
		{
			delete pCol;
			pCol = NULL;
		}
	}
}


void CDataTable::SetDs(IRecoredset* ds)
{
	this->m_recordset= ds;
}

void CDataTable::copy(CDataTable* pDt) //复制数据
{

}

void CDataTable::clone(CDataTable* pDt) //复制表结构
{

	for (int i=0,sz=Columns.size();i<sz;i++)
	{
		map<wstring,int>::iterator Iter;
		Iter = m_ColMap.find(Columns[i]->m_ColumnName);
		if(Iter != m_ColMap.end())
		{
			//已经存在
			return;
		}
		CDataColumn* pColumn = new CDataColumn();
		_tcscpy_s(pColumn->m_ColumnName,32,Columns[i]->m_ColumnName);
		m_ColMap.insert(pair<wstring,int>(pColumn->m_ColumnName,m_ColMap.size()));

		pDt->Columns.push_back(pColumn);
	}
}

CDataTable::CDataTable()
{
	Columns.clear();
	m_ColMap.clear();
	m_recordset = NULL;

}

CDataTable::~CDataTable()
{
	for (size_t i=0,sz=Rows.size();i<sz;i++)
	{
		CDataRow* pRow = (CDataRow*)Rows[i];
		if (pRow)
		{
			delete pRow;
			pRow = NULL;
		}
	}

	for (size_t i=0,sz=Columns.size();i<sz;i++)
	{
		CDataColumn* pCol = (CDataColumn*)Columns[i];
		if (pCol)
		{
			delete pCol;
			pCol = NULL;
		}
	}
}

CDataColumn::CDataColumn(const CDataColumn& C)
{
	//m_bShow=TRUE;
	m_bShow = C.m_bShow;
	_tcscpy_s(m_ColumnName,32,C.m_ColumnName);
}

void CDataColumn::GetValue(CString& strValue)
{
	if(value.vt==VT_I4||value.vt==VT_DECIMAL)
	{
		//CString strTrans;
		strValue.Format(_T("%ld"),value.intVal);
		//Result.Add(strTrans);
	}
	else if(value.vt==VT_R4)
	{
		CString strTrans;
		strValue.Format(_T("%.2f"),value.fltVal);
		if (strValue.Right(1) == "0")
			strValue = strValue.Left(strValue.GetLength()-1);
		//Result.Add(strTrans);
	}
	else if(value.vt==VT_R8)
	{
		strValue.Format(_T("%.1lf"),value.dblVal);
	}
	else
	{
		if (value.vt!=VT_NULL)
		{
#ifdef _UNICODE
			//char* cstr = _com_util::ConvertBSTRToString(value.bstrVal);
			if (value.vt==VT_EMPTY)
			{
				strValue.Format(_T("%s"),_T(""));
			}
			else if(value.vt==VT_DATE)
			{
				DATE dt = value.date;
				COleDateTime odt = COleDateTime(dt);
				CString str;
				strValue = odt.Format(_T("%Y-%m-%d %H:%M:%S"));
			}
			else
				strValue.Format(_T("%s"),value.bstrVal);
			//delete cstr;
#else
			char* cstr = _com_util::ConvertBSTRToString(value.bstrVal);
			strValue.Format(_T("%s"),cstr);
			delete cstr;
#endif			
		}
	}

}