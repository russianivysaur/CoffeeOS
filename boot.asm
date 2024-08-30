org 0
bits 16

start:
    jmp short _start
    nop

times 33 db 0


_start:
    jmp 0x7c0:init

init:
    cli
    mov ax,0x7c0
    mov ds,ax
    mov es,ax
    mov ax,0x00
    mov ss,ax
    mov sp,0x7c00
    sti
    call load_from_disk



print_message:
    lodsb
    cmp al,0
    je done
    mov ah,0eh
    int 0x10
    jmp print_message

done:
   ret

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

times 510-($-$$) db 0
dw 0xAA55

buffer:
