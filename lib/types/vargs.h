#ifndef __VOIKER_LIB_VARIADIC_ARGUMENTS
#define __VOIKER_LIB_VARIADIC_ARGUMENTS


#if defined(__GNUC__) && __GNUC__ >= 3
    typedef __builtin_va_list   va_list;
#else
    typedef char *              va_list;
#endif


#define va_start(list, last)            __builtin_va_start((list), last)
#define va_end(list)                    __builtin_va_end((list))
#define va_arg(list, type)              __builtin_va_arg((list), type)
#define __va_copy(destination, source)  __builtin_va_copy((destination), (source))

#if __ISO_C_VISIBLE >= 1999
#define va_copy(destination, source)    __va__va_copy((destination), (source))
#endif


#endif
