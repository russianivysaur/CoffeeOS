global load_gdt

DATA_SEG equ 0x10
CODE_SEG equ 0x08

load_gdt:
      mov eax,[esp+4]
      lgdt[eax]
      mov ax,DATA_SEG
      mov ds,ax
      mov ss,ax
      mov gs,ax
      mov fs,ax
      mov es,ax
      jmp CODE_SEG:.here


.here:
   ret