//
// Created by bulbasaur on 20/12/24.
//

#include "heap.h"
#include "../stdlib/stdlib.h"

struct Heap* create_heap(uint32_t start_address,uint32_t size){
  int n_entries = (size) / HEAP_BLOCK_SIZE;
  uint8_t entries[n_entries];
  memset(&entries,0,n_entries);
  struct Heap* heap = (struct Heap*) HEAP_STORAGE_LOCATION;
  heap -> start_address = start_address;
  heap -> size = size;
  heap -> entries = entries;
  return heap;
}


uint32_t alloc(uint32_t size,struct Heap* heap){
  int required_blocks = size/HEAP_BLOCK_SIZE;
  int additional = size%HEAP_BLOCK_SIZE;
  if(additional!=0){
    required_blocks++;
  }
  int n_entries = (heap->size) / HEAP_BLOCK_SIZE;
  uint32_t start_address = 0;
  int startEntry = 0;
  int count = 0;
  for(int i=0;i<n_entries;i++){
    if(count==required_blocks){
      break;
    }
    if(heap->entries[i]==FREE){
      if(count==0){
        startEntry = i;
        start_address = (heap->start_address+(i*HEAP_BLOCK_SIZE));
      }
      count++;
    }else{
      count = 0;
      startEntry = 0;
      start_address = 0;
    }
  }
  if(count==required_blocks){
    for(int i=startEntry;i<count;i++){
      heap->entries[startEntry] = USED;
    }
    return start_address;
  }
  return 0x0;
}

