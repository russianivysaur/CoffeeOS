[bits 16]
[org 0x7c00]
KERNEL_START EQU 0x1000

mov bp,0x9000
mov sp,bp


call display_fancy_text
call load_kernel
%include "custom_bootloader_text.asm"
%include "load_from_disk.asm"

times 510 - ($-$$) db 0
dw 0xaa55
