//
// Created by bulbasaur on 20/12/24.
//

#include "kheap.h"
#include "heap.h"
#include "../stdlib/stdlib.h"

struct Heap* kheap;
void init_kheap(){
  kheap = create_heap(KERNEL_HEAP_START,KERNEL_HEAP_SIZE);
}


uint32_t* kalloc(uint32_t size){
  return alloc(size,kheap);
}

void kfree(uint32_t* address){
  free(address,kheap);
}

uint32_t* kzalloc(uint32_t size){
  uint32_t* allocated = kalloc(size);
  memset(allocated,0,size);
  return allocated;
}