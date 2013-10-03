#ifndef _CGUSALELIST_H_
#define _CGUSALELIST_H_
#include "typedefine.h" 
#include "IParseJson.h"

class CGuSaleList : public CGobj , public IParseJson
{
public:
	typedef void ( CGuSaleList::*FuncT )( string key, CGobj* pGuSaleInfo, void* value );
	
	typedef map<string, FuncT>GuSaleListMap;

	CGuSaleList();

	virtual ~CGuSaleList();

// 	virtual BOOL ParseJson( CGobj* pRoot, const char* json );
// 
// 	virtual BOOL Rebuild( CGobj* pRoot );

	map<string, FuncT> mapfunc;

	string m_id;

	string m_expert_id;

	string m_operate;

	string m_stock; //股票代号

	string m_shares; 

	string m_price; //价格

	string m_operate_time; //用户在此时操作时间

	string m_created_at; //创建时间

	string m_updated_at; //更新时间

	string m_user_name; //用户名 

	string m_uid; //用户id

	string m_avatar; //头像

	string m_stock_name; //股票名字

	//卖出
	string m_user_id;
	
	int m_count; //卖出多少股票

	string m_buy_price; //买入价格

	string m_buy_time; //买入时间

	string m_sell_time; //卖出时间

	string m_trans_earn;

	string m_rate;

	string m_time_type;

	string m_opp_id;

	string m_sell_price;// 卖出价格

	void SetUser_id( string key, CGobj* pGuSale, void* obj);

	void SetCount( string key, CGobj* pGuSale, void* obj);

	void SetBuy_price( string key, CGobj* pGuSale, void* obj);

	void SetSell_time( string key, CGobj* pGuSale, void* obj);

	void SetTrans_earn( string key, CGobj* pGuSale, void* obj);

	void SetRate( string key, CGobj* pGuSale, void* obj);

	void SetTime_type( string key, CGobj* pGuSale, void* obj);

	void SetOpp_id( string key, CGobj* pGuSale, void* obj);

	void SetSell_price( string key, CGobj* pGuSale, void* obj);

	




	void SetId( string key, CGobj* pGuSale, void* obj);

	void SetExpert_id( string key, CGobj* pGuSale, void* obj);

	void SetOperate( string key, CGobj* pGuSale, void* obj);

	void SetStock( string key, CGobj* pGuSale, void* obj);

	void SetShares( string key, CGobj* pGuSale, void* obj);

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

	virtual void DealJsonNode( string strNode, int value );

	virtual void DealJsonNode( string strNode, unsigned int value );

	virtual void DealJsonNode( string strNode, double value );
	

	virtual IParseJson* CreateJsonItem( string strKey );

};



#endif
