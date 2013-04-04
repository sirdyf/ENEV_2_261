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

    std::ofstream  _LogFile;     //файловый поток вывода, в который пишется лог

    unsigned  _ErrorsCount;
    unsigned  _WarningsCount;

    //помещает необходимые данные в начало каждого лога
    void  StartupBanner(const char*);
    //помещает необходимые данные в конец каждого лога
    void  EndBanner(void);

    //пишем в лог текущее время
    void  WriteTime(void);
    //пишет в лог указанным цветом указанную строку
    void  Write(const char*, const char*, va_list);
	int level;
public:

    std::ofstream& LogFile(void)           {return _LogFile;} 
	void AddLevel();
	void SubLevel();
    //пишет в лог произвольное сообщение
    void  WriteMessage(const char*, ...);
    void  WriteMessageLevelUp(const char*, ...);
    void  WriteMessageLevelDown(const char*, ...);
    //пишет в лог предупреждение
    void  WriteWarning(const char*, ...);
    //пишет в лог сообщение об ошибке
    void  WriteError(const char*, ...);

    //в конструкторе создается лог и туда помещаются необходимые данные
    CLogFile(const char*, const char*);
    //в деструкторе лог завершается и закрывается
    ~CLogFile(void);
};

//extern CLogFile SDELog;

#ifndef _ESLNDEBUG
  /*макросы, описанные ниже предназначены для более удобной записи
  сообщения об ошибке в лог и возврата результата.*/
  //err - текст ошибки, ret - возвращаемый результат
  #define MACRO_ERROR_RET(err,ret) {SDELog.WriteError(##err##);return(##ret##);}
  //err - текст ошибки; осуществляется выход из вызывающей функции
  #define MACRO_ERROR_RET_VOID(err) {SDELog.WriteError(##err##);return;}
#else
  #define MACRO_ERROR_RET(err,ret)  {return(##ret##);}
  #define MACRO_ERROR_RET_VOID(err) {return;}
#endif
//---------------------------------------------------------------------------
}




#endif
