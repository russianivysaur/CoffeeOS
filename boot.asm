org 0x7c00
bits 16

welcome_message: db 'Coffee bootloader',0

start:
    mov si,welcome_message
    call print_welcome_message


print_welcome_message:
    lodsb
    cmp al,0
    je done
    mov ah,0eh
    int 0x10
    jmp print_welcome_message


done:
    jmp done

times 510-($-$$) db 0
dw 0xAA55
