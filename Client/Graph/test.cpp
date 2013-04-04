#include <windows.h>
#include <stdio.h>

BOOL LogText(char *lpszText, ...)
{
    va_list argList;
    FILE *pFile;

    // �������������� ������ ����������
    va_start(argList, lpszText);

    // ��������� ���-���� ��� ���������� ������
    if ((pFile = fopen("log.txt", "a+")) == NULL)
    return(FALSE);

    // ����� ��� ����� � ��������� �� ����� ������
    vfprintf(pFile, lpszText, argList);
    putc('\n', pFile);

    // ��������� ����
    fclose(pFile);
    va_end(argList);

	return(TRUE);
}