#ifndef _CGUSALELIST_H_
#define _CGUSALELIST_H_
#include "typedefine.h" 
#include "IParseJson.h"

class CGuSaleList : public CGobj , public IParseJson
{
public:
	typedef void ( CGuSaleList::*FuncT )( string key, CGobj* pGuSaleInfo, void* value );
	
	typedef map<string, FuncT>GuSaleListMap;

	//CGuSaleList();

	virtual ~CGuSaleList();

	virtual BOOL ParseJson( CGobj* pRoot, const char* json );

	virtual BOOL Rebuild( CGobj* pRoot );

	map<string, FuncT> mapfunc;

	string m_id;
	string m_expert_id;
	string m_operate;
	string m_stock;
	string m_price;
	string m_operate_time;
	string m_created_at;
	string m_updated_at;
	string m_user_name;
	string m_uid;
	string m_avatar;
	string m_stock_name;

	void SetId( string key, CGobj* pGuSale, void* obj);

	void SetExpert_id( string key, CGobj* pGuSale, void* obj);

	void SetOperate( string key, CGobj* pGuSale, void* obj);

	void SetStock( string key, CGobj* pGuSale, void* obj);

	void SetPrice( string key, CGobj* pGuSale, void* obj);

	void SetOperate_time( string key, CGobj* pGuSale, void* obj);

	void SetCreated_at( string key, CGobj* pGuSale, void* obj);

	void SetUpdated_at( string key, CGobj* pGuSale, void* obj);

	void SetUser_name( string key, CGobj* pGuSale, void* obj);

	void SetUid( string key, CGobj* pGuSale, void* obj);

	void SetAvatar( string key, CGobj* pGuSale, void* obj);

	void SetStock_name( string key, CGobj* pGuSale, void* obj);

	//IParseJson
	virtual void DealJsonNode( string strNode, string value );

	virtual IParseJson* CreateJsonItem( string strKey );

};



#endif
