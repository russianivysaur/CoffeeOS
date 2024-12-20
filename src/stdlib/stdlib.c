//
// Created by bulbasaur on 20/12/24.
//
#include <stdint.h>
#include "stdlib.h"
#include <stddef.h>

extern uint32_t kernel_end;
void itoa(int num,uint8_t* buffer){
  int i=0;
  if(num==0){
    buffer[i++] = '0';
  }else{
    while(num!=0){
      int last = num%10;
      num = num/10;
      char c = ((char)last) + '0';
      buffer[i++] = c;
    }
  }
  buffer[i] = '\0';
}


void memset(void* dst,int c,size_t len){
    char* c_ptr = (char*) dst;
    for(size_t i=0;i<len;i++){
        c_ptr[i] = c;
    }
}


uint32_t kalloc(uint32_t length){
  uint32_t allocated = (uint32_t) &kernel_end;
  kernel_end += length;
  return allocated;
}

void kfree(void* address,uint32_t length) {

}