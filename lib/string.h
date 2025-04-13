#ifndef __VOIKER_LIB_STRING
#define __VOIKER_LIB_STRING


#include <lib/types/defs.h>


#define STRING_DOUBLESIDED_ALPHABET "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"


size_t string_length(const char *string);
void string_int_to_string(int value, char *output, int base);


#endif
