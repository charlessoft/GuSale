#ifndef _COBJECT_H_
#define _COBJECT_H_
#include "typedefine.h" 
class CGobj
{
public:
//     CGobj* pPrevious;
// 
//     CGobj* pNext;
// 
//     char* m_json;
// 
//     CGobj()
//     {
//         pPrevious = NULL;
//         pNext = NULL;
//         m_json = NULL;
//     }
};

class IParseJson
{
public:
	IParseJson(){ m_bFirstCreateItem = FALSE; }

	virtual ~IParseJson(){}

	virtual BOOL ParseJson();

	virtual BOOL ParseJson( IParseJson* pRoot, const char* json );

	virtual BOOL ParseJson( const char* json );

	virtual void PrintValueTree( Json::Value &value, IParseJson* pParent, IParseJson* pObj, const std::string strkey, const std::string &path="" );

	virtual void Callbak( Json::Value &value, CGobj* pRoot, CGobj* pCurrent, CGobj* pChild, CGobj* pDocPrevious, const std::string strkey, const std::string &path );

	virtual void PrintValueTree( Json::Value &value, const std::string strkey, const std::string &path = "" );

	virtual void Callbak( Json::Value &value, const std::string strkey, const std::string &path );

	virtual void DealJsonNode( string strNode, string value );

	virtual void DealJsonNode( string strNode, int value );

	virtual void DealJsonNode( string strNode, unsigned int value );

	virtual void DealJsonNode( string strNode, double value );

	virtual IParseJson* CreateJsonItem( string strKey );
	
private:
	BOOL m_bFirstCreateItem;

};
#endif
