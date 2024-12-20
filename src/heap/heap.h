//
// Created by bulbasaur on 20/12/24.
//

#include <stdint.h>
#ifndef HEAP_H
#define HEAP_H

#define HEAP_BLOCK_SIZE 4096 //4 kb blocks

#define HEAP_STORAGE_LOCATION 0x1000000 //16MB

#define USED 0x1
#define FREE 0x0

struct Heap{
  uint32_t start_address;
  uint32_t size;
  uint8_t* entries;
};

struct Heap* create_heap(uint32_t start_address,uint32_t size);


#endif //HEAP_H
