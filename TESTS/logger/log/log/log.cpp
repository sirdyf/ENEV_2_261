// log.cpp : Defines the entry point for the console application.
//
// ������ ��� ������� �� ��������� ������
//#define LOG_DISABLED

// ���������� ��� ���� ������
//#define LOG_DEBUG_DISABLED

#include "logger.h"

int testFunc()
{
  static int cnt = 1;
  LOG_ERROR << "Function " << cnt << " error.";
  return 11110 + cnt++;
}


void TestRecCrash(){
	LOG_ERROR << "same error";
	return;
  const int RecCount = 10; // ��������� �����, ����� ��� ����� ���� ����������� �� ������
  static int cnt = 1;

  LOG_ERROR  << "Entry " << cnt << " error.";

  if(cnt+1 >= RecCount)
  {
    double *p = 0;
    *p = 0; // access violation
  }

  if( cnt++ < RecCount )
      TestRecCrash();
}

int main(/*int argc, char* argv[]*/)
{
  LOG_PREFIX("mainLog");
  LOG_LEVEL(logger::Debug+1); // ������� ���� � �������� (��������, ���� �� ��������� ������)

  LOG_DEBUG_LEV(0) << "Test Level 0" ;
  LOG_DEBUG_LEV(1) << "Test Level 1" ;
  LOG_DEBUG_LEV(2) << "Test Level 2" ;
  LOG_DEBUG << "Test dedug" << 2 ;
  LOG_WARNING << "Test warning" << 3 ;//<< " : "  << " : " << 0.6 << " output.";
  LOG_ERROR << "Test error" << 4 ;
  LOG_PREFIX("mainLog2");
  LOG_ERROR << "Test error" << 5 ;

 TestRecCrash();
	system("pause");
  return 0;
}