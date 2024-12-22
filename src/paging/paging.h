//
// Created by bulbasaur on 22/12/24.
//
#include <stdint.h>
#include "../heap/kheap.h"
#ifndef PAGING_H
#define PAGING_H
extern void load_page_directory(uint32_t*);
extern void enable_paging();
uint32_t* create_page_directory(struct Heap* kheap);
void init_paging(uint32_t* kernel_page_directory);
void map_directory_to_address(uint32_t* directory,uint32_t virtual_addr,uint32_t phys_addr);
#define PAGING_PRESENT        0b00000001
#define PAGING_WRITABLE       0b00000010
#define PAGING_ALL_ACCESS     0b00000100
#define PAGING_WRITE_THROUGH  0b00001000
#define PAGING_CACHE_DISABLED 0b00010000
#define PAGE_ENTRY_COUNT 1024
//1024*4 bytes = 4096 bytes total of page sizes
#define PAGE_DIRECTORY_SIZE 4096
#define PAGE_TABLE_SIZE 4096
#endif //PAGING_H
