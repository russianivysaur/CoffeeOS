load_kernel:
   pusha
   mov dh,2
   push dx
   mov ah,02h
   mov bx,KERNEL_START
   mov al,dh
   mov cl,2
   mov ch,0
   mov dh,0
   int 13h
   jc disk_error
   pop dx
   cmp al,dh
   jne sector_error
   popa
   call display_success
   ret


disk_error:
   call display_disk_error
   ret

sector_error:
   call display_sector_error
   ret
