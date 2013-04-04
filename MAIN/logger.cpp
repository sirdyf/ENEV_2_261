#include "..\client\logger.h"

    // Синглтон от WolfHound: http://rsdn.ru/forum/Message.aspx?mid=531518&only=1
LONG logger::Private::atom_set(volatile LONG* ptr, LONG value){
	return ::InterlockedExchange(ptr, value);
}

LONG logger::Private::atom_get(volatile LONG* ptr){
	return ::InterlockedExchangeAdd(ptr, 0);
}
