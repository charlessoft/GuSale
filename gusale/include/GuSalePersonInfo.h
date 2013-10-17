#ifndef _CGUSALEPERSONINFO_H_
#define _CGUSALEPERSONINFO_H_
#include "typedefine.h" 
#include "IParseJson.h"

class CGuSalePersonInfo_Content;
class CGuSalePersonInfo_Data;

class CGuSalePersonInfo_Data : public CGobj , public IParseJson
{
public:
	typedef void ( CGuSalePersonInfo_Data::*FuncT )( string key, CGobj* pGuSaleInfo, void* value );

	typedef map<string, FuncT>GuSaleListMap;

	CGuSalePersonInfo_Data();

	virtual ~CGuSalePersonInfo_Data();

	map<string, FuncT> mapfunc;

	string m_uid;
	string m_feed_id;
	string m_feed_menu;
	string m_feed_type;
	string m_related_id;
	string m_user_name;
	string m_avatar;
	string m_expert_id;
	string m_stockid;
	string m_title;
	string m_site;
	string m_org_id;
	string m_comment_cnt;
	string m_pub_date;
	string m_create_date;
	string m_user_stock;

	void SetUid( string key, CGobj* pGuSale, void* obj );

	void SetFeed_id( string key, CGobj* pGuSale, void* obj );

	void SetFeed_menu( string key, CGobj* pGuSale, void* obj );

	void SetFeed_type( string key, CGobj* pGuSale, void* obj );

	void SetRelated_id( string key, CGobj* pGuSale, void* obj );

	void SetUser_name( string key, CGobj* pGuSale, void* obj );

	void SetAvatar( string key, CGobj* pGuSale, void* obj );

	void SetExpert_id( string key, CGobj* pGuSale, void* obj );

	void SetStockid( string key, CGobj* pGuSale, void* obj );

	void SetTitle( string key, CGobj* pGuSale, void* obj );

	void SetSite( string key, CGobj* pGuSale, void* obj );

	void SetOrg_id( string key, CGobj* pGuSale, void* obj );

	void SetComment_cnt( string key, CGobj* pGuSale, void* obj );

	void SetPub_date( string key, CGobj* pGuSale, void* obj );

	void SetCreate_date( string key, CGobj* pGuSale, void* obj );

	void SetUser_stock( string key, CGobj* pGuSale, void* obj );

	virtual void DealJsonNode( string strNode, string value );

	virtual void DealJsonNode( string strNode, int value );

	virtual void DealJsonNode( string strNode, unsigned int value );

	virtual void DealJsonNode( string strNode, double value );

	virtual IParseJson* CreateJsonItem( string strKey );

	//vector<CGuSalePersonInfo_Content*> m_ContentArr;
	CGuSalePersonInfo_Content* m_pGuSalePersonInfo_Content;
};

class CGuSalePersonInfo_Content : public CGobj , public IParseJson
{
public:
	typedef void ( CGuSalePersonInfo_Content::*FuncT )( string key, CGobj* pGuSaleInfo, void* value );

	typedef map<string, FuncT>GuSaleListMap;

	CGuSalePersonInfo_Content();

	virtual ~CGuSalePersonInfo_Content();

	map<string, FuncT> mapfunc;

	void SetStockid( string key, CGobj* pGuSale, void* obj );
	
	void SetStock_name( string key, CGobj* pGuSale, void* obj );
	
	void SetOperate( string key, CGobj* pGuSale, void* obj );

	void SetShares( string key, CGobj* pGuSale, void* obj );
	
	void SetPrice( string key, CGobj* pGuSale, void* obj );


	virtual void DealJsonNode( string strNode, string value );

	virtual void DealJsonNode( string strNode, int value );

	virtual void DealJsonNode( string strNode, unsigned int value );

	virtual void DealJsonNode( string strNode, double value );

	virtual IParseJson* CreateJsonItem( string strKey );

	string m_stockid;
	
	string m_stock_name;
	
	string m_shares;
	
	string m_price;
	
	string m_operate;
};

class CGuSalePersonInfo : public CGobj , public IParseJson
{
public:
	typedef void ( CGuSalePersonInfo::*FuncT )( string key, CGobj* pGuSaleInfo, void* value );

	typedef map<string, FuncT>GuSaleListMap;

	CGuSalePersonInfo();

	virtual ~CGuSalePersonInfo();

	map<string, FuncT> mapfunc;
	
	string m_code;

	string m_msg;

	void SetCode( string key, CGobj* pGuSale, void* obj );

	void SetMsg( string key, CGobj* pGuSale, void* obj );


	virtual void DealJsonNode( string strNode, string value );

	virtual void DealJsonNode( string strNode, int value );

	virtual void DealJsonNode( string strNode, unsigned int value );

	virtual void DealJsonNode( string strNode, double value );

	virtual IParseJson* CreateJsonItem( string strKey );

	//CGuSalePersonInfo_Data* m_pGuSalePersonInfo_Data;
	vector<CGuSalePersonInfo_Data*> m_GuSalePersonInfo_DataArr;

	void GetPersonInfo( string userid, int trade_type, int offset, int view_cnt );

};
#endif