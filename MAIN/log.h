//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH

#pragma warning ( once : 4005 )

#include <fstream>
#include <stdarg.h>
//---------------------------------------------------------------------------
namespace ESL
{                        
//---------------------------------------------------------------------------
class CLogFile
{
private:
    char logtext[1024];

    std::ofstream  _LogFile;     //�������� ����� ������, � ������� ������� ���

    unsigned  _ErrorsCount;
    unsigned  _WarningsCount;

    //�������� ����������� ������ � ������ ������� ����
    void  StartupBanner(const char*);
    //�������� ����������� ������ � ����� ������� ����
    void  EndBanner(void);

    //����� � ��� ������� �����
    void  WriteTime(void);
    //����� � ��� ��������� ������ ��������� ������
    void  Write(const char*, const char*, va_list);
	int level;
public:

    std::ofstream& LogFile(void)           {return _LogFile;} 
	void AddLevel();
	void SubLevel();
    //����� � ��� ������������ ���������
    void  WriteMessage(const char*, ...);
    void  WriteMessageLevelUp(const char*, ...);
    void  WriteMessageLevelDown(const char*, ...);
    //����� � ��� ��������������
    void  WriteWarning(const char*, ...);
    //����� � ��� ��������� �� ������
    void  WriteError(const char*, ...);

    //� ������������ ��������� ��� � ���� ���������� ����������� ������
    CLogFile(const char*, const char*);
    //� ����������� ��� ����������� � �����������
    ~CLogFile(void);
};

//extern CLogFile SDELog;

#ifndef _ESLNDEBUG
  /*�������, ��������� ���� ������������� ��� ����� ������� ������
  ��������� �� ������ � ��� � �������� ����������.*/
  //err - ����� ������, ret - ������������ ���������
  #define MACRO_ERROR_RET(err,ret) {SDELog.WriteError(##err##);return(##ret##);}
  //err - ����� ������; �������������� ����� �� ���������� �������
  #define MACRO_ERROR_RET_VOID(err) {SDELog.WriteError(##err##);return;}
#else
  #define MACRO_ERROR_RET(err,ret)  {return(##ret##);}
  #define MACRO_ERROR_RET_VOID(err) {return;}
#endif
//---------------------------------------------------------------------------
}




#endif
