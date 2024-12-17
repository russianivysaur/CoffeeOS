//
// Created by bulbasaur on 17/12/24.
//

#include "stdlib.h"
#include <stddef.h>
void memset(void* dst,int c,size_t len){
  char* c_ptr = (char*) dst;
  for(size_t i=0;i<len;i++){
    c_ptr[i] = c;
  }
}