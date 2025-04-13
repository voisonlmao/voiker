#ifndef __VOIKER_LIB_IO
#define __VOIKER_LIB_IO


#include <lib/types/int.h>


void kput(const char *string);
void kputf(const char *string, ...);
void sput(uint16_t com_port, const char *string);
void sputf(uint16_t com_port, const char *string, ...);


#endif
