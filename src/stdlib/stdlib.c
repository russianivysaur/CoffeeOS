//
// Created by bulbasaur on 20/12/24.
//
#include <stdint.h>
#include "stdlib.h"
#include <stddef.h>

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