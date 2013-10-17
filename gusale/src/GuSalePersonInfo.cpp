#include "../include/GuSalePersonInfo.h"
#include "../include/StdString.h"
#include "../include/CService.h"
#include <iostream> 
#include <sstream> 
using namespace std;

CGuSalePersonInfo_Data::CGuSalePersonInfo_Data()
{
	mapfunc["uid"] = &CGuSalePersonInfo_Data::SetUid;
	mapfunc["feed_id"] = &CGuSalePersonInfo_Data::SetFeed_id;
	mapfunc["feed_menu"] = &CGuSalePersonInfo_Data::SetFeed_menu;
	mapfunc["feed_type"] = &CGuSalePersonInfo_Data::SetFeed_type;
	mapfunc["related_id"] = &CGuSalePersonInfo_Data::SetRelated_id;
	mapfunc["user_name"] = &CGuSalePersonInfo_Data::SetUser_name;
	mapfunc["avatar"] = &CGuSalePersonInfo_Data::SetAvatar;
	mapfunc["expert_id"] = &CGuSalePersonInfo_Data::SetExpert_id;
	mapfunc["stockid"] = &CGuSalePersonInfo_Data::SetStockid;
	mapfunc["title"] = &CGuSalePersonInfo_Data::SetTitle;
	mapfunc["site"] = &CGuSalePersonInfo_Data::SetSite;
	mapfunc["org_id"] = &CGuSalePersonInfo_Data::SetOrg_id;
	mapfunc["comment_cnt"] = &CGuSalePersonInfo_Data::SetComment_cnt;
	mapfunc["pub_date"] = &CGuSalePersonInfo_Data::SetPub_date;
	mapfunc["create_date"] = &CGuSalePersonInfo_Data::SetCreate_date;
	mapfunc["user_stock"] = &CGuSalePersonInfo_Data::SetUser_stock;
	m_pGuSalePersonInfo_Content = NULL;
}

CGuSalePersonInfo_Data::~CGuSalePersonInfo_Data()
{
	if ( m_pGuSalePersonInfo_Content )
	{
		delete m_pGuSalePersonInfo_Content;
		m_pGuSalePersonInfo_Content = NULL;
	}

}


void CGuSalePersonInfo_Data::DealJsonNode( string strNode, string value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value.c_str() );
	}
}

void CGuSalePersonInfo_Data::DealJsonNode( string strNode, int value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSalePersonInfo_Data::DealJsonNode( string strNode, unsigned int value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSalePersonInfo_Data::DealJsonNode( string strNode, double value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)&value );
	}
}

IParseJson* CGuSalePersonInfo_Data::CreateJsonItem( string strKey )
{

	return NULL;
}

void CGuSalePersonInfo_Data::SetUid( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_uid = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetFeed_id( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_feed_id = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetFeed_menu( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_feed_menu = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetFeed_type( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_feed_type = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetRelated_id( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_related_id = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetUser_name( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_user_name = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetAvatar( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_avatar = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetExpert_id( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_expert_id = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetStockid( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_stockid = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetTitle( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_title = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetSite( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_site = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetOrg_id( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_org_id = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetComment_cnt( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_comment_cnt = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetPub_date( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_pub_date = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetCreate_date( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_create_date = (char*)obj;
	}
}

void CGuSalePersonInfo_Data::SetUser_stock( string key, CGobj* pGuSale, void* obj )
{
	if( obj )
	{
		this->m_user_stock = (char*)obj;
	}
}

CGuSalePersonInfo_Content::CGuSalePersonInfo_Content()
{
	mapfunc["stockid"] = &CGuSalePersonInfo_Content::SetStockid;
	mapfunc["stock_name"] = &CGuSalePersonInfo_Content::SetStockid;
	mapfunc["operate"] = &CGuSalePersonInfo_Content::SetOperate;
	mapfunc["shares"] = &CGuSalePersonInfo_Content::SetShares;
	mapfunc["price"] = &CGuSalePersonInfo_Content::SetPrice;
}

CGuSalePersonInfo_Content::~CGuSalePersonInfo_Content()
{
	

}

void CGuSalePersonInfo_Content::SetOperate( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_operate = (char*)obj;
	}
}

void CGuSalePersonInfo_Content::SetStockid( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_stockid = (char*)obj;
	}
}

void CGuSalePersonInfo_Content::SetStock_name( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_stock_name = (char*)obj;
	}
}

void CGuSalePersonInfo_Content::SetShares( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_shares = (char*)obj;
	}
}

void CGuSalePersonInfo_Content::SetPrice( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_price = (char*)obj;
	}
}




void CGuSalePersonInfo_Content::DealJsonNode( string strNode, string value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value.c_str() );
	}
}

void CGuSalePersonInfo_Content::DealJsonNode( string strNode, int value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSalePersonInfo_Content::DealJsonNode( string strNode, unsigned int value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSalePersonInfo_Content::DealJsonNode( string strNode, double value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)&value );
	}
}

IParseJson* CGuSalePersonInfo_Content::CreateJsonItem( string strKey )
{

	return NULL;
}


CGuSalePersonInfo::CGuSalePersonInfo()
{
	
	mapfunc["code"] = &CGuSalePersonInfo::SetCode;
	mapfunc["msg"] = &CGuSalePersonInfo::SetMsg;
}

CGuSalePersonInfo::~CGuSalePersonInfo()
{
// 	if ( m_pGuSalePersonInfo_Data )
// 	{
// 		delete m_pGuSalePersonInfo_Data;
// 		m_pGuSalePersonInfo_Data = NULL;
// 	}
	 	vector<CGuSalePersonInfo_Data*>::iterator Iter;
	 	for( Iter != m_GuSalePersonInfo_DataArr.begin(); Iter != m_GuSalePersonInfo_DataArr.end(); ++Iter )
	 	{
	 		delete *Iter;
	 	}
	 	m_GuSalePersonInfo_DataArr.clear();
}

void CGuSalePersonInfo::SetCode( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_code = (char*)obj;
	}
}

void CGuSalePersonInfo::SetMsg( string key, CGobj* pGuSale, void* obj )
{
	if ( obj )
	{
		this->m_msg = (char*)obj;
	}

}

void CGuSalePersonInfo::DealJsonNode( string strNode, string value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value.c_str() );
	}
}

void CGuSalePersonInfo::DealJsonNode( string strNode, int value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSalePersonInfo::DealJsonNode( string strNode, unsigned int value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)value );
	}
}

void CGuSalePersonInfo::DealJsonNode( string strNode, double value )
{
	GuSaleListMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (void*)&value );
	}
}

IParseJson* CGuSalePersonInfo::CreateJsonItem( string strKey )
{
	if ( strKey == "data" )
	{
		CGuSalePersonInfo_Data* pGuSalePersonInfo_Data = new CGuSalePersonInfo_Data;
		m_GuSalePersonInfo_DataArr.push_back( pGuSalePersonInfo_Data );
		return pGuSalePersonInfo_Data;
	}
	return NULL;
}

void CGuSalePersonInfo::GetPersonInfo( string userid, int trade_type, int offset, int view_cnt )
{
 	stringstream strPostDataStream;
 	string strurl = "http://www.gu360.com/feeds/his/";
 	Service CService;
 	//string strPostData = "trade_type=1&offset=1&view_cnt=11";
 	strPostDataStream << "userid=" << userid.c_str() << "&trade_type=" << trade_type << "&offset=" << offset << "&view_cnt=" << view_cnt;
 
 	string strPostData = strPostDataStream.str();
 	vector<string> custom_header;
 	custom_header.push_back("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
 	custom_header.push_back("X-Requested-With: XMLHttpRequest");
 	custom_header.push_back("Referer: http://www.gu360.com/performance/trading");
 	PutData putdata;
 	putdata.data = (char*)strPostData.c_str();
 	putdata.datalen = strPostData.length();
 	CService.HttpRequest("POST",strurl,custom_header, &putdata,&CService);
 	string buffer = CService.m_resp_buffer;
 	string header = CService.m_resp_header;
// 	g_Logger.Debug( __FILE__, __LINE__, UTF8ToUnicode(strPostData).c_str() );
 
 	if ( buffer != "" )
 	{
 		this->ParseJson( this, buffer.c_str() );
 	}

}