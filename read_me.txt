ошибка памяти

 dfomin (10:07:14 14/08/2009)
C/C++->CodeGeneration->Runtime Library->
Было: "Runtime Library = multi-threaded debug(/MTd)"

 sasha (10:07:45 14/08/2009)
и чё этот параметр включает/отключает?

 dfomin (10:07:58 14/08/2009)
C/C++->CodeGeneration->Runtime Library->
Стало: "Runtime Library = multi-threaded debug DLL (/MDd)"

 dfomin (10:08:07 14/08/2009)
И все пошло!

еще есть:
Linker->Command Line -> Additional options:
/FORCE:MULTIPLE

--------------------------
Выяснилось, что если в опциях Release в разделе с/C++ - Code Generation в качестве Runtime Library поставить Multi-threaded Debug DLL (/MDd) вместо Multi-threaded DLL (/MD), то программа уже нормально запускается и работает..

проблем может быть несколько...
Первое, что приходит в голову - в Debug версии все переменные и массивы инициализируются 0xcc а в Release - нет. Поэтому значения неинициализированный переменных будет разным в разных configurations'ах.

У меня такое довольно часто бывало. Справлялся с этим следующим образом: в разные места программы засовывал OutputDebugString, и таким образом контролировал выполнение программы. Если что-то шло не так исправлял соответствующий кусок кода.
----------
 sasha (10:15:05 14/08/2009)
Ставишь Runtime Library - Multi Threaded (Debug)

Именно эта опция включает статическую линковку CRT.
---------------
Пошаговая инструкция:

Solution Explorer->правый клик на проекте->Properties
Configuration->All configurations;
C/C++->CodeGeneration->Runtime Library->Multi-threaded Debug (/MTd);
Linker->Manifest file->Generate manifest->No;
General->Character Set->Use Multi-Byte Character Set;
OK.

И будет вам счастье.
Да и про сервис пак не забудьте.
----------------------
Здесь небольшая хитрость в отладочном режиме у нас будет консольное приложение, а в релизе консоль создаватся не будет. Теперь необходимо настроть проект. Заходим в свойства проекта (Project->Propertis) во вкладке General ставим <Use Multi-Byte Character Set>, этим мы указываем что не  будем использовать Юникод. В вкладке Linker->System ставим <Console (/SUBSYSTEM:CONSOLE)> (только для конфигурации Debug). Также желательно поставить в C/C++->Code Generation->Runtime Library  "Multi-threaded Debug (/MTd))" для конфигурации Debug и "Multi-threaded (/MT)" для конфигурации Release, тогда ваша программа не будет требовать наличия библиотек Visual Studio 2005.
----------------------------
