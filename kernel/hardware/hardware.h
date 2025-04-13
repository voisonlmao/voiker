#ifndef __VOIKER_KERNEL_HARDWARE
#define __VOIKER_KERNEL_HARDWARE


#include <lib/types/bool.h>


typedef struct __voiker_hardware_info {
    bool vga_monochrome;
} hardware_info_t;


hardware_info_t hardware_get_info();


#endif
