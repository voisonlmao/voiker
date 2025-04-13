#include <kernel/hardware/hardware.h>
#include <lib/types/int.h>


hardware_info_t
hardware_get_info()
{
    uint16_t *detected_hardware = (uint16_t *)0x0410;
    uint8_t video_info = (*detected_hardware & 0x30);

    hardware_info_t info = {};
    info.vga_monochrome = video_info == 0x30;

    return info;
}
