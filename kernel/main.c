#include <kernel/interupts/gdt.h>
#include <kernel/io/serial.h>
#include <kernel/io/port.h>
#include <kernel/misc.h>
#include <kernel/tty.h>
#include <lib/io.h>


#define COM 0x3F8


void kmain() {
    tty_init();
    tty_clear();

    if (!serial_port_init(COM)) {
        klogf("unable to access COM-port (%x)\n", COM);
    }

    slog(COM, "installing gdt.\n");
    gdt_install();
    
    slog(COM, "initialization complete.\n");
    klog("this is ready, yay!\n");
}
