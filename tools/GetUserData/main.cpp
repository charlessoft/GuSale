#include <stdio.h>
#include <stdlib.h>
#include  "CService.h"
#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include "StdString.h"
using namespace std;
int g_nindex = 0;
int show_version;
int show_help;
int n_begin;
int n_end;
char* pfile; 

extern "C" void FX_OUTPUT_LOG_FUNC(const char* pfile,const char* format, ...)
{
    va_list argList;
    va_start(argList, format);
    printf("pfile=%s\r\n",pfile);
    FILE* file = fopen(pfile, "ab+");
    if (file == NULL) return;
    vfprintf(file, format, argList);
    fprintf(file, "\n");
    fclose(file);
    va_end(argList);

}
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

               //for(int i=0;i<utf8data.size();i++)
               //{
               //    printf("%2X ",(unsigned char)utf8data[i]);
               //}
               char search[] = {0xE7,0x9a,0x0};
               //printf("search=%s\r\n",search);
               char sztitle[] = "<title>";
               int nlen=strlen(sztitle);
               int npos = utf8data.find(search);
               //printf("npos=%d,nlen=%d\r\n",npos,nlen);
               string username = utf8data.substr(nlen,npos-nlen);
               wstring wstr = UTF8ToUnicode(username);
               string stmp = ws2s(wstr);
               //      cout<<stmp<<endl;
               return stmp;      
           }
        }
    }
}
void WriteToFile(string buffer,char* pfile)
{
    FILE* fp = fopen(pfile,"ab");
    if(fp)
    {
        fwrite(buffer.data(),1,buffer.size(),fp);
        fclose(fp);
    }
    else
    {
        printf("open fail--\r\n");
    }
}

int get_options(int argc,char** argv)
{
    char* p;
    int i;
    for (i = 1; i < argc; i++) {
        p = (char*)argv[i];
        //printf("p=%c\r\n",*p++);

        if(*p++ != '-')
        {
            printf("p======%c",*p);
            printf("invalid option:%s",argv[i]);
            return -1;
        }
        //else
        //{
        //    printf("ok\r\n");
        //}
        while(*p)
        {
            switch(*p++)
            {
                case '?':
                case 'h':
                    show_version = 1;
                    show_help = 1;
                    break;
                case 'v':
                    show_version = 1;
                    break;
                case 'f':
 //                   printf("argv[i]=%s\r\n",argv[++i]);
                    n_begin =  atoi(argv[++i]);
                    break;
                case 'e':
                    n_end = atoi(argv[++i]);
                    break;
                case 'w':
                    pfile = argv[++i];
                    break;
            }
        }
    }
    return 1;
}
int main(int argc, char** argv)
{
    if(get_options(argc,argv) != 1)
    {
        return 1;
    }
    if(show_version)
    {
        printf("version:xxxx\r\n");
    }
    if(show_help)
    {   
    }
    printf("begin=%d,end=%d,file=%s\r\n",n_begin,n_end,pfile);
    int i=0;

    for(i=n_begin;i<n_end;i++)
    {
        //stringstream ss;
        char szbuf[260]={0};
        Service CService;
        sprintf(szbuf,"%s%d","http://www.gu360.com/home/",i);
        string strurl = szbuf;
        //string strurl="http://www.gu360.com/home/";
        //strurl +=i;
        int nRes = CService.HttpRequest("GET",strurl);
        string resp_buffer = CService.m_resp_buffer;
        string resp_header = CService.m_resp_header;

        string username = GetTitle(resp_buffer);
        printf("username=%s",username.c_str());
        //WriteToFile(username,pfile);
        FX_OUTPUT_LOG_FUNC(pfile,"%d,%s",i,username.c_str());

        //WriteToFile(resp_buffer);
    }
    //    printf("resp_buffer=%s",resp_buffer.c_str());
    //    printf("resp_header=%s",resp_header.c_str());
    //

}
