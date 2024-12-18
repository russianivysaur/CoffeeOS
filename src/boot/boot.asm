global _start
extern main

MAGIC_NUMBER EQU 0x1BADB002
FLAGS EQU 0x0
CHECKSUM EQU -MAGIC_NUMBER

KERNEL_STACK_SIZE EQU 4096


section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE


section .text:
align 4
     dd MAGIC_NUMBER
     dd FLAGS
     dd CHECKSUM


_start:
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call main

.loop:
    jmp .loop