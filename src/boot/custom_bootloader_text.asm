text db "Hello, Welcome to Coffee Bootloader.",0
diskerror db "Disk error.",0
sectorerror db "Sector error.",0
success db "Kernel loaded successfully",0
display_fancy_text:
     mov si,text
     mov ah,0xE

loop_till_text_over:
     mov al,[si]
     cmp al,0
     je done
     int 10h
     inc si
     jmp loop_till_text_over


done:
    ret


display_disk_error:
    mov si,diskerror
    mov ah,0xE
    jmp loop_till_text_over
    ret

display_sector_error:
    mov si,sectorerror
    mov ah,0xE
    jmp loop_till_text_over
    ret

display_success:
    mov si,success
    mov ah,0xE
    jmp loop_till_text_over
    ret
