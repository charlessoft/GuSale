#ifndef CLOUD_SERVICE_INTERFACE
#define CLOUD_SERVICE_INTERFACE
#include "../TypeDefine.h"
#include "../CService.h"
#include "../../src/tinyxml/tinyxml.h"

	
class CAuthenticator;
class CDataCredentials;
class IDataRequestFactory;
class IDataRequest;
class IAtomEntry
{
public:
	string m_respBuffer;
	string m_respHeader;
};

enum DataRequestType
{
	Type_Login,
	/// <summary>The request is used for query</summary>
	Type_Query,
	/// <summary>The request is used for an insert</summary>
	Type_Insert,
	/// <summary>The request is used for an update</summary>
	Type_Update,
	/// <summary>The request is used for a delete</summary>
	Type_Delete,
	/// <summary>This request is used for a batch operation</summary>
	Type_Batch
};


class IFeedQuery
{
public:
	IFeedQuery(){};
	IFeedQuery(string baseUri);
	int m_QueryType;
	/// <summary>baseUri property holder</summary> 
	string m_Query;
	/// <summary>category part as string, comma seperated</summary> 
	// QueryCategoryCollection categories;
	/// <summary>author part as string</summary> 
	string m_Author;
	/// <summary>extra parameters as string</summary> 
	string m_ExtraParameters;
	/// <summary>mininum date/time as time_t</summary> 
	time_t m_DateTimeMin;
	/// <summary>maximum date/time as time_t</summary> 
	time_t m_DateTimeMax;
	/// <summary>mininum date/time for the publicationdate as time_t</summary> 
	time_t m_PublishedMin;
	/// <summary>maximum date/time for the publicationdate as time_t</summary> 
	time_t m_PublishedMax;
	/// <summary>start-index as integer</summary> 
	int m_StartIndex;
	/// <summary>number of entries to retrieve as integer</summary> 
	int m_NumToRetrieve;
	/// <summary>alternative format as AlternativeFormat</summary> 
	//AlternativeFormat altFormat;

	//IMS（If-Modified-Since）标签
	//如果时间一致，那么返回HTTP状态码304（不返回文件内容），客户端接到之后，就直接把本地缓存文件显示到浏览器中。
	//如果时间不一致，就返回HTTP状态码200和新的文件内容，客户端接到之后，会丢弃旧文件，把新文件缓存起来，并显示到浏览器中。
	time_t m_IfModifiedSince;

	BOOL m_DefaultSSL;

	BOOL m_UseCategoryQueriesAsParameter;

	/// <summary>the oauth requestor id</summary>
	string m_OauthRequestorId;

	/// <summary>the base URI</summary> 
	string m_BaseUri;

	string m_Etag;

	virtual string CalculateQuery( string basePath );

	virtual char InsertionParameter( string basePath );

	char CreateCategoryString( string& builder, char connect );

private:
};

class IXmlAtom
{
public:
	IXmlAtom(){}
	/* 处理xml结点	*/
	virtual void DealXmlNode( string strNode, string strNodeAttribute, string Value) = 0;

	//创建字节点
	virtual IXmlAtom* CreateItem( string key ){ return NULL; }

	virtual void LoadXml(char* xmlPath);

	virtual void ParseXml(char* strXmlStream );

// 	typedef void (T::*HandlerPtr)( string strNode, string strNodeAttribute, string Value);
// 	map<string,HandlerPtr> m_HandlerPtrMap;
// 	
// 	void SetHandler( string strHandlerName,HandlerPtr pHander )
// 	{
// 		m_HandlerPtrMap[strHandlerName] = pHander;
// 	}

private:
	string DumpNode(TiXmlNode * pParent,TiXmlNode * pNode,IXmlAtom* pIAtom, int flag);
};

class IAtomFeed 
{
public:
	IAtomFeed(IAtomFeed * pAtomFeed) { m_url = m_url; m_strStream = pAtomFeed->m_strStream;} 
	IAtomFeed(){}
	
	virtual ~IAtomFeed(){}
	//vector<IAtomEntry*> m_feedEntries;
	
	static IAtomFeed* CreateFeed( string strStream, string uriToUse );

	//virtual void ParseXml(string strStreamInput);

	//virtual void ParseXml(){}
	
	void Release(){ delete this; }

	string m_url;
	string m_strStream;
};

class IService
{
public:
	IService()
	{
		m_pAuthenticator = NULL;
		m_pDataRequestFactory = NULL;
	}

	virtual ~IService();

	virtual void SetAuthenticator( CAuthenticator* pAuthenticator ){ m_pAuthenticator = pAuthenticator; }

	CAuthenticator* GetAuthenticator(){ return m_pAuthenticator; }

	virtual IAtomFeed* Query( IFeedQuery* pFeedQuery );

	void SetDataRequestFactory(	IDataRequestFactory* pDataRequestFactory ){ m_pDataRequestFactory = pDataRequestFactory; }

	virtual IAtomEntry* Insert( string strUriTarget, string inputStream, string strContentType, string strSlugHeader );

	virtual IAtomEntry* Insert( string strUriTarget, BYTE* inputStream, long nStreamLen, string strContentType, string strSlugHeader );

	virtual IAtomEntry* Insert( CAuthenticator* pAuthenticator, IAtomEntry* pDocEntry ){ return NULL; }
	
	int DownLoad( string strUri, FILEWRITE* pFileWriteStruct);

	int DownLoad( string strUri, GETPROCESS* pFileGetProcessStruct, FILEWRITE* pFileWriteStruct);

	BOOL DeleteFile( string strUri, string strETag );

protected:
	CAuthenticator* m_pAuthenticator;

	IDataRequestFactory* m_pDataRequestFactory;
private:
	//IAtomFeed* CreateAndParseFeed( string lpStream, string uriToUse );

	IAtomFeed* CreateFeed( string strStream, string uriToUse );

	virtual IDataRequest* Query( string queryUri, string eTag );

	virtual IDataRequest* Query( string queryUri, time_t ifModifySince );

	virtual IDataRequest* Query( string queryUri, time_t ifModifySince, string etag, long& contentLength );

};



//解析类
class IBaseFeedParse
{

};

class CRequestSettings
{
public:
	enum AuthenticationType
	{
		none,
		clientLogin,
		authSub,
		oAuth,
		oAuth2
	};
	CRequestSettings();
	CRequestSettings( string applicationName, CDataCredentials* pCredentials );
protected:
public:
	AuthenticationType m_authType;
	string m_applicationName;
	CDataCredentials* m_pCredentials;
	string m_authSubToken;
	int m_pageSize;// = -1;
	int m_max;// = -1;
	bool m_autoPage;
	int m_timeout;// = -1;
	string m_consumerKey;
	string m_consumerSecret;
	string m_oAuthUser;
	string m_oAuthDomain;
	string m_token;
	string tm_okenSecret;
	//AsymmetricAlgorithm privateKey;
	//Uri clientLoginHandler;
	BOOL m_useSSL;
	friend class CAuthenticator;
};


class CDataCredentials
{
public:
	CDataCredentials();
	CDataCredentials( string username, string password );
	CDataCredentials( string clientToken );
	string GetUserName(){ return m_userName; }
	string GetUserPwd(){ return m_passWord; }
protected:
private:
	string m_passWord;
	string m_userName;
	string m_clientToken;
	string m_captchaAnswer;
	string m_captchaToken;
	//string accountType = GoogleAuthentication.AccountTypeDefault;
	friend class CAuthenticator;
};


class CAuthenticator : public IFeedQuery
{
public:
	CAuthenticator();

	CAuthenticator( CRequestSettings* pRequestSetting );
	
	virtual void SetRequestSetting( CRequestSettings* pRequestSetting );

	CRequestSettings* GetRequestSetting(){ return m_pRequestSetting; }

	CRequestSettings* m_pRequestSetting;
	
	CDataCredentials* m_DataCredentials;

	string m_AuthToken;
private:
};



 


class IDataRequest
{
public:
	IDataRequest();
    
	virtual ~IDataRequest(){}

	virtual void Execute(){}

	virtual string GetResp_buffer() = 0;

	virtual string GetResp_header() = 0;

	virtual char* GetResponse(){ return NULL; }

	virtual BOOL SendRequest() = 0;

	virtual void EnsureWebRequest();

	virtual void EnsureCredentials();

	virtual void SetFileWrite( FILEWRITE* pFileWriteStruct ) = 0;

	virtual void SetDownLoadProcess( GETPROCESS* pGetProcessStruct ) = 0;
	
	virtual void SetUpLoadProcess( GETPROCESS* pGetProcessStruct ) = 0;

	virtual void SetPostData( string postData ) = 0;

	virtual void SetPostData( BYTE* lpPostData, long nPostDataLen ) = 0;

	virtual void SetPutData( BYTE* lpPutData, long nPutDataLen, long nCurPos, long nTotalDataLen ) = 0;

	virtual void SetAuthenticator( CAuthenticator* pAuthenticator ){ this->m_pAuthenticator = pAuthenticator; }
	
	virtual void ClearHeaders(){ m_headers.clear(); }


	DataRequestType m_DataRequestType;

	time_t	m_IfModifiedSince;

	BOOL m_useGZip;

	string m_SlugHeader;

	string m_ContentType;

	vector<string> m_headers;

	vector<string> m_CustomerHeaders;

	CAuthenticator* m_pAuthenticator;	

	string m_ETag;

	string m_IfMatch;

	string m_IfNoneMatch;// = "If-None-Match";

};

class CDataRequest : public IDataRequest
{
public:
	CDataRequest(){ m_nTotalLen = 0; m_nCurPos = 0;}

	virtual ~CDataRequest(){}
	
	virtual void SetFileWrite(FILEWRITE* pFileWriteStruct);

	virtual void SetDownLoadProcess( GETPROCESS* pGetProcessStruct );

	virtual void SetUpLoadProcess( GETPROCESS* pGetProcessStruct );

	virtual void SetPostData( string postData );

	virtual void SetPostData( BYTE* lpPostData, long nPostDataLen );
	
	virtual void SetPutData( BYTE* lpPutData, long nPutDataLen, long nCurPos, long nTotalDataLen );

	virtual void SetRedirectUrl( const char* redirectUri ){ m_uri = redirectUri; }

	virtual string GetResp_buffer();

	virtual string GetResp_header();

	virtual int SendRequest();

	virtual void SetHttpMethod( const char* httpMethod ){ m_httpMethod = httpMethod; }

	virtual void EnsureCredentials(){}

	string  m_uri;
	void Release(){ delete this; }
protected:
	Service m_curlMgr;

	
	
private:
	string m_PostData;
	string m_resp_buffer;
	string m_resp_header;
	string m_httpMethod;	
	long m_nTotalLen;// put Data时候可以使用,用来计算进度条,
	long m_nCurPos;//put Data时候计算进度条
};

class IDataRequestFactory
{
public:
    IDataRequestFactory();

    virtual ~IDataRequestFactory(){};
	
	virtual IDataRequest* CreateRequest( const char* uriTarget ) = 0;

	virtual IDataRequest* CreateRequest( DataRequestType type, const char* uriTarget ) = 0;

	virtual IDataRequest* CreateRequest( CAuthenticator* pAuthenticator, DataRequestType type, const char* uriTarget ) = 0;
	
	string m_SlugHeader;
};

#endif
