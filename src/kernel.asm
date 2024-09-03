[BITS 32]
CODE_SEG equ 0x08
DATA_SEG equ 0x10
protected:
     mov eax,DATA_SEG
     mov ds,eax
     mov es,eax
     mov fs,eax
     mov gs,eax
     mov ss,eax
     mov ebp,0x00200000
     ;A20 line
     in al,0x92
     or al,2
     out 0x92,al

     jmp $
