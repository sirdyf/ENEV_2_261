#include <windows.h>
#include <stdio.h>

BOOL LogText(char *lpszText, ...)
{
    va_list argList;
    FILE *pFile;

    // инициализируем список аргументов
    va_start(argList, lpszText);

    // открываем лог-файл для добавления данных
    if ((pFile = fopen("log.txt", "a+")) == NULL)
    return(FALSE);

    // пишем наш текст и переходим на новую строку
    vfprintf(pFile, lpszText, argList);
    putc('\n', pFile);

    // закрываем файл
    fclose(pFile);
    va_end(argList);

	return(TRUE);
}