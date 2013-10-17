#pragma once
#include <map>
#include <string>
#include <list>
class  CTaskInfo;
typedef map<int,CTaskInfo*> MapTaskList;
typedef list<CTaskInfo*> TaskFileList;

class CTaskInfo
{
public:
	CTaskInfo();
	CTaskInfo(wstring filePath);
	~CTaskInfo(){}
	CTaskInfo(const CTaskInfo&); //拷贝构造函数
	int m_Index;
	wstring m_strTaskName;//任务名字
	wstring m_strFileExtent; //文件扩展名
	wstring m_strFileName;//文件名
	wstring m_strFileNameWithoutExt;
	wstring m_strFilePath;
	int m_nFileType;
};

class CTaskQueue
{
private:
	CTaskQueue(void);
public:
	~CTaskQueue(void);
	//map<int,string> m_TaskList;
	MapTaskList m_TaskList;
	LONG m_nSingleDealWps;//同时只能处理一条wps数据
	LONG m_nSingleDealDoc;//同时只能处理一条wps数据
	LONG m_nSingleDealEt;//同时只能处理一条et数据
	LONG m_nSingleDealXls;//同时只能处理一条Xls数据
	LONG m_nSingleDealDps;//同时只能处理一条dps数据
	LONG m_nSingleDealPpt;//同时只能处理一条ppt数据
	CRITICAL_SECTION m_Critical_LockSingle;

	list<CTaskInfo*> m_TaskListlist;

	list<CTaskInfo*> m_TaskListRedeal;//用来存放重做任务

	void Produce();

	void Consume();

	void PutTask(CTaskInfo* pTaskInfo);

	CTaskInfo* PopTask();

	void PutTaskRe_dealData(CTaskInfo* pTaskInfo);

	void GetRedealData();

	int GetTaskListCount();

	void SetSingleDealWps(BOOL bFlag);

	void DealResult(CTaskInfo* pTaskInfo,int nRes);

	void UpdateLog(TCHAR* szlog);

	void UpdateDealCount(TCHAR* szlog);

	void UpdateDealFile(TCHAR* szlog);

	HANDLE   g_hMutex;               //用于线程间的互斥   
	HANDLE   g_hFullSemaphore;           //当缓冲区满时迫使生产者等待   
	HANDLE   g_hEmptySemaphore;           //当缓冲区空时迫使消费者等待   

	static inline CTaskQueue* getSingletonPtr()
	{
		return &getSingleton();
	}

	static inline CTaskQueue& getSingleton()
	{
		static CTaskQueue _instance; 
		return _instance;
	}
	BOOL EnumFile(CString str,TCHAR* filter,CStringArray& array);

	BOOL GetChangeData(string url,string strParam,list<CTaskInfo*>& array);

	string GetServerData(string url,string strParam);

	BOOL ParseJson(const char* json,list<CTaskInfo*>& array);

	CStringArray m_FileArr;
	//vector<CTaskInfo*> m_FileDataArr;
};

#define g_TaskListMgr CTaskQueue::getSingleton()
#define g_pTaskListMgr CTaskQueue::getSingleton()

