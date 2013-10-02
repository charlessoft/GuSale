#ifndef _CGUSALEDATA_H_
#define _CGUSALEDATA_H_
#include "typedefine.h" 
#include "IParseJson.h"
class CGuSaleList;

class CGuSaleList;
class CGuSaleData : public CGobj , public IParseJson
{
public:
	typedef void ( CGuSaleData::*FuncT )( string key, CGuSaleData* pGuSaleInfo, void* value );

	typedef map<string, FuncT>GuSaleDataMap;

	CGuSaleData();

	virtual ~CGuSaleData();

	virtual BOOL ParseJson( CGuSaleData* pRoot, const char* json );

	virtual BOOL Rebuild( CGuSaleData* pRoot );

	map<string, FuncT> mapfunc;



	virtual void SetCnt( string key, CGuSaleData* pGuSale, void* obj );

	virtual void SetTrade_type( string key, CGuSaleData* pGuSale, void* obj );

	virtual void SetDay( string key, CGuSaleData* pGuSale, void* obj );

	vector<CGuSaleList*> m_GuSaleListArr;

	string m_Cnt;
	
	string m_Trade_type;

	string m_Day;

	//IParseJson
	virtual void DealJsonNode( string strNode, string value );

	virtual IParseJson* CreateJsonItem( string strKey );
	
};



#endif
