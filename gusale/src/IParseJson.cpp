
#include "../include/IParseJson.h"
#include <algorithm> // sort
#include <stdio.h>
#include <stddef.h>
//#include "CGDocTree.h"

BOOL IParseJson::ParseJson()
{
	return FALSE;
}

void IParseJson::DealJsonNode( string strNode, string value )
{

}

IParseJson* IParseJson::CreateJsonItem( string strKey )
{
return NULL;
}

void IParseJson::Callbak( Json::Value &value,CGobj* pRoot,CGobj* pcurrent,CGobj* pchild,CGobj* pDocPrevious,const std::string strkey,const std::string &path )
{

}

void IParseJson::Callbak( Json::Value &value,const std::string strkey,const std::string &path )
{

}

void IParseJson::PrintValueTree( Json::Value &value,CGobj* pRoot,CGobj* pcurrent,CGobj* pchild,CGobj* pDocPrevious,const std::string strkey,const std::string &path /*= ""*/ )
{
    switch ( value.type() )
    {
        case Json::nullValue:
            {
                //(pcurrent->*mapfunc[path])("dd",pcurrent,(void*)value.asBool());
                Callbak(value,pRoot,pcurrent,pchild,pDocPrevious,strkey,path);

                break;
            }
        case Json::intValue:
            Callbak(value,pRoot,pcurrent,pchild,pDocPrevious,strkey,path);
            break;
        case Json::uintValue:
            break;
        case Json::realValue:
            break;
        case Json::stringValue:
            Callbak(value,pRoot,pcurrent,pchild,pDocPrevious,strkey,path);
            break;
        case Json::booleanValue:
            {
                Callbak(value,pRoot,pcurrent,pchild,pDocPrevious,strkey,path);
            }
            break;
        case Json::arrayValue:
            {
                int size = value.size();
                for ( int index =0; index < size; ++index )
                {
                    Callbak(value,pRoot,pcurrent,pchild,pDocPrevious,strkey,path);
                }
            }
            break;
        case Json::objectValue:
            {
                Json::Value::Members members( value.getMemberNames() );
                std::sort( members.begin(), members.end() );
                std::string suffix = "";//*(path.end()-1) == '.' ? "" : "";
                for ( Json::Value::Members::iterator it = members.begin(); 
                        it != members.end(); 
                        ++it )
                {
                    const std::string &name = *it;

                    PrintValueTree(/* fout,*/ value[name],pRoot,pcurrent,pchild,pDocPrevious,/*strtmp,*/ name,path + suffix + name );
                    Callbak(value,pRoot,pcurrent,pchild,pDocPrevious,strkey,path);
                }
            }
            break;
        default:
            break;
    }
}




BOOL IParseJson::ParseJson( CGobj* pRoot ,const char* json )
{


    Json::Features features;
    Json::Reader reader(features);
    Json::Value root;
    bool parsingSuccessful = reader.parse(json, root);
    if ( !parsingSuccessful )
    {
        return FALSE;
    }

    PrintValueTree(root,pRoot,pRoot,NULL,NULL,"");
    return TRUE;
}

BOOL IParseJson::ParseJson( const char* json )
{
    Json::Features features;
    Json::Reader reader( features );
    Json::Value root;
    bool parsingSuccessful = reader.parse( json, root );
    if ( !parsingSuccessful )
    {
        return FALSE;
    }
    PrintValueTree( root ,"","");
    return TRUE;

}

void IParseJson::PrintValueTree( Json::Value &value,const std::string strkey,const std::string &path /*= ""*/ )
{
    switch ( value.type() )
    {
        case Json::nullValue:
        case Json::intValue:	
        case Json::uintValue:
        case Json::realValue:
        case Json::stringValue:
        case Json::booleanValue:
            Callbak(value,strkey,path);
            break;
        case Json::arrayValue:
            {
                int size = value.size();
                for ( int index =0; index < size; ++index )
                {
                    Callbak(value,strkey,path);
                }
            }
            break;
        case Json::objectValue:
            {
                //fprintf( fout, "%s={}\n", path.c_str() );
                Json::Value::Members members( value.getMemberNames() );
                std::sort( members.begin(), members.end() );
                std::string suffix = "";//*(path.end()-1) == '.' ? "" : "";
                for ( Json::Value::Members::iterator it = members.begin(); 
                        it != members.end(); 
                        ++it )
                {
                    const std::string &name = *it;

                    PrintValueTree(/* fout,*/ value[name],name,path + suffix + name );
                    Callbak(value,strkey,path);
                }
            }
            break;
        default:
            break;
    }
}

