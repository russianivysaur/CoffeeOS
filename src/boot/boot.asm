ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_start:
   jmp short start
   nop

times 33 db 0 ; empty 33 bytes for bios paramter block


start:
   jmp 0:init



init:
   cli ; Disable bios interrupts
   mov ax,0x00
   mov ds,ax ;Data segment
   mov es,ax ;Extra segment
   mov ss,ax ;Stack segment
   mov sp,0x00 ;Stack pointer
   sti ;Enable bios interrupts
   

.protected_mode:
   cli
   lgdt[gdt_descriptor]
   mov eax,cr0
   or eax,0x1
   mov cr0, eax
   jmp CODE_SEG:protectedMode

;GDT beginning
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

;a gdt entry default code segment (CS)
gdt_code: 
    dw 0xffff  ; 0-15 bits
    dw 0       ; base 0-15 bits
    db 0       ; base 16-23 bits
    db 0x9a    ; access byte
    db 1100111b ; flags
    db 0 ; 24-31 bits

;data segement (DS,GS, ES,FS,GS)
gdt_data:
    dw 0xffff  ; 0-15 bits
    dw 0       ; base 0-15 bits
    db 0       ; base 16-23 bits
    db 0x92    ; access byte
    db 1100111b ; flags
    db 0 ; 24-31 bits

gdt_end:

gdt_descriptor:
   dw gdt_end - gdt_start - 1
   dd gdt_start


[BITS 32]
protectedMode:
       mov ax, DATA_SEG
       mov ds, ax
       mov es,ax
       mov fs,ax
       mov gs,ax
       mov ss,ax
       mov ebp, 0x00200000
       mov esp,ebp

       ;Enable A20 line
       in al,0x92
       or al,2
       out 0x92,al
       
       jmp $


times 510-($-$$) db 0 ;clearing memory till 512 bytes
dw 0xAA55 ;little endian writing for boot signature (2 bytes)
