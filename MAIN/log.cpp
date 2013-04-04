//---------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>

#pragma hdrstop

#include "log.h"
//---------------------------------------------------------------------------

namespace ESL
{
//---------------------------------------------------------------------------
//CLogFile SDELog("log.htm","Global Log");
//---------------------------------------------------------------------------

void CLogFile::StartupBanner(const char *logname)
{
    _LogFile<<"<html>";
    _LogFile<<"<title>Log</title>";
    _LogFile<<"<meta http-equiv=\"Content-Type\"content=\"text/html; charset=windows-1251\">";
    _LogFile<<"<body bgcolor=\"#555555\" text=\"#aaaaaa\">";
    _LogFile<<"<pre>";
    _LogFile<<"<h1>Work Log - "<<logname<<"</h1><BR>";
    _LogFile<<"<h3><NoBR>----------------------------- Begin ------------------------------</NoBR></h3>";
}

//---------------------------------------------------------------------------

void CLogFile::EndBanner()
{
    _LogFile<<"<h3><NoBR>---------------------------- Results -----------------------------</NoBR></h3>";
    _LogFile<<"<B>"<<_ErrorsCount<<" error(s), "<<_WarningsCount<<" warning(s)";
    _LogFile<<"</B></pre></body></html>";
}

//---------------------------------------------------------------------------

void CLogFile::WriteTime(void)
{
    SYSTEMTIME time;
//    GetSystemTime(&time);
    _LogFile<<"<Font Size = 1 Color = #ABABAB Face = Verdana><B>";
    _LogFile<<time.wHour<<":"<<time.wMinute<<":"<<time.wSecond<<"."<<time.wMilliseconds<<" - ";
    _LogFile<<"</B></font>";
}

//---------------------------------------------------------------------------
void CLogFile::AddLevel(){
	++level;
	if (level>9) level=9;
}
void CLogFile::SubLevel(){
	--level;
	if (level<0) level=0;
}
void CLogFile::Write(const char* color, const char* string, va_list args)
{
    if (!string) return;

	ZeroMemory(logtext,sizeof(logtext));
	char tab[10]={9,9,9,9,9,9,9,9,9,9};
	tab[level]=0;
	vsprintf(logtext, string, args);

//    WriteTime();
    _LogFile<<"<Font Size = 2 Color = "<<color
            <<" Face = Verdana>"<<tab<<logtext<<"</font><BR>";
}

//---------------------------------------------------------------------------

void CLogFile::WriteMessage(const char* string, ...){
    va_list args;
    va_start(args, string);
    Write("#00FF00",string,args);
    va_end(args);
}
void CLogFile::WriteMessageLevelUp(const char* string, ...){
    va_list args;
    va_start(args, string);
    Write("#00FF00",string,args);
    va_end(args);
	AddLevel();
}
void CLogFile::WriteMessageLevelDown(const char* string, ...){
	SubLevel();
    va_list args;
    va_start(args, string);
    Write("#00FF00",string,args);
    va_end(args);
}

//---------------------------------------------------------------------------

void CLogFile::WriteWarning(const char* string, ...)
{
    va_list args;
    va_start(args, string);
    Write("#FFFF00",string,args);
    va_end(args);

    ++_WarningsCount;
}

//---------------------------------------------------------------------------

void CLogFile::WriteError(const char* string, ...)
{
    va_list args;
    va_start(args, string);
    Write("#FF0000",string,args);
    va_end(args);

    ++_ErrorsCount;
}

//---------------------------------------------------------------------------

CLogFile::CLogFile(const char *file,const char *logname):
    _ErrorsCount(0), _WarningsCount(0)
{
	_LogFile.open(file,std::ios::out | std::ios::trunc);
    StartupBanner(logname);
	level=0;
}

//---------------------------------------------------------------------------

CLogFile::~CLogFile()
{
    EndBanner();
    _LogFile.close();
}

//---------------------------------------------------------------------------
}
