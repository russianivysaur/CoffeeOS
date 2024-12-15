#include "vga.h"
void main(){
  volatile char* ideoMemory = VIDEO_MEMORY_ADDRESS;
  cls();
  char* hello = "Hello, It's a work in progress";
  centerWrite(hello);
}
