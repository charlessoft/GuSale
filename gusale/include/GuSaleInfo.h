#ifndef _CGUSALEINFO_H_
#define _CGUSALEINFO_H_
#include "typedefine.h" 
#include "IParseJson.h"
#define INTAKE  1
#define OFFTAKE -1
class CGuSaleData;
class CGuSaleList;
class CGuSaleInfo : public CGobj , public IParseJson
{
public:
	typedef void ( CGuSaleInfo::*FuncT )( string key, CGuSaleInfo* pGuSaleInfo, void* value );
	
	typedef map<string, FuncT>GuSaleInfoMap;

	CGuSaleInfo();

	virtual ~CGuSaleInfo();

	//IParseJson

	virtual void DealJsonNode( string strNode, string value );

	virtual IParseJson* CreateJsonItem( string strKey );
	//

	//virtual BOOL ParseJson( CGobj* pRoot, const char* json );

	virtual BOOL Rebuild( CGobj* pRoot );

	map<string, FuncT> mapfunc;

	void SetCode( string key, CGuSaleInfo* pGuSale, void* obj );

	void SetMsg( string key, CGuSaleInfo* pGuSale, void* obj );

	void SetData( string key, CGuSaleInfo* pGuSale, void* obj );

	void SetList( string key, CGuSaleInfo* pGuSale, void* obj );

	//获取股票买卖数据 taade_type =0/-1, offset偏移, view_cnt 一次显示个数
	void GetSaleInfo( int trade_type, int offset, int view_cnt );

	CGuSaleData* m_pGuSaleData;

	string m_code;
	
	string m_msg;
};



#endif
