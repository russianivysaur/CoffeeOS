ORG 0x7c00
BITS 16

start:
   mov si,message
   call startPrint


startPrint:
.start:
   lodsb
   cmp al,0
   je .done
   call printCharacter
   jmp .start
.done:
   ret


printCharacter:
   mov ah,0eh
   int 0x10
   ret




message: db 'This is coffee bootloader',0

times 510-($-$$) db 0 ;clearing memory till 512 bytes
dw 0xAA55 ;little endian writing for boot signature (2 bytes)
