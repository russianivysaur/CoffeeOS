global load_page_directory

load_page_directory:
      mov eax,[esp+4]
      mov cr3,eax
      mov eax,cr0
      or eax,0x80000001
      mov cr0,eax
      ret