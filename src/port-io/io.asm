global outb
global inb
global inw


outb:
   mov al,[esp+8]
   mov dx,[esp+4]
   out dx,al
   ret


inb:
   xor eax,eax
   mov dx,[esp+4]
   in al,dx
   ret


inw:
   xor eax,eax
   xor edx,edx
   mov dx,[esp+4]
   in ax,dx
   ret