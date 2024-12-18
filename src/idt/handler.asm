global handler
extern c_handler

handler:
      push eax
      push ebx
      push ecx
      push edx
      push ebp
      push edi
      call c_handler
      pop edi
      pop ebp
      pop edx
      pop ecx
      pop ebx
      pop eax
      iret