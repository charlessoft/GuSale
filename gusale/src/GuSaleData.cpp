#include "../include/GuSaleData.h"

CGuSaleData::CGuSaleData()
{

}

CGuSaleData::~CGuSaleData()
{

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
	this->m_Cnt = (char*)obj;
}

void CGuSaleData::SetTrade_type( string key, CGuSaleData* pGuSale, void* obj )
{
	this->m_Trade_type = (char*)obj;
}

void CGuSaleData::SetDay( string key, CGuSaleData* pGuSale, void* obj )
{
	this->m_Day = (char*)obj;
}

void CGuSaleData::DealJsonNode( string strNode, string value )
{
	GuSaleDataMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value.c_str() );
	}
}

IParseJson* CGuSaleData::CreateJsonItem( string strKey )
{
	if ( strKey == "list" )
	{
		CGuSaleList* pGuSaleList = new CGuSaleList;
		this->m_GuSaleListArr.push_back( pGuSaleList );
		return (IParseJson*)pGuSaleList;
	}

}