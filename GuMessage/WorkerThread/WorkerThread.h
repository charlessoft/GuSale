#ifndef _WORKERTHREAD_H_
#define _WORKERTHREAD_H_
#include "../stdafx.h"
#include "../DICThreadPool/DICTaskObject.h"

//#include "FileConvertDatabaseMgr.h"
// 增加你的头文件
//#include "../MFCDeInCreaseThreadPool/ThreadDialog.h"

//买入
#define THREAD_TYPE_PULL_INTAKE 0

//卖出
#define THREAD_TYPE_PULL_OFFTAKE 1

class CTaskInfo;
class CFileConvertDatabaseMgr;
class CWorkerThread: 
    public CDICTaskObject
{
public:
    CWorkerThread();
    ~CWorkerThread();

public:
    VOID SetAutoDelete( BOOL bAutoDel );

    // 以下增加你的成员函数
    VOID SetLifeTime( DWORD dwtime );
    DWORD GetLifeTime();
    INT_PTR TaskDialog();
    VOID SetDlgClosedEvent();

	void SetIndex(int nIndex);
void SetType(int nType);
	void CreateFileConverDbMgr();
protected:
    EThreadRoutineExitType Run();

	EThreadRoutineExitType Run_InTake();
	
	EThreadRoutineExitType Run_OffTake();

    BOOL AutoDelete();

private:
    // 以下增加你的成员函数
    static DWORD WINAPI ThreadRoutine( LPVOID lpParam );
	BOOL RunOfficeExe(CTaskInfo* pTaskInfo,int nUseType);
	void RunPdfExe(CTaskInfo* pTaskInfo,int nUseType);
	void RunNTVista(CTaskInfo* pTaskInfo,int nUseType);
	BOOL RunNTXP_2003(CTaskInfo* pTaskInfo,int nUseType);
private:
    BOOL m_bAutoDelete;

    // 以下增加你的成员变量
    DWORD m_dwLifeTime;

    HANDLE m_hThreadTaskDialog;

//    CThreadDialog m_ThreadDialog;

    HANDLE m_hEventDlgClosed;

	int m_nType; //用来判断用是那个类型
	
	
	int m_nIndex;





	//COperateLog* m_pOperateLog;


};

#endif