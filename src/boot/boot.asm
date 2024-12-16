[bits 16]
[org 0x7c00]


protected:
     cli
     lgdt [gdt_descriptor]
     mov eax,cr0
     or al,1
     mov cr0,eax
     jmp CODE_SEG:init32


[bits 32]
init32:
     mov eax,DATA_SEG
     mov ds,eax
     mov ss,eax
     mov fs,eax
     mov es,eax
     ;Stack
     mov ebp,0x80000
     mov esp,ebp

     mov eax,0x1 ;Parameter for lba read LBA 1
     mov cl,0x2 ; No of sectors to read
     mov edi,0x100000 ;Target address
     call ata_lba_read
     jmp CODE_SEG:0x100000 ;1 mebabyte address


[bits 32]
;Source @ https://wiki.osdev.org/ATA_read/write_sectors
ata_lba_read:
               pushfd
               and eax, 0x0FFFFFFF
               push eax
               push ebx
               push ecx
               push edx
               push edi

               mov ebx, eax         ; Save LBA in RBX
               
               mov edx, 0x01F6      ; Port to send drive and bit 24 - 27 of LBA
               shr eax, 24          ; Get bit 24 - 27 in al
               or al, 11100000b     ; Set bit 6 in al for LBA mode
               out dx, al

               mov edx, 0x01F2      ; Port to send number of sectors
               mov al, cl           ; Get number of sectors from CL
               out dx, al
               
               mov edx, 0x1F3       ; Port to send bit 0 - 7 of LBA
               mov eax, ebx         ; Get LBA from EBX
               out dx, al

               mov edx, 0x1F4       ; Port to send bit 8 - 15 of LBA
               mov eax, ebx         ; Get LBA from EBX
               shr eax, 8           ; Get bit 8 - 15 in AL
               out dx, al


               mov edx, 0x1F5       ; Port to send bit 16 - 23 of LBA
               mov eax, ebx         ; Get LBA from EBX
               shr eax, 16          ; Get bit 16 - 23 in AL
               out dx, al

               mov edx, 0x1F7       ; Command port
               mov al, 0x20         ; Read with retry.
               out dx, al

.still_going:  in al, dx
               test al, 8           ; the sector buffer requires servicing.
               jz .still_going      ; until the sector buffer is ready.

               mov eax, 256         ; to read 256 words = 1 sector
               xor bx, bx
               mov bl, cl           ; read CL sectors
               mul bx
               mov ecx, eax         ; RCX is counter for INSW
               mov edx, 0x1F0       ; Data port, in and out
               rep insw             ; in to [RDI]

               pop edi
               pop edx
               pop ecx
               pop ebx
               pop eax
               popfd
               ret

gdt_start:

gdt_null:
   dq 0x0


gdt_code:
   dw 0xffff ; limit
   dw 0x0 ;base lower
   db 0x0 ;base 32-39
   db 0x9a ; access byte 
   db 0xcf
   db 0x00


gdt_data:
   dw 0xffff
   dw 0x0
   db 0x0
   db 0x92
   db 0xcf
   db 0x0

gdt_end:

gdt_descriptor:
      dw gdt_end - gdt_start - 1
      dd gdt_start

CODE_SEG EQU gdt_code - gdt_start
DATA_SEG EQU gdt_data - gdt_start

times 510 - ($-$$) db 0
dw 0xaa55
