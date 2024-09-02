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
    jmp CODE_SEG:protected


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



;Printing routine
print_message:
    lodsb
    cmp al,0
    je done
    mov ah,0eh
    int 0x10
    jmp print_message

done:
   ret

;Disk loader
load_from_disk:
    mov ah,02h
    mov al,1
    mov ch,0
    mov cl,2
    mov dh,0
    mov bx,buffer
    int 0x13
    mov si,buffer
    call print_message


[BITS 32]
protected:
     mov eax,DATA_SEG
     mov ds,eax
     mov es,eax
     mov fs,eax
     mov gs,eax
     mov ss,eax
     mov ebp,0x00200000
     ;A20 line
     in al,0x92
     or al,2
     out 0x92,al

     jmp $


message: db 'Hi',0
times 510-($-$$) db 0
dw 0xAA55

;disk buffer
buffer:
