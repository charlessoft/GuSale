#include <stdio.h>
#include <stdlib.h>
#include  "CService.h"
#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include "StdString.h"
using namespace std;
int g_nindex = 0;
string GetTitle(string buffer)
{
    boost::smatch what;
    boost::regex expression("<title>.+</title>");
    bool r= boost::regex_search(buffer, what, expression );
    if( r )
    {
        for(size_t i=0;i<what.size();i++)
        {
           if(what[i].matched)
           {
               string utf8data = what[i];

             char search[] = {0xE7,0x9a};
             char sztitle[] = "<title>";
             int nlen=strlen(sztitle);
             int npos = utf8data.find(search);
             string username = utf8data.substr(nlen,npos-nlen);
             wstring wstr = UTF8ToUnicode(username);
             string stmp = ws2s(wstr);
             cout<<stmp<<endl;
            return stmp;      
           }
        }
    }
}
void WriteToFile(string buffer)
{
    FILE* fp = fopen("1.txt","wb");
    if(fp)
    {
        fwrite(buffer.data(),1,buffer.size(),fp);
        fclose(fp);
    }
}

int main()
{
    Service CService;
    string strurl="http://www.gu360.com/home/2310144";
    int nRes = CService.HttpRequest("GET",strurl);
    string resp_buffer = CService.m_resp_buffer;
    string resp_header = CService.m_resp_header;
    
    GetTitle(resp_buffer);
    WriteToFile(resp_buffer);
//    printf("resp_buffer=%s",resp_buffer.c_str());
//    printf("resp_header=%s",resp_header.c_str());
//
    
}
