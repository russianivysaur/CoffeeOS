#include <stdint.h>
#ifndef PAGING_H
#define PAGING_H
extern void load_page_directory(uint32_t*);
extern void enable_paging();
uint32_t* create_directory();
void switch_directory(uint32_t* directory);
void init_paging();
void map_vaddr(uint32_t* directory,void* v_addr,uint32_t p_addr);
#define PAGE_PRESENT       0b00000001
#define PAGE_WRITABLE      0b00000010
#define PAGE_ALL_ACCESS    0b00000100

#define PAGE_ENTRY_COUNT 1024
#define PAGE_SIZE 4096

#endif