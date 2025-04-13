.equ flags, 1<<0 | 1<<1
.equ magic, 0x1BADB002
.equ checksum, -(magic + flags)


.section .multiboot
.align 4
.long magic
.long flags
.long checksum


.section .bss
.align 16
stack_begin: .skip 16384
stack_end:


.section .text
.global _start
.type _start, @function
_start:
    mov $stack_end, %esp
    call kmain
    cli
_l: hlt
    jmp _l

.size _start, . - _start
