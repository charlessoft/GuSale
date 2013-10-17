#include "../include/GuSaleList.h"
#include "../include/StdString.h"

CGuSaleList::CGuSaleList()
{
	mapfunc["id"] = &CGuSaleList::SetId;
	mapfunc["expert_id"] = &CGuSaleList::SetExpert_id;
	mapfunc["operate"] = &CGuSaleList::SetOperate;
	mapfunc["stock"] = &CGuSaleList::SetStock;
	mapfunc["price"] = &CGuSaleList::SetPrice;
	mapfunc["shares"] = &CGuSaleList::SetShares;
	mapfunc["operate_time"] = &CGuSaleList::SetOperate_time;
	mapfunc["created_at"] = &CGuSaleList::SetCreated_at;
	mapfunc["updated_at"] = &CGuSaleList::SetUpdated_at;
	mapfunc["user_name"] = &CGuSaleList::SetUser_name;
	mapfunc["uid"] = &CGuSaleList::SetUid;
	mapfunc["avatar"] = &CGuSaleList::SetAvatar;
	mapfunc["stock_name"] = &CGuSaleList::SetStock_name;


	mapfunc["user_id"] = &CGuSaleList::SetUser_id;
	mapfunc["count"] = &CGuSaleList::SetCount;
	mapfunc["buy_price"] = &CGuSaleList::SetBuy_price;
	mapfunc["sell_time"] = &CGuSaleList::SetSell_time;
	mapfunc["trans_earn"] = &CGuSaleList::SetTrans_earn;
	mapfunc["rate"] = &CGuSaleList::SetRate;
	mapfunc["time_type"] = &CGuSaleList::SetTime_type;
	mapfunc["opp_id"] = &CGuSaleList::SetOpp_id;
	mapfunc["sell_price"] = &CGuSaleList::SetSell_price;

}

CGuSaleList::~CGuSaleList()
{
	

}

void CGuSaleList::SetId( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_id = (char*)obj;
	}
}

void CGuSaleList::SetExpert_id( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_expert_id = (char*)obj;
	}
}

void CGuSaleList::SetOperate( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_operate = (char*)obj;
	}
}

void CGuSaleList::SetStock( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_stock = (char*)obj;
	}
}

void CGuSaleList::SetShares( string key, CGobj* pGuSale, void* obj)
{
	if ( obj )
	{
		this->m_shares = (char*)obj;
	}
}

void CGuSaleList::SetPrice( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_price = (char*)obj;
	}
}

void CGuSaleList::SetOperate_time( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_operate_time = (char*)obj;
	}
}

void CGuSaleList::SetCreated_at( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_created_at = (char*)obj;
	}
}

void CGuSaleList::SetUpdated_at( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_updated_at = (char*)obj;
	}
}

void CGuSaleList::SetUser_name( string key, CGobj* pGuSale, void* obj )
{
// 	string strUserName = (char*)obj;
// 	this->m_user_name = UTF8ToUnicode( strUserName );
	if ( obj )
	{
		this->m_user_name = (char*)obj;
	}
}

void CGuSaleList::SetUid( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_uid = (char*)obj;
	}
}

void CGuSaleList::SetAvatar( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_avatar = (char*)obj;
	}
}

void CGuSaleList::SetStock_name( string key, CGobj* pGuSale, void* obj )
{
// 	string stock_name = (char*)obj;
// 	this->m_stock_name = UTF8ToUnicode( stock_name );
	if ( obj )
	{
		this->m_stock_name = (char*)obj;
	}
}

void CGuSaleList::SetUser_id( string key, CGobj* pGuSale, void* obj)
{
	if ( obj )
	{
		this->m_user_id = (char*)obj;
	}
	
}

void CGuSaleList::SetCount( string key, CGobj* pGuSale, void* obj)
{
	if ( obj )
	{
		this->m_count = (char*)obj;
	}
	
}

void CGuSaleList::SetBuy_price( string key, CGobj* pGuSale, void* obj)
{
	if ( obj )
	{
		this->m_buy_price = (char*)obj;
	}
}

void CGuSaleList::SetSell_time( string key, CGobj* pGuSale, void* obj)
{
	if ( obj )
	{
		this->m_sell_time = (char*)obj;
	}
}

void CGuSaleList::SetTrans_earn( string key, CGobj* pGuSale, void* obj)
{
	if ( obj )
	{
		this->m_trans_earn = (char*)obj;
	}
	
}

void CGuSaleList::SetRate( string key, CGobj* pGuSale, void* obj)
{
	this->m_rate = (char*)obj;
}

void CGuSaleList::SetTime_type( string key, CGobj* pGuSale, void* obj)
{
	if ( obj )
	{
		this->m_time_type = (char*)obj;
	}
	
	
}

void CGuSaleList::SetOpp_id( string key, CGobj* pGuSale, void* obj)
{
	this->m_opp_id = (char*)obj;
}

void CGuSaleList::SetSell_price( string key, CGobj* pGuSale, void* obj)
{
	if ( obj )
	{
		this->m_sell_price = (char*)obj;
	}
}

void CGuSaleList::SetBuy_time( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_buy_time = (char*)obj;
	}
}



void CGuSaleList::DealJsonNode( string strNode, string value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value.c_str() );
	}
}

void CGuSaleList::DealJsonNode( string strNode, int value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSaleList::DealJsonNode( string strNode, unsigned int value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSaleList::DealJsonNode( string strNode, double value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)&value );
	}
}

IParseJson* CGuSaleList::CreateJsonItem( string strKey )
{

	return NULL;
}