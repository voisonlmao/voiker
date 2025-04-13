#include <kernel/hardware/vga.h>
#include <lib/types/defs.h>
#include <lib/types/bool.h>
#include <lib/types/int.h>


uint8_t *buffer;
bool colors_available;


void
vga_init(
    bool monochrome
) {
    buffer = monochrome
        ? (uint8_t *)0xB0000
        : (uint8_t *)0xB8000;

    colors_available = !monochrome;
}


uint8_t
vga_color_pack_pair(
    vga_color_t foreground,
    vga_color_t background
) {
    return (uint8_t)foreground | (uint8_t)background << 4;
}

void
vga_put_character(
    uint8_t x, uint8_t y,
    char character,
    uint8_t color_pair
) {
    uint16_t index = 0;
    if (colors_available) {
        index = (y * VGA_VIDEO_WIDTH * 2) + (x * 2);
    } else {
        index = y * VGA_VIDEO_WIDTH + x;
    }

    buffer[index] = character;
    if (colors_available) {
        buffer[index + 1] = color_pair;
    }
}


void
vga_color_unpack_pair(
    uint8_t color,
    vga_color_t *foreground,
    vga_color_t *background
) {
    if (NULL != foreground) {
        *foreground = color & 0x0F;
    }

    if (NULL != background) {
        *background = color & 0xF0;
    }
}

char
vga_get_character(
    uint8_t x, uint8_t y,
    uint8_t *color
) {
    uint16_t index = 0;
    if (colors_available) {
        index = (y * VGA_VIDEO_WIDTH * 2) + (x * 2);
    } else {
        index = y * VGA_VIDEO_WIDTH + x;
    }

    char character = buffer[index];
    if (colors_available && NULL != color) {
        *color = buffer[index + 1];
    }

    return character;
}
