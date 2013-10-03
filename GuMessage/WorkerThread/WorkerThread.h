#ifndef _WORKERTHREAD_H_
#define _WORKERTHREAD_H_
#include "../stdafx.h"
#include "../DICThreadPool/DICTaskObject.h"

//#include "FileConvertDatabaseMgr.h"
// �������ͷ�ļ�
//#include "../MFCDeInCreaseThreadPool/ThreadDialog.h"

//����
#define THREAD_TYPE_PULL_INTAKE 0

//����
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

    // ����������ĳ�Ա����
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
    // ����������ĳ�Ա����
    static DWORD WINAPI ThreadRoutine( LPVOID lpParam );
	BOOL RunOfficeExe(CTaskInfo* pTaskInfo,int nUseType);
	void RunPdfExe(CTaskInfo* pTaskInfo,int nUseType);
	void RunNTVista(CTaskInfo* pTaskInfo,int nUseType);
	BOOL RunNTXP_2003(CTaskInfo* pTaskInfo,int nUseType);
private:
    BOOL m_bAutoDelete;

    // ����������ĳ�Ա����
    DWORD m_dwLifeTime;

    HANDLE m_hThreadTaskDialog;

//    CThreadDialog m_ThreadDialog;

    HANDLE m_hEventDlgClosed;

	int m_nType; //�����ж������Ǹ�����
	
	
	int m_nIndex;





	//COperateLog* m_pOperateLog;


};

#endif