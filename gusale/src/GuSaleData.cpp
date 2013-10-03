#include "../include/GuSaleData.h"
#include "../include/GuSaleList.h"

CGuSaleData::CGuSaleData()
{
	mapfunc["cnt"] = &CGuSaleData::SetCnt;
	mapfunc["trade_type"]=&CGuSaleData::SetTrade_type;
	mapfunc["day"]=&CGuSaleData::SetDay;

}

CGuSaleData::~CGuSaleData()
{
	vector<CGuSaleList*>::iterator Iter;
	for ( Iter = this->m_GuSaleListArr.begin(); Iter != this->m_GuSaleListArr.end(); ++Iter )
	{
		delete *Iter;
	}
	this->m_GuSaleListArr.clear();
	
}

BOOL CGuSaleData::ParseJson( CGuSaleData* pRoot, const char* json )
{
	return FALSE;
}

BOOL CGuSaleData::Rebuild( CGuSaleData* pRoot )
{
	return FALSE;
}


void CGuSaleData::SetCnt( string key, CGuSaleData* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_Cnt = (int)obj;
	}
}

void CGuSaleData::SetTrade_type( string key, CGuSaleData* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_Trade_type = (char*)obj;
	}
}

void CGuSaleData::SetDay( string key, CGuSaleData* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_Day = (char*)obj;
	}
}

void CGuSaleData::DealJsonNode( string strNode, string value )
{
	GuSaleDataMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value.c_str() );
	}
}

void CGuSaleData::DealJsonNode( string strNode, int value )
{
	GuSaleDataMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSaleData::DealJsonNode( string strNode, unsigned int value )
{
	GuSaleDataMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSaleData::DealJsonNode( string strNode, double value )
{
	GuSaleDataMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)&value );
	}
}


IParseJson* CGuSaleData::CreateJsonItem( string strKey )
{
	if ( strKey == "list" )
	{
		CGuSaleList* pGuSaleList = new CGuSaleList;
		this->m_GuSaleListArr.push_back( pGuSaleList );
		return pGuSaleList;
	}
	return NULL;
}