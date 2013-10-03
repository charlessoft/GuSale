#ifndef _TYPEDEFINE_H_
#define _TYPEDEFINE_H_
#include <string>
using namespace std;

typedef int                 BOOL;
#define FALSE 0
#define TRUE 1

#ifdef _LINUX_
    #define BOOL int
#endif
#endif


#ifdef _LINUX_
#else
#ifdef _DEBUG



#else
#endif
#endif

//#include "../lib/jsoncpp/include/json/json.h"
//#include "../lib/curl/include/curl/curl.h"
#include "../lib/jsoncpp-src-0.5.0/include/json/json.h"
#include "../lib/curl-7.32.0/include/curl/curl.h"

#define	WIN_PLATFORM
#include <windows.h>

#include <string>
#include <vector>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"wldap32.lib")