#include <kernel/hardware/hardware.h>
#include <kernel/hardware/vga.h>
#include <kernel/tty.h>
#include <lib/types/int.h>


vga_color_t foreground, background;
uint8_t x, y;


void
tty_init() {
    hardware_info_t info = hardware_get_info();
    vga_init(info.vga_monochrome);

    foreground = VGA_COLOR_GRAY;
    background = VGA_COLOR_BLACK;

    x = y = 0;
}


void
tty_clear() {
    for (uint8_t y = 0; y < VGA_VIDEO_HEIGHT; y++) {
        for (uint8_t x = 0; x < VGA_VIDEO_WIDTH; x++) {
            vga_put_character(x, y, ' ',
                    vga_color_pack_pair(foreground, background));
        }
    }

    x = y = 0;
}

void
tty_set_color(
    vga_color_t new_foreground,
    vga_color_t new_background
) {
    foreground = new_foreground;
    background = new_background;
}

void
tty_set_pointer_position(
    uint8_t new_x,
    uint8_t new_y
) {
    x = new_x;
    y = new_y;
}

void
tty_put_character(
    char character
) {
    uint8_t color_pair = vga_color_pack_pair(foreground, background);
    if (character != '\n') vga_put_character(x, y, character, color_pair);

    if (character == '\n' || ++x >= VGA_VIDEO_WIDTH) {
        x = 0;
        if (++y >= VGA_VIDEO_HEIGHT) {
            y--;
            tty_scroll_up();
        }
    }
}

void
tty_scroll_up() {
    char character;
    uint8_t color_pair;

    for (uint8_t y = 1; y < VGA_VIDEO_HEIGHT; y++) {
        for (uint8_t x = 0; x < VGA_VIDEO_WIDTH; x++) {
            character = vga_get_character(x, y, &color_pair);
            vga_put_character(x, y, ' ',
                    vga_color_pack_pair(VGA_COLOR_GRAY, VGA_COLOR_BLACK));
            vga_put_character(x, y - 1, character, color_pair);
        }
    }
}
