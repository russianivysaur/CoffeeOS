//
// Created by bulbasaur on 20/12/24.
//

#include "kheap.h"
#include "heap.h"
#include "../stdlib/stdlib.h"
struct Heap* init_kheap(){
  return create_heap(KERNEL_HEAP_START,KERNEL_HEAP_SIZE);
}


uint32_t* kalloc(uint32_t size,struct Heap* heap){
  return alloc(size,heap);
}

void kfree(uint32_t* address,struct Heap* heap){
  free(address,heap);
}

uint32_t* kzalloc(uint32_t size,struct Heap* heap){
  uint32_t* allocated = kalloc(size,heap);
  memset(allocated,0,size);
  return allocated;
}