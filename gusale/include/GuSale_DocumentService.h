#ifndef _GDOC_DOCUMENTSERVICE_H_
#define _GDOC_DOCUMENTSERVICE_H_
#include "cloud_serviceinterface.h"
#include "../TypeDefine.h"
class CGDoc_DocumentEntry;
class CGDoc_DocumentService : public IService
{
public:
	CGDoc_DocumentService();

	enum DocumentService_QueryType
	{
		QueryType_Login,
		QueryType_DocumentList,
	};

	virtual ~CGDoc_DocumentService();

	virtual IAtomFeed* Query( IFeedQuery* feedQuery );

	virtual IAtomFeed* QueryClientLoginToken( IFeedQuery* pFeedQuery );	

	virtual BOOL Login();

	static string m_DocumentsNamespace;

	static string m_Revisions;

	CGDoc_DocumentEntry* UploadDocument( string fileName, string documentName );

	CGDoc_DocumentEntry* UploadDocument( string fileName, string documentName, string contentType );

	CGDoc_DocumentEntry* UploadFile( string strFileName, string strDocumentName, string strContentType, BOOL bConvert );

	CGDoc_DocumentEntry* UploadDocument_ResumUploadFile( string strUriTarget,string fileName, string documentName, string contentType );

	CGDoc_DocumentEntry* UploadDocument_ResumUploadFile( string strUriTarget, string fileName, string documentName, string contentType, GETPROCESS* pFileGetProcessStruct );

	CGDoc_DocumentEntry* UploadDocument_ResumUploadFile( string strUriTarget, string fileName, string documentName, string contentType, GETPROCESS* pFileGetProcessStruct, FILEACCESS* pFileAccessStruct );

	//	CGDoc_DocumentEntry* UploadDocument_ResumUploadFile( string fileName, string documentName, DocumentType contentType );



	BOOL DownLoad( string uri, FILEWRITE* pFileWriteStruct );

	BOOL DownLoad( string uri, GETPROCESS* pFileGetProcessStruct, FILEWRITE* pFileWriteStruct );

	map<string,string> m_DocumentType;

	//int DeleteFile( string uri, string strETag );

	BOOL  IsLogin(){return m_bIsLogin;}

	string InitiateUpload( const char* resumableUploadUri, CAuthenticator* pAuthenticator, CGDoc_DocumentEntry* pDocEntry, string strUpload_Content_Type, long nUpload_Content_length, string strSlugHeader );


	virtual CGDoc_DocumentEntry* Insert_Folder( string strUriTarget, IAtomEntry* pDocEntry );

	static string s_DocumentsNamespace;
	static string s_Revisions;

protected:
private:
	BOOL m_bIsLogin;
	//    virtual IAtomFeed* QueryGet
};

#endif
