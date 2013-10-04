#include "stdafx.h"
#include "TaskQueue.h"

 CRITICAL_SECTION m_Critical_TaskList;
 #define Lock EnterCriticalSection(&m_Critical_TaskList)
 #define UnLock LeaveCriticalSection(&m_Critical_TaskList)
 
 #define LockSingle EnterCriticalSection(&m_Critical_LockSingle)
 #define UnLockSingle LeaveCriticalSection(&m_Critical_LockSingle)
 // CTaskQueue::m_BSingleDealWps = FALSE;
 BOOL bTst = FALSE;
 
 
 #ifdef _GET_URL_DATA_
 	const unsigned short SIZE_OF_BUFFER = 2;   //缓冲区长度  
 #else
 	const unsigned short SIZE_OF_BUFFER = 10;   //缓冲区长度  
 #endif
 
 int   g_buffer[SIZE_OF_BUFFER];         //缓冲区是个循环队列 
 unsigned   short   ProductID   =   0;         //产品号   
 unsigned   short   ConsumeID   =   0;         //将被消耗的产品号 
 unsigned   short   in   =   0;             //产品进缓冲区时的缓冲区下标   
 unsigned   short   out   =   0;             //产品出缓冲区时的缓冲区下标   
 
 LONG g_dealCount=0;
 
 CTaskInfo::CTaskInfo()
 {
 	m_strTaskName=L"";
 	m_strFileName=L"";
 	m_strFileExtent=L"";
 }
 
 CTaskInfo::CTaskInfo(wstring filePath)
 {
 	m_Index = 0;
 	m_strFilePath = filePath;
 	int nPos = filePath.rfind('.');
 	m_strFileExtent = filePath.substr(nPos);
 	nPos = filePath.rfind('\\');
 	m_strFileName = filePath.substr(nPos+1);
 	m_strFileNameWithoutExt = m_strFileName.substr(0,m_strFileName.find('.'));
 	wstring strFileExtent = _tcslwr((wchar_t*)m_strFileExtent.c_str());
 //	map<wstring,int>::iterator Iter = theApp.m_pConfig->m_MapFileType.find(strFileExtent);
 // 	if (Iter!=theApp.m_pConfig->m_MapFileType.end())
 // 	{
 // 		//说明找到
 // 		m_nFileType = theApp.m_pConfig->m_MapFileType[m_strFileExtent];
 // 	}
 // 	else
 // 	{
 // 		g_Logger.Debug(__FILE__,__LINE__,_T("没有对应的文件类型%s"),m_strFileExtent.c_str());
 // 	}
 // 	if (_tcsicmp(m_strFileExtent.c_str(),_T(".doc")) ==0)
 // 	{
 // 		m_nFileType = FILETYPE_DOC;
 // 	}
 // 	else if(_tcsicmp(m_strFileExtent.c_str(),_T(".docx")) ==0)
 // 	{
 // 		m_nFileType = FILETYPE_DOCX;
 // 
 // 	}
 // 	else if(_tcsicmp(m_strFileExtent.c_str(),_T(".wps")) ==0)
 // 	{
 // 		m_nFileType = FILETYPE_WPS;
 // 	}
 // 	else if(_tcsicmp(m_strFileExtent.c_str(),_T(".xls")) ==0)
 // 	{
 // 		m_nFileType = FILETYPE_XLS;
 // 	}
 // 	else if(_tcsicmp(m_strFileExtent.c_str(),_T(".xlt")) ==0)
 // 	{
 // 		m_nFileType = FILETYPE_XLT;
 // 	}
 // 	else if(_tcsicmp(m_strFileExtent.c_str(),_T(".xlsx")) ==0)
 // 	{
 // 		m_nFileType = FILETYPE_XLSX;
 // 	}
 // 	else if(_tcsicmp(m_strFileExtent.c_str(),_T(".et")) ==0)
 // 	{
 // 		m_nFileType = FILETYPE_ET;
 // 	}
 }
 
 CTaskInfo::CTaskInfo(const CTaskInfo& taskInfo) //拷贝构造函数
 {
 	this->m_strTaskName = taskInfo.m_strTaskName;
 	this->m_strFileExtent = taskInfo.m_strFileExtent;
 	this->m_strFileName = taskInfo.m_strFileName;
 	this->m_Index = taskInfo.m_Index;	
 	this->m_nFileType= taskInfo.m_nFileType;	
 
 }
 
 CTaskQueue::CTaskQueue(void)
 
 {
 	m_nSingleDealWps = 0;
 	m_nSingleDealEt = 0;
 	m_nSingleDealDps = 0;
 	m_nSingleDealDoc = 0;
 	m_nSingleDealXls = 0;
 	m_nSingleDealPpt = 0;
 	InitializeCriticalSection(&m_Critical_TaskList);
 	InitializeCriticalSection(&m_Critical_LockSingle);
 	//创建各个互斥信号   
 	g_hMutex   =   CreateMutex(NULL,FALSE,NULL);   
 	g_hFullSemaphore   =   CreateSemaphore(NULL,SIZE_OF_BUFFER-1,SIZE_OF_BUFFER-1,NULL);   
 	g_hEmptySemaphore   =   CreateSemaphore(NULL,0,SIZE_OF_BUFFER-1,NULL);   
 
 
 
 }
 
 CTaskQueue::~CTaskQueue(void)
 {
 	DeleteCriticalSection(&m_Critical_TaskList);
 	DeleteCriticalSection(&m_Critical_LockSingle);
 	TaskFileList::iterator Iter;
 	for (Iter = m_TaskListlist.begin();Iter!=m_TaskListlist.begin();++Iter)
 	{
 		delete *Iter;
 	}
 	m_TaskListlist.clear();
 }
 
 void CTaskQueue::Produce()
 {
 	g_Logger.Debug_Trace(__FILE__,__LINE__,_T("Producing   %d"),++ProductID);
 	g_Logger.Debug_Trace(__FILE__,__LINE__,_T("Succeed"));
 
 }
 
 
 
 void  CTaskQueue::Consume()   
 {
 
 	g_Logger.Debug_Trace(__FILE__,__LINE__,_T("Consuming   %d"),ConsumeID);
 	g_Logger.Debug_Trace(__FILE__,__LINE__,_T("Succeed"));
 }

 void CTaskQueue::PutTask(CTaskInfo* pTaskInfo)
 {
 
 
 	g_Logger.Debug_Trace(__FILE__,__LINE__,_T("Appending   a   product   ...   "));
 
 	list<CTaskInfo*> ::iterator Iter;
 
 	BOOL bFind = FALSE;
 	for (Iter = m_TaskListlist.begin();Iter!=m_TaskListlist.end();++Iter)
 	{
 		CTaskInfo* pTmpTaskInfo = (CTaskInfo*)*Iter;
 		if (pTmpTaskInfo->m_strFileName == pTaskInfo->m_strFileName)
 		{
 			bFind = TRUE;
 			break;
 		}
 	}

 	if (bFind == FALSE)
 	{
 		CString strLog;
 		m_TaskListlist.push_back(pTaskInfo);
 		strLog.Format(_T("生产者:放入数据%d,文件名%s,队列个数:%d"),pTaskInfo->m_Index,pTaskInfo->m_strFileName.c_str(),g_TaskListMgr.m_TaskListlist.size());
 		g_TaskListMgr.UpdateLog(strLog.GetBuffer());
 		g_Logger.Debug_Trace(__FILE__,__LINE__,_T("Succeed"));
 		g_Logger.Debug_Trace(__FILE__,__LINE__,_T("----ProductID-----%d"),pTaskInfo->m_Index);
 	}
 	else
 		delete pTaskInfo;
 	
 }
 
 void CTaskQueue::PutTaskRe_dealData(CTaskInfo* pTaskInfo)
 {
 	LockSingle;
 	g_Logger.Debug_Trace(__FILE__, __LINE__, _T("----------------放回数据:%s"),pTaskInfo->m_strFileName.c_str());
 	g_Logger.Debug(__FILE__, __LINE__,  _T("----------------放回数据:%s"),pTaskInfo->m_strFileName.c_str());
 	CTaskInfo* ptmp = new CTaskInfo(*pTaskInfo);
 	m_TaskListRedeal.push_back(ptmp);
 	UnLockSingle;
 }
 
 
 void CTaskQueue::GetRedealData()
 {
 	LockSingle;
 	CTaskInfo* pTaskInfo = NULL;
 	while (m_TaskListRedeal.size()>0)
 	{
 		pTaskInfo = m_TaskListRedeal.front();
 		m_TaskListRedeal.pop_front();
 		m_TaskListlist.push_back(pTaskInfo);
 	}
 	UnLockSingle;
 }
 
 
 CTaskInfo* CTaskQueue::PopTask()
 {
 	g_Logger.Debug_Trace(__FILE__,__LINE__,_T("Taking   a   product   ...   "));
 	CTaskInfo* pTaskInfo = NULL;
 	if (m_TaskListlist.size()>0)
 	{
 		pTaskInfo = m_TaskListlist.front();
 		m_TaskListlist.pop_front();
 		//g_Logger.Debug_Trace(__FILE__,__LINE__,_T("Succeed"));
 		//g_Logger.Debug_Trace(__FILE__,__LINE__,_T("----ConsumeID---------------%d"),pTaskInfo->m_Index);
 		CString strLog;
 		strLog.Format(_T("file count =%d"),m_TaskListlist.size());
 		UpdateLog(strLog.GetBuffer());
 	}
 
 	return pTaskInfo;
 
 }
 
 int CTaskQueue::GetTaskListCount()
 {
 	Lock;
 	int nCount = m_TaskList.size();
 	UnLock;
 	return nCount;
 }
 
 
 void CTaskQueue::UpdateDealCount(TCHAR* szlog)
 {
 
 //::SendMessage(AfxGetApp()->m_pMainWnd->m_hWnd,UM_DEALCOUNT,(WPARAM)szlog,NULL);
 
 }
 
 
 void CTaskQueue::UpdateLog(TCHAR* szlog)
 {
 	//if(AfxGetApp()->m_pMainWnd->m_hWnd)
 //		::SendMessage(AfxGetApp()->m_pMainWnd->m_hWnd,UM_DEALRESULT,(WPARAM)szlog,NULL);
 }
 
 
 void CTaskQueue::DealResult(CTaskInfo* pTaskInfo,int nRes)
 {
 	Lock;
 
 	CString strLog;
 	strLog.Format(_T("result taskid=%d,res=%d,TaskListCount=%d"),pTaskInfo->m_Index,nRes,m_TaskList.size());
 	UpdateLog(strLog.GetBuffer());
 	g_Logger.Debug(__FILE__,__LINE__,strLog);
 
 // 	if (pTaskInfo->m_nFileType == FILETYPE_PNG ||
 // 		pTaskInfo->m_nFileType == FILETYPE_BMP ||
 // 		pTaskInfo->m_nFileType == FILETYPE_TIF ||
 // 		pTaskInfo->m_nFileType == FILETYPE_TIFF ||
 // 		pTaskInfo->m_nFileType == FILETYPE_JPEG ||
 // 		pTaskInfo->m_nFileType == FILETYPE_JPG )
 // 	{
 // 		if ( nRes == FALSE )
 // 		{
 // 			g_dealCount++;
 // 			strLog.Format(_T("处理个数 %ld"),g_dealCount);
 // 			UpdateDealCount(strLog.GetBuffer());
 // 		}
 // 	}
 // 	else if ( nRes != FALSE )
 // 	{
 // 		g_dealCount++;
 // 		strLog.Format(_T("处理个数 %ld"),g_dealCount);
 // 		UpdateDealCount(strLog.GetBuffer());
 // 	}
 
 	//g_Logger.Debug_Trace(__FILE__,__LINE__,_T("result taskid=%d,res=%d,TaskListCount=%d"),pTaskInfo->m_Index,nRes,m_TaskList.size());
 	
 	UnLock;
 }
 
 void CTaskQueue::SetSingleDealWps(BOOL bFlag)
 {
 	Lock;
 	m_nSingleDealWps = bFlag;
 	UnLock;
 }
 string CTaskQueue::GetServerData(string url,string strParam)
 {
 // 	Service cservice;
 // 	//string url = "http://10.142.51.15/test.php";
 // 	vector<string> header;
 // 	string mydata="userName=hellocharles";
 // 	PutData pt;
 // 	memset(&pt,0,sizeof(PutData));
 // 	pt.data = (char*)mydata.c_str();
 // 	pt	.datalen = mydata.length();
 // 	string resp_buffer="",resp_header="";
 // 	int nRes = cservice.HttpRequest("POST",url,header,&pt	,resp_buffer,resp_header);
 // 	if (nRes == CURLE_OK)
 // 	{
 // 		return resp_buffer;
 // 	}
 	return "";
 }
 
 BOOL CTaskQueue::ParseJson(const char* json,list<CTaskInfo*>& array)
 {
 // 	Json::Features features;
 // 	Json::Reader reader( features );
 // 	Json::Value root;
 // 	//const char* testjson = "[{\"type\" : \".doc\", \"filepath\" :\"1.doc\"} , {\"type\" : \".doc\", \"filepath\" : \"2.doc\"},{\"type\" : \".doc\", \"filepath\" : \"3.doc\"},{\"type\" : \".doc\", \"filepath\" : \"4.doc\"},{\"type\" : \".doc\", \"filepath\" : \"5.doc\"},{\"type\" : \".doc\", \"filepath\" : \"6.doc\"},{\"type\" : \".doc\", \"filepath\" : \"7.doc\"},{\"type\" : \".doc\", \"filepath\" : \"8.doc\"},{\"type\" : \".doc\", \"filepath\" : \"9.doc\"},{\"type\" : \".doc\", \"filepath\" : \"10.doc\"}]";
 // 	//bool parsingSuccessful = reader.parse( testjson, root );
 // 	//const char* testjson = "[{\"type\" : \"doc\", \"filepath\":\"1.doc\"},{\"type\" : \"doc\", \"filepath\" : \"2.doc\"},{\"type\" : \"doc\", \"filepath\" : \"3.doc\"},{\"type\" : \"doc\", \"filepath\" : \"4.doc\"},{\"type\" : \"doc\", \"filepath\" : \"5.doc\"},{\"type\" : \"doc\", \"filepath\" : \"6.doc\"},{\"type\" : \"doc\", \"filepath\" : \"7.doc\"},{\"type\" : \"doc\", \"filepath\" : \"8.doc\"},{\"type\" : \"doc\", \"filepath\" : \"9.doc\"}, {\"type\" : \"doc\", \"filepath\" : \"10.doc\"},{\"type\" : \"doc\", \"filepath\" : \"11.doc\"} , {\"type\" : \"doc\", \"filepath\" : \"12.doc\"}]";
 // 	CString strjson;
 // 	int file1=0;
 // 	int file2=0;
 // 	time_t t;
 // 	time(&t);
 // 	srand(t);
 // 	file1 = rand()%200;
 // 	file2	 = rand()%200;
 // 	//if (ii>=30)
 // 	{
 // 		return FALSE;
 // 	}
 // 	strjson.Format(_T("[{\"type\" : \".doc\", \"filepath\" :\"%d.doc\"} , {\"type\" : \".doc\", \"filepath\" : \"%d.doc\"},{\"type\" : \".doc\", \"filepath\" :\"%d.doc\"} , {\"type\" : \".doc\", \"filepath\" : \"%d.doc\"},{\"type\" : \".doc\", \"filepath\" :\"%d.doc\"} , {\"type\" : \".doc\", \"filepath\" : \"%d.doc\"},{\"type\" : \".doc\", \"filepath\" :\"%d.doc\"} , {\"type\" : \".doc\", \"filepath\" : \"%d.doc\"}]"),ii++,ii++,ii++,ii++,ii++,ii++,ii++,ii++);
 // //	const char* testjson = "[{\"type\" : \".doc\", \"filepath\" :\"1.doc\"} , {\"type\" : \".doc\", \"filepath\" : \"2.doc\"},{\"type\" : \".doc\", \"filepath\" : \"3.doc\"}]";
 // 	string strTmp = ws2s(strjson.GetBuffer());
 // 	bool parsingSuccessful = reader.parse(strTmp.c_str(), root );
 // //bool parsingSuccessful = reader.parse( testjson , root );
 // 	if ( !parsingSuccessful )
 // 	{
 // 		return FALSE;
 // 	}
 // 	int size = root.size();
 // 	string type;
 // 	string filepath;
 // 	CTaskInfo* pTaskInfo = NULL;
 // 	for (int i=0; i<size; ++i)
 // 	{
 // 		type = root[i]["type"].asString();
 // 		filepath = root[i]["filepath"].asString();
 // 
 // 		for (map<wstring,int>::iterator Iter=theApp.m_pConfig->m_MapFileType.begin();Iter!=theApp.m_pConfig->m_MapFileType.end();++Iter)
 // 		{
 //  			if (s2ws(type) == Iter->first)
 //  			{
 //  				pTaskInfo = new CTaskInfo(s2ws(filepath));
 //  				//array.push_back(pTaskInfo);
 // 				g_TaskListMgr.PutTask(pTaskInfo);
 //  				break;
 //  			}
 // 		}
 // 		
 // 	}
 	return TRUE;
 }
 
 BOOL CTaskQueue::GetChangeData(string url,string strParam,list<CTaskInfo*>& array)
 {
 
//  	string respBuffer = GetServerData(url,strParam);
//  	if (respBuffer=="")
//  	{
//  		return FALSE;
//  	}
//  	ParseJson(respBuffer.c_str(),array);
 
   
 	return TRUE;
 }
 
 BOOL CTaskQueue::EnumFile(CString str,TCHAR* filter,CStringArray& array)
 {
 // 	CFileFind fileFinder;
 // 	CString filePath = str + _T("//*.*");
 // 
 // 	BOOL bFinished = fileFinder.FindFile(filePath);
 // 	while(bFinished)  //每次循环对应一个类别目录
 // 	{
 // 		bFinished = fileFinder.FindNextFile();
 // 		if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //若是目录则递归调用此方法
 // 		{
 // 			// BayesCategoryTest(bt, fileFinder.GetFilePath());
 // 		}
 // 		else  //再判断是否为txt文件
 // 		{
 // 			//获取文件类型
 // 			CString fileName = fileFinder.GetFileName();
 // 			int dotPos=fileName.ReverseFind('.');
 // 			CString fileTmpExt= fileName.Right(fileName.GetLength()-dotPos);
 // 			CString fileExt = fileTmpExt.MakeLower();
 // 			for (map<wstring,int>::iterator Iter=theApp.m_pConfig->m_MapFileType.begin();Iter!=theApp.m_pConfig->m_MapFileType.end();++Iter)
 // 			{
 // 				if (fileExt.CompareNoCase(Iter->first.c_str()) == 0)
 // 				{
 // 					array.Add(str+_T("\\")+fileName);
 // 					break;
 // 				}
 // 			}
 // // 			if(fileExt == _T(".doc") ||
 // // 				fileExt == _T(".docx") ||
 // // 				fileExt == _T(".wps") ||
 // // 				fileExt == _T(".xls") ||
 // // 				fileExt == _T(".et")  ||
 // // 				fileExt == _T(".xlsx") 
 // // 				)  //若是txt文件则开始分类测试
 // // 			{
 // // 				array.Add(str+fileName);
 // // 			}
 // 		}
 // 	}
 	return  TRUE;
 }