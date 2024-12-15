[bits 16]
[org 0x7c00]
bpb:
  jmp short here
  nop

  times 33 db 0

here:
KERNEL_START EQU 0x1000

mov bp,0x7c00
mov sp,bp


call display_fancy_text
call load_kernel
call switch32
jmp $
%include "./src/boot/custom_bootloader_text.asm"
%include "./src/boot/load_from_disk.asm"
%include "./src/boot/gdt.asm"
%include "./src/boot/32bit.asm"

[bits 32]
launch_kernel:
      call KERNEL_START
      jmp $

times 510 - ($-$$) db 0
dw 0xaa55
