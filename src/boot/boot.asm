org 0x7c00
bits 16

CODE_SEG equ code_segment_gdt - gdt_start
DATA_SEG equ data_segment_gdt - gdt_start


;bios parameter bloc
start:
    jmp short _start
    nop

times 33 db 0


_start:
    jmp 0x00:init

;Enable segments and print a message
init:
    cli
    mov ax,0x00
    mov ds,ax
    mov es,ax
    mov ax,0x00
    mov ss,ax
    mov sp,0x7c00
    sti
    call load_gdt


;loading gdt
load_gdt:
    cli
    lgdt[gdt]
    mov eax,cr0
    or al,1 ;Enabling PE bit in CR0
    mov cr0,eax
    jmp CODE_SEG:load32

;gdt
gdt:
    dw gdt_end - gdt_start - 1
    dd gdt_start

gdt_start:
null_entry:
     times 8 db 0
code_segment_gdt:
     dw 0xffff ;limit
     dw 0 ; base
     db 0 ;base 16-23
     db 0x9a ; access byte
     db 11001111b ;limit and flags
     db 0; base
data_segment_gdt:
     dw 0xffff ;limit
     dw 0 ; base
     db 0 ;base 16-23
     db 0x92 ; access byte
     db 11001111b ;limit and flags
     db 0; base
gdt_end:


[BITS 32]
load32:
     mov eax,1
     mov ecx,100
     mov edi,0x0100000
     call ata_lba_read
     jmp CODE_SEG:0x0100000


times 510-($-$$) db 0
dw 0xAA55

;disk buffer
buffer:
