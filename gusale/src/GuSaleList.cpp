#include "../include/GuSaleList.h"

// CGuSaleList::CGuSaleList():CGobj(),IParseJson()
// {
// 
// }

CGuSaleList::~CGuSaleList()
{

}

void CGuSaleList::SetId( string key, CGobj* pGuSale, void* obj )
{
	this->m_id = (char*)obj;
}

void CGuSaleList::SetExpert_id( string key, CGobj* pGuSale, void* obj )
{
	this->m_expert_id = (char*)obj;
}

void CGuSaleList::SetOperate( string key, CGobj* pGuSale, void* obj )
{
	this->m_operate = (char*)obj;
}

void CGuSaleList::SetStock( string key, CGobj* pGuSale, void* obj )
{
	this->m_stock = (char*)obj;
}

void CGuSaleList::SetPrice( string key, CGobj* pGuSale, void* obj )
{
	this->m_price = (char*)obj;
}

void CGuSaleList::SetOperate_time( string key, CGobj* pGuSale, void* obj )
{
	this->m_operate_time = (char*)obj;
}

void CGuSaleList::SetCreated_at( string key, CGobj* pGuSale, void* obj )
{
	this->m_created_at = (char*)obj;
}

void CGuSaleList::SetUpdated_at( string key, CGobj* pGuSale, void* obj )
{
	this->m_updated_at = (char*)obj;
}

void CGuSaleList::SetUser_name( string key, CGobj* pGuSale, void* obj )
{
	this->m_user_name = (char*)obj;
}

void CGuSaleList::SetUid( string key, CGobj* pGuSale, void* obj )
{
	this->m_uid = (char*)obj;
}

void CGuSaleList::SetAvatar( string key, CGobj* pGuSale, void* obj )
{
	this->m_avatar = (char*)obj;
}

void CGuSaleList::SetStock_name( string key, CGobj* pGuSale, void* obj )
{
	this->m_stock_name = (char*)obj;
}


void CGuSaleList::DealJsonNode( string strNode, string value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value.c_str() );
	}
}

IParseJson* CGuSaleList::CreateJsonItem( string strKey )
{

	return NULL;
}