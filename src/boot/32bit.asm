[bits 16]
switch32:
    cli
    lgdt [gdt_descriptor]
    mov eax,cr0
    or eax, 0x1
    mov cr0,eax
    jmp CODE_SEG:init


[bits 32]
init:
    mov ax,DATA_SEG
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov fs,ax
    mov gs,ax

    mov ebp,0x900000
    mov esp,ebp

    call launch_kernel
