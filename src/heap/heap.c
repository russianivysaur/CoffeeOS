//
// Created by bulbasaur on 20/12/24.
//

#include "heap.h"
#include "../stdlib/stdlib.h"
#include "../kernel/kernel.h"
#include <stdbool.h>

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


uint32_t* alloc(uint32_t size,struct Heap* heap){
  int required_blocks = size/HEAP_BLOCK_SIZE;
  int additional = size%HEAP_BLOCK_SIZE;
  if(additional!=0){
    required_blocks++;
  }


  int n_entries = (heap->size) / HEAP_BLOCK_SIZE;
  uint32_t* start_address = 0;
  int startEntry = 0;
  int count = 0;
  for(int i=0;i<n_entries;i++){
    if(count==required_blocks){
      break;
    }
    if(heap->entries[i]==FREE){
      if(count==0){
        startEntry = i;
        start_address = (uint32_t*)(heap->start_address+(i*HEAP_BLOCK_SIZE));
      }
      count++;
    }else{
      count = 0;
      startEntry = 0;
      start_address = 0;
    }
  }
  //1st bit tells if block is used
  // 2nd bit tells if the block is first
  // 3rd bit tells if the block is last
  // 4th bit tells if next block is used
  // 0x0 if not used
  if(count==required_blocks && count==1){
    heap->entries[startEntry] |= (FIRST | LAST | USED);
    return start_address;
  }
  if(count==required_blocks){
    heap->entries[startEntry] |= (FIRST | NEXT | USED);
    for(int i=1;i<count-1;i++){
      heap->entries[startEntry + i] |= (USED | NEXT);
    }
    heap->entries[startEntry+count-1] |= (USED | LAST);
    return start_address;
  }
  return 0x0;
}

bool is_aligned(uint32_t address){
  return (address % HEAP_BLOCK_SIZE) == 0;
}


void free(uint32_t* address,struct Heap* heap){
  bool res = is_aligned((uint32_t)address);
  if(!res){
    return;
  }
  uint32_t add = (uint32_t)address;
  int start_entry_index = (add - heap->start_address) / HEAP_BLOCK_SIZE;
  bool is_first = (heap->entries[start_entry_index] & FIRST) == FIRST;
  if(!is_first){
    return;
  }
  bool is_used = (heap->entries[start_entry_index] & USED) == USED;
  while(is_used){
    if((heap->entries[start_entry_index]&LAST)==LAST){
        heap->entries[start_entry_index] = FREE;
        start_entry_index++;
        break;
    }
    heap->entries[start_entry_index] = FREE;
    start_entry_index++;
    is_used = (heap->entries[start_entry_index] & USED) == USED;
  }
  return;
}
