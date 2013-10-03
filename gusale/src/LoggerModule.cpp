/**********************************************************************
* Copyright (C) 2008 -  - All Rights Reserved
*
* 文件名称:        LoggerModule.cpp
* 摘    要:        日志包裹类,日志模块的接口
*     
* 作    者:        yanglinbo, 
* 修    改:        查看文件最下方.
* 
***********************************************************************/

#include "../include/LoggerModule.h"

#include <cstdlib>
#include <iostream>
#include <log4cplus/config.hxx>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/socket.h>
#include <log4cplus/helpers/threads.h>
#include <log4cplus/spi/loggerimpl.h>
#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/spi/appenderattachable.h>
#include <log4cplus/appender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
//#include <stdarg.h>
#include <tchar.h>
using namespace log4cplus;
LoggerModule::LoggerModule()
{
	m_LogFileName = NULL;
}

LoggerModule::~LoggerModule()
{
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
	LOG4CPLUS_INFO(_logger, "Logger System Stop Finish.");
}

#define DO_LOGGERW(logLevel, filename, fileline, pFormat, bufSize)\
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();\
	\
	if(_logger.isEnabledFor(logLevel))\
{                \
	va_list args;            \
	va_start(args, pFormat);        \
 	wchar_t buf[bufSize] = {0};        \
 	_vsntprintf(buf, sizeof(buf), pFormat, args);    \
 	va_end(args);           \
 	_logger.forcedLog(logLevel, buf, filename, fileline); \
}


#define DO_LOGGER(logLevel, filename, fileline, pFormat, bufSize)\
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();\
	\
	if(_logger.isEnabledFor(logLevel))\
{                \
	va_list args;            \
	va_start(args, pFormat);        \
	TCHAR buf[bufSize] = {0};        \
	_vsntprintf(buf, sizeof(buf), pFormat, args);    \
	va_end(args);           \
	_logger.forcedLog(logLevel, buf, filename, fileline); \
}


#define DO_LOGGER_TRACE(logLevel, filename, fileline, pFormat, bufSize)\
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();\
	\
	if(_logger.isEnabledFor(logLevel))\
{                \
	va_list args;            \
	va_start(args, pFormat);        \
	TCHAR buf[bufSize] = {0};        \
	_vsntprintf(buf, sizeof(buf), pFormat, args);    \
	va_end(args);           \
	TCHAR TraceBuf[bufSize] = {0}; \
	_stprintf_s(TraceBuf,_T("CQ_TEST_line=%d,log=%s\r\n"),fileline,buf); \
	OutputDebugString(TraceBuf); \
}


void LoggerModule::Debug( const char* filename, const int fileline, const TCHAR* pFormat, ... )
{
	DO_LOGGER(log4cplus::DEBUG_LOG_LEVEL, filename, fileline, pFormat, 2048);
}

void LoggerModule::DebugW(const char* filename, const int fileline,const wchar_t* pFormat,... )
{
	
	DO_LOGGERW(log4cplus::DEBUG_LOG_LEVEL, filename, fileline, pFormat, 2048);
}

void LoggerModule::Error( const char* filename, const int fileline, const TCHAR* pFormat,...  )
{
	DO_LOGGER(log4cplus::ERROR_LOG_LEVEL, filename, fileline, pFormat, 256);
}

void LoggerModule::Fatal( const char* filename, const int fileline, const TCHAR* pFormat, ... )
{
	DO_LOGGER(log4cplus::FATAL_LOG_LEVEL, filename, fileline, pFormat, 256);
}

void LoggerModule::Info( const char* filename, const int fileline, const TCHAR* pFormat,...  )
{
	DO_LOGGER(log4cplus::INFO_LOG_LEVEL, filename, fileline, pFormat, 512);
}

void LoggerModule::Warn( const char* filename, const int fileline, const TCHAR* pFormat,...  )
{
	DO_LOGGER(log4cplus::WARN_LOG_LEVEL, filename, fileline, pFormat, 256);
}

void LoggerModule::Trace( const char* filename, const int fileline, const TCHAR* pFormat, ... )
{
	DO_LOGGER(log4cplus::TRACE_LOG_LEVEL, filename, fileline, pFormat, 1024);
}

void LoggerModule::Debug_Trace(const char* filename,const int fileline, const TCHAR* pFormat,...)
{
	DO_LOGGER_TRACE(log4cplus::TRACE_LOG_LEVEL, filename, fileline, pFormat, 1024);
}


void LoggerModule::StartSystem( const TCHAR* properties_filename )
{
	if (properties_filename==NULL) return;

 	log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(false);
 	log4cplus::PropertyConfigurator::doConfigure(properties_filename);
 	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
 	LOG4CPLUS_INFO(_logger, "Logger System Start Finish.");
}

void LoggerModule::StopSystem()
{

}

void LoggerModule::SetFileName(TCHAR* logFileName)
{
	m_LogFileName = logFileName;
}

void LoggerModule::StartSystemByUseer()
{
	/* step 1: Instantiate an appender object */
	log4cplus::SharedAppenderPtr _append(new log4cplus::RollingFileAppender(m_LogFileName, 10*1024, 5));
	
	_append->setName(_T("append for test"));   
	/* step 2: Instantiate a layout object */    
	std::wstring pattern = _T("%D{%m/%d/%y %H:%M:%S} [%t] %-5p %c{2} %%%x%% - %m [%l]%n");
	std::auto_ptr<log4cplus::Layout> _layout(new PatternLayout(pattern));   
	/* step 3: Attach the layout object to the appender */    

	_append->setLayout( _layout );   
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
	_logger.addAppender(_append);
	/* step 6: Set a priority for the logger  */    
	_logger.setLogLevel(ALL_LOG_LEVEL);   
	LOG4CPLUS_INFO(_logger, "Logger System Start Finish.");
}
