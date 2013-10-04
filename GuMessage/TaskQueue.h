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
	CTaskInfo(const CTaskInfo&); //�������캯��
	int m_Index;
	wstring m_strTaskName;//��������
	wstring m_strFileExtent; //�ļ���չ��
	wstring m_strFileName;//�ļ���
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
	LONG m_nSingleDealWps;//ͬʱֻ�ܴ���һ��wps����
	LONG m_nSingleDealDoc;//ͬʱֻ�ܴ���һ��wps����
	LONG m_nSingleDealEt;//ͬʱֻ�ܴ���һ��et����
	LONG m_nSingleDealXls;//ͬʱֻ�ܴ���һ��Xls����
	LONG m_nSingleDealDps;//ͬʱֻ�ܴ���һ��dps����
	LONG m_nSingleDealPpt;//ͬʱֻ�ܴ���һ��ppt����
	CRITICAL_SECTION m_Critical_LockSingle;

	list<CTaskInfo*> m_TaskListlist;

	list<CTaskInfo*> m_TaskListRedeal;//���������������

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

	HANDLE   g_hMutex;               //�����̼߳�Ļ���   
	HANDLE   g_hFullSemaphore;           //����������ʱ��ʹ�����ߵȴ�   
	HANDLE   g_hEmptySemaphore;           //����������ʱ��ʹ�����ߵȴ�   

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

