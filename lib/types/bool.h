#ifndef __VOIKER_LIB_BOOL
#define __VOIKER_LIB_BOOL


#if defined(__GNUC__) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901)

#define false 0
#define true 1

#else

typedef enum {
    false = 0,
    true = 1
} _Bool;

#define false false
#define true true

#endif


#define bool _Bool


#endif

