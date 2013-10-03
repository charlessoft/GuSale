/**********************************************************************
* Copyright (C) 2008 - - All Rights Reserved
*
* �ļ�����:        LoggerModule.h
* ժ    Ҫ:        ��־������,��־ģ��Ľӿ�
*     
* ��    ��:        yanglinbo, 
* ��    ��:        �鿴�ļ����·�.
* 
***********************************************************************/

#ifndef __LoggerModule_H__
#define __LoggerModule_H__
#include <tchar.h>

//��������
#ifndef LOGGER_MODULE_CLASS
	#ifdef  LOGGER_MODULE_DLL
		#define LOGGER_MODULE_CLASS _declspec(dllimport)
	#else
		#define LOGGER_MODULE_CLASS _declspec(dllexport)
	#endif
#endif

//ģ�鶨��
#ifdef _DEBUG
	#define LOGGER_MODULE_DLL_NAME    TEXT("LoggerModuleD.dll")            //��� DLL ����
#else
	#define LOGGER_MODULE_DLL_NAME    TEXT("LoggerModule.dll")            //��� DLL ����
#endif


/// ������
/// @note �ڳ���������ʱ�����Logger::Start���������磺
///       g_Logger.StartSystem("logModule.properties");
///       ����־��ʾ�����£�
///       g_Logger.Debug(__FILE__, __LINE__, "Debug log[%d]", 100);
///       �÷������Ϻ�printf()��CSting::Format()������ࡣ
///       �����VS2005�Լ����ϵĿ�������������ʹ�ú����־�����ӷ��㣺
///       LOG_DEBUG("Debug log[%d]", 100);
class LOGGER_MODULE_CLASS LoggerModule
{
public:
	LoggerModule();
	virtual ~LoggerModule();

	/// ������־ϵͳ
	/// @param[in] properties_filename ��־ϵͳ�����ļ��ļ���
	void StartSystem(const TCHAR* properties_filename);

	///�û��Զ��������ļ�,Ŀǰֻ���޸��ļ���
	void StartSystemByUseer();
	
	//�û��Զ����ļ���
	void SetFileName(TCHAR* logFileName);

	/// �ر���־ϵͳ
	void StopSystem();

public:
	void Debug(const char* filename, const int fileline, const TCHAR* pFormat,... );
	
	void DebugW(const char* filename, const int fileline,const wchar_t* pFormat,...  );

	void Error(const char* filename, const int fileline, const TCHAR* pFormat,... );

	void Fatal(const char* filename, const int fileline, const TCHAR* pFormat,... );

	void Info(const char* filename, const int fileline, const TCHAR* pFormat,... );

	void Warn(const char* filename, const int fileline, const TCHAR* pFormat,... );

	void Trace(const char* filename, const int fileline, const TCHAR* pFormat,... );

	void Debug_Trace(const char* filename,const int fileline, const TCHAR* pFormat,...);


public:
	static inline LoggerModule* getSingletonPtr()
	{
		return &getSingleton();
	}
	static inline LoggerModule& getSingleton()
	{
		static LoggerModule _instance; 
		return _instance;
	}
public:
	TCHAR* m_LogFileName;
};
#define g_Logger LoggerModule::getSingleton()
#define g_pLogger LoggerModule::getSingleton()


//////////////////////////////////////////////////////////////////////////
// ������־
//////////////////////////////////////////////////////////////////////////
#define ASSERT_LOG(expr)\
	if ( (expr) ) {;} else g_Logger.Error(__FILE__, __LINE__, #expr);


//////////////////////////////////////////////////////////////////////////
// ���µĺ�ֻ��VS2005�Լ�֮�ϵİ汾����ʹ�ã���ΪVS2005֮�µİ汾��֧�ֿɱ������
//////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && _MSC_VER > 1400 
 #define LOG_DEBUG()    g_Logger.Debug(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_ERROR()    g_Logger.Error(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_FATAL()    g_Logger.Fatal(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_INFO()    g_Logger.Info(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_WARN()    g_Logger.Warn(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_TRACE()    g_Logger.Trace(__FILE__, __LINE__, __VA_ARGS__);
#endif
//#include <tchar.h>


#endif