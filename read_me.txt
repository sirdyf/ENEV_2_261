������ ������

 dfomin (10:07:14 14/08/2009)
C/C++->CodeGeneration->Runtime Library->
����: "Runtime Library = multi-threaded debug(/MTd)"

 sasha (10:07:45 14/08/2009)
� �� ���� �������� ��������/���������?

 dfomin (10:07:58 14/08/2009)
C/C++->CodeGeneration->Runtime Library->
�����: "Runtime Library = multi-threaded debug DLL (/MDd)"

 dfomin (10:08:07 14/08/2009)
� ��� �����!

��� ����:
Linker->Command Line -> Additional options:
/FORCE:MULTIPLE

--------------------------
����������, ��� ���� � ������ Release � ������� �/C++ - Code Generation � �������� Runtime Library ��������� Multi-threaded Debug DLL (/MDd) ������ Multi-threaded DLL (/MD), �� ��������� ��� ��������� ����������� � ��������..

������� ����� ���� ���������...
������, ��� �������� � ������ - � Debug ������ ��� ���������� � ������� ���������������� 0xcc � � Release - ���. ������� �������� �������������������� ���������� ����� ������ � ������ configurations'��.

� ���� ����� �������� ����� ������. ���������� � ���� ��������� �������: � ������ ����� ��������� ��������� OutputDebugString, � ����� ������� ������������� ���������� ���������. ���� ���-�� ��� �� ��� ��������� ��������������� ����� ����.
----------
 sasha (10:15:05 14/08/2009)
������� Runtime Library - Multi Threaded (Debug)

������ ��� ����� �������� ����������� �������� CRT.
---------------
��������� ����������:

Solution Explorer->������ ���� �� �������->Properties
Configuration->All configurations;
C/C++->CodeGeneration->Runtime Library->Multi-threaded Debug (/MTd);
Linker->Manifest file->Generate manifest->No;
General->Character Set->Use Multi-Byte Character Set;
OK.

� ����� ��� �������.
�� � ��� ������ ��� �� ��������.
----------------------
����� ��������� �������� � ���������� ������ � ��� ����� ���������� ����������, � � ������ ������� ���������� �� �����. ������ ���������� �������� ������. ������� � �������� ������� (Project->Propertis) �� ������� General ������ <Use Multi-Byte Character Set>, ���� �� ��������� ��� ��  ����� ������������ ������. � ������� Linker->System ������ <Console (/SUBSYSTEM:CONSOLE)> (������ ��� ������������ Debug). ����� ���������� ��������� � C/C++->Code Generation->Runtime Library  "Multi-threaded Debug (/MTd))" ��� ������������ Debug � "Multi-threaded (/MT)" ��� ������������ Release, ����� ���� ��������� �� ����� ��������� ������� ��������� Visual Studio 2005.
----------------------------
