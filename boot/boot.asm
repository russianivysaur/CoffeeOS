ORG 0
BITS 16

_start:
   jmp short start
   nop

times 33 db 0 ; empty 33 bytes for bios paramter block


start:
   jmp 0x7c0:init

init:
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
