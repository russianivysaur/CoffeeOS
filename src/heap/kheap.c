//
// Created by bulbasaur on 20/12/24.
//

#include "kheap.h"
#include "heap.h"
struct Heap* init_kheap(){
  return create_heap(KERNEL_HEAP_START,KERNEL_HEAP_SIZE);
}