//
// Created by bulbasaur on 20/12/24.
//

#include <stdint.h>
#ifndef HEAP_H
#define HEAP_H

#define HEAP_BLOCK_SIZE 4096 //4 kb blocks

//wasting almost 14 mb of space here
#define HEAP_STORAGE_LOCATION 0x1000000 //16MB


//1st bit tells if block is used
#define USED     0b00000001
//2nd bit tells if the block is first
#define FIRST    0b00000010
//3rd bit tells if the block is last
#define LAST     0b00000100
//4th bit tells if next block is used
#define NEXT     0b00001000
//0x0 if not used
#define FREE     0x0

struct Heap{
  uint32_t start_address;
  uint32_t size;
  uint8_t* entries;
};

struct Heap* create_heap(uint32_t start_address,uint32_t size);
void free(uint32_t*,struct Heap*);
uint32_t* alloc(uint32_t size,struct Heap* heap);


#endif //HEAP_H
