#include <kernel/io/serial.h>
#include <kernel/tty.h>
#include <lib/types/vargs.h>
#include <lib/types/defs.h>
#include <lib/string.h>
#include <lib/io.h>


void
kput(
    const char *string
) {
    for (size_t index = 0; index < string_length(string); index++) {
        tty_put_character(string[index]);
    }
}

void
kputf(
    const char *string,
    ...
) {
    va_list list;
    va_start(list, string);
    
    char arg_character;
    char *arg_buffer;
    int arg_number;
    char arg_number_str[12] = { 0 };

    while (*string) {
        char character = *string++;
        switch (character) {
        case '%':
            character = *string++;
            if (character == 's') {
                arg_buffer = va_arg(list, char *);
                kput(arg_buffer);
            } else if (character == 'd') {
                arg_number = va_arg(list, int);
                string_int_to_string(arg_number, arg_number_str, 10);
                kput(arg_number_str);
            } else if (character == 'x') {
                arg_number = va_arg(list, int);
                string_int_to_string(arg_number, arg_number_str, 16);
                kput(arg_number_str);
            } else if (character == 'c') {
                arg_character = va_arg(list, int);
                tty_put_character(arg_character);
            } else if (character == '%') {
                tty_put_character('%');
            }
            break;
        default:
            tty_put_character(character);
            break;
        }
    }

    va_end(list);
}


void
sput(
    uint16_t com_port,
    const char *string
) {
    for (size_t index = 0; index < string_length(string); index++) {
        if (string[index] == '\n') {
            serial_port_write(com_port, '\r');
        }
        serial_port_write(com_port, string[index]);
    }
}

void
sputf(
    uint16_t com_port,
    const char *string,
    ...
) {
    va_list list;
    va_start(list, string);
    
    char arg_character;
    char *arg_buffer;
    int arg_number;
    char arg_number_str[12] = { 0 };

    while (*string) {
        char character = *string++;
        switch (character) {
        case '%':
            character = *string++;
            if (character == 's') {
                arg_buffer = va_arg(list, char *);
                sput(com_port, arg_buffer);
            } else if (character == 'd') {
                arg_number = va_arg(list, int);
                string_int_to_string(arg_number, arg_number_str, 10);
                sput(com_port, arg_number_str);
            } else if (character == 'x') {
                arg_number = va_arg(list, int);
                string_int_to_string(arg_number, arg_number_str, 16);
                sput(com_port, arg_number_str);
            } else if (character == 'c') {
                arg_character = va_arg(list, int);
                if (arg_character == '\n') {
                    serial_port_write(com_port, '\r');
                }
                serial_port_write(com_port, arg_character);
            } else if (character == '%') {
                serial_port_write(com_port, '%');
            }
            break;
        default:
            tty_put_character(character);
            break;
        }
    }

    va_end(list);
}
