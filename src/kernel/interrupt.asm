section .asm

global interrupt

interrupt:
       mov eax,0
       mov ebx,1
       div eax