#include "../include/GuSaleInfo.h"
#include "../include/CService.h"
CGuSaleInfo::CGuSaleInfo()
{
	m_pGuSaleData = NULL;

	mapfunc["code"]=&CGuSaleInfo::SetCode;
	mapfunc["msg"]=&CGuSaleInfo::SetMsg;
	mapfunc["data"]=&CGuSaleInfo::SetData;

}

CGuSaleInfo::~CGuSaleInfo()
{
	if ( m_pGuSaleData )
	{
		delete m_pGuSaleData;
		m_pGuSaleData = NULL;
	}
	

}

// BOOL CGuSaleInfo::ParseJson( CGobj* pRoot, const char* json )
// {
// 	return TRUE;
// }


BOOL CGuSaleInfo::Rebuild( CGobj* pRoot )
{

	return TRUE;
}


void CGuSaleInfo::SetCode( string key, CGuSaleInfo* pGuSale, void* obj )
{
	m_code = (char*)obj;
}

void CGuSaleInfo::SetMsg( string key, CGuSaleInfo* pGuSale, void* obj )
{
	m_msg = (char*)obj;
}

void CGuSaleInfo::SetData( string key, CGuSaleInfo* pGuSale, void* obj )
{
// 	if ( !m_pGuSaleData )
// 	{
// 		m_pGuSaleData = new CGuSaleData;
// 	}
	
}

void CGuSaleInfo::SetList( string key, CGuSaleInfo* pGuSale, void* obj )
{
	
}


void CGuSaleInfo::GetSaleInfo()
{
	string strurl = "http://www.gu360.com/performance/tradinglist";
	Service CService;
	string strPostData = "trade_type=1&offset=0&view_cnt=11";
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

	if ( buffer != "" )
	{
		this->ParseJson( this, buffer.c_str() );
	}
	
}

void CGuSaleInfo::DealJsonNode( string strNode, string value )
{
	GuSaleInfoMap::iterator Iter = mapfunc.find( strNode );
	if ( Iter != mapfunc.end() )
	{
		(this->*mapfunc[strNode])( strNode, this, (char*)value.c_str() );
	}
	
}

IParseJson* CGuSaleInfo::CreateJsonItem( string strKey )
{
	if ( strKey == "data" )
	{
		m_pGuSaleData = new CGuSaleData;
		return (IParseJson*)m_pGuSaleData;
	}
	
}