section .asm
global load_idt
load_idt:
    mov ebx,[esp+4]
    lidt[ebx]
    ret