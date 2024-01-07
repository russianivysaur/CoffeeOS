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
   jmp CODE_SEG:load32

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
load32:
	mov eax,1
	mov ecx,100
	mov edi,0x100000
	call ata_lba_read
	jmp CODE_SEG:0x100000


;Dummy driver for kernel loading
ata_lba_read:
   mov ebx,eax ;Backup the LBA
   ;Send the highest 8 bits of the lba to disk controller
   shr eax, 24
   or eax,0xe0 ; Select the master drive
   mov dx,0x1f6 ;Port for disk driver
   out dx,al
   ;Finished sending the highest 8 bits of lba

   ;Sectors
   mov eax,ecx
   mov dx, 0x1f2
   out dx, al
   ;Finished sending total sectors to read

   mov eax,ebx ;Restore lba
   mov dx,0x1f3
   out dx,al
   ; Finished sending more bits

   ;Send more bits
   mov dx,0x1f4
   mov eax,ebx
   shr eax, 8
   out dx, al
   ;Finished more bits

   ;Send upper 16 bits for LBA
   mov dx, 0x1f5
   mov eax,ebx
   shr eax,16
   out dx,al
   ;Finished sending upper 16 bits of LBA

   mov dx,0x1f7
   mov al,0x20
   out dx,al


;Read all sectors into memory
.next_sector:
   push ecx

;Checking if we need to read
.try_again:
   mov dx,0x1f7
   in al,dx
   test al,8
   jz .try_again

   ;Reading 256 word at a time
   mov ecx,256
   mov dx,0x1f0
   rep insw
   pop ecx
   loop .next_sector
   ret

times 510-($-$$) db 0 ;clearing memory till 512 bytes
dw 0xAA55 ;little endian writing for boot signature (2 bytes)
