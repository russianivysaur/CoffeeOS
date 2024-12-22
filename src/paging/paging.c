//
// Created by bulbasaur on 22/12/24.
//

#include "paging.h"

uint32_t* create_page_directory(struct Heap* kheap){
  uint8_t flags = PAGING_PRESENT | PAGING_WRITABLE | PAGING_ALL_ACCESS;
  uint32_t* directory = (uint32_t*) kzalloc(sizeof(uint32_t) * PAGE_ENTRY_COUNT,kheap);
  int offset = 0;
  for(int directory_offset=0;directory_offset<PAGE_ENTRY_COUNT;directory_offset++){
    uint32_t* page_table = (uint32_t*) kzalloc(sizeof(uint32_t) * PAGE_ENTRY_COUNT,kheap);
    for(int page_offset=0;page_offset<PAGE_ENTRY_COUNT;page_offset++){
      page_table[page_offset] = (uint32_t)(PAGE_TABLE_SIZE * page_offset + (offset)) | flags;
    }
    offset += (PAGE_ENTRY_COUNT * PAGE_TABLE_SIZE);
    directory[directory_offset] = (uint32_t)page_table | flags;
  }
  return directory;
}


void init_paging(uint32_t* kernel_page_directory){
  load_page_directory(kernel_page_directory);
  enable_paging();
}


void map_directory_to_address(uint32_t* directory,uint32_t virtual_addr,uint32_t phys_addr){
  uint8_t flags = PAGING_PRESENT | PAGING_WRITABLE | PAGING_ALL_ACCESS;
  uint32_t directory_offset = virtual_addr / (PAGE_ENTRY_COUNT * PAGE_TABLE_SIZE);
  uint32_t table_offset = virtual_addr % (PAGE_ENTRY_COUNT * PAGE_TABLE_SIZE) / PAGE_TABLE_SIZE;
  uint32_t pde = directory[directory_offset];
  uint32_t* table = (uint32_t*) (pde & 0xfffff000);
  table[table_offset] = phys_addr | flags;
}