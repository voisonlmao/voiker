#!/bin/sh

obinary="voiker.bin"

cflags="-std=gnu99 -ffreestanding -O2 -Wall -Wextra -I."
ldflags="-ffreestanding -O2 -nostdlib -lgcc"


sfiles=(
    "kernel/interupts/gdt.s"
    "kernel/boot.s"
)

cfiles=(
    "kernel/hardware/hardware.c"
    "kernel/hardware/vga.c"
    "kernel/interupts/gdt.c"
    "kernel/io/port.c"
    "kernel/io/serial.c"
    "kernel/main.c"
    "kernel/tty.c"
    "lib/io.c"
    "lib/string.c"
)


# debug information
echo "================ VOIBLD ================"
echo "obinary = ${obinary}"
echo "cflags  = ${cflags}"
echo "ldflags = ${ldflags}"
echo "sfiles  = ("

for file in "${sfiles[@]}"; do
    echo "    ${file}"
done

echo ")"
echo "cfiles  = ("

for file in "${cfiles[@]}"; do
    echo "    ${file}"
done

echo ")"
echo "========================================"

# setting error handler
set -e


if [ "$1" == "-c" ]; then
    echo "clearing..."
    rm -rf build/*
    exit
fi


mkdir -p build

# building all .s files
for sfile in "${sfiles[@]}"; do
    echo "target: ${sfile}"
    
    name=${sfile//\//_}
    i686-elf-as ${sfile} -o build/${name}.o
done

# building all .c files
for cfile in "${cfiles[@]}"; do
    echo "target: ${cfile}"
    
    name=${cfile//\//_}
    i686-elf-gcc -c ${cfile} -o build/${name}.o ${cflags}
done

# finaly linking the binary
echo "linking: ${obinary} "
i686-elf-gcc -T linker.ld -o ${obinary} build/*.o ${ldflags}

echo "================= DONE ================="



if [ "$1" == "-t" ]; then
    echo "qemu target: ${obinary}"
    qemu-system-i386 -kernel ${obinary}
fi
