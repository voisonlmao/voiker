#include <lib/types/int.h>
#include <lib/types/defs.h>
#include <lib/string.h>
#include <lib/io.h>


size_t
string_length(
    const char *string
) {
    size_t length = 0;
    while (*string++) {
        length++;
    }

    return length;
}

void
string_int_to_string(
    int value,
    char *output,
    int base
) {
    for (size_t index = 0; index < 12; index++) {
        output[index] = '\0';
    }

    char temporary_buffer[12] = { 0 };
    uint8_t buffer_index = 0;

    if (base < 2 || base > 36) {
        return;
    }

    int target_value = value;

    do {
        temporary_buffer[buffer_index++] = STRING_DOUBLESIDED_ALPHABET[35 + target_value % base];
        target_value /= base;
    } while (target_value);

    if (value < 0 && base == 10) {
        temporary_buffer[buffer_index++] = '-';
    }

    buffer_index--;
    uint8_t size = buffer_index;
    do {
        char chararcter = temporary_buffer[buffer_index];
        if (chararcter == '\0') {
            break;
        }
        output[size - buffer_index] = chararcter;
        buffer_index--;
    } while (buffer_index + 1);
}
