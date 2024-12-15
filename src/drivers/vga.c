#include "../kernel/vga.h"
void cls(){
  char* videoMemory = VIDEO_MEMORY_ADDRESS;
  int offset = 0;
  while(offset<ROWS*COLS*2){
    videoMemory[offset] = ' ';
    videoMemory[offset+1] = (GREEN << 4) | (RED);
    offset += 2;
  }
}

void centerWrite(char* string){
  int offset = (ROWS*COLS*2)/2 - 30; 
  writeString(string,offset);
}


void writeString(char* string,int offset){
  volatile char* videoMemory = VIDEO_MEMORY_ADDRESS;
  while(*string!='\0'){
    videoMemory[offset] = *string;
    videoMemory[offset+1] = (GREEN << 4) | (RED);
    string++;
    offset += 2;
  }
}
