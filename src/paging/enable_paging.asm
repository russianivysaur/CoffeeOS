global enable_paging

global load_page_directory


load_page_directory:
       mov ebx,[esp+4]
       mov cr3,ebx
       ret


enable_paging:
     mov eax,cr0
     or eax,0x80000000
     mov cr0,eax
     ret