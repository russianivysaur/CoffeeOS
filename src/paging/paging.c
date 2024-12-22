//
// Created by bulbasaur on 22/12/24.
//

#include "paging.h"

uint32_t* create_page_directory(struct Heap* kheap){
  uint8_t flags = PAGING_PRESENT | PAGING_WRITABLE | PAGING_CACHE_DISABLED | PAGING_ALL_ACCESS;
  uint32_t* directory = (uint32_t*) kzalloc(PAGE_DIRECTORY_SIZE,kheap);
  for(int directory_offset=0;directory_offset<PAGE_ENTRY_COUNT;directory_offset++){
    uint32_t* page_table = (uint32_t*) kzalloc(PAGE_TABLE_SIZE,kheap);
    for(int page_offset=0;page_offset<PAGE_ENTRY_COUNT;page_offset++){
      page_table[page_offset] = (uint32_t)(PAGE_TABLE_SIZE * page_offset + (directory_offset)) | flags;
    }
    directory[directory_offset] = (uint32_t)page_table | flags;
  }
  return directory;
}


uint32_t* init_paging(struct Heap* kheap){
  uint32_t* kernel_page_directory = create_page_directory(kheap);
  load_page_directory(kernel_page_directory);
  enable_paging();
  return kernel_page_directory;
}


void map_directory_to_address(uint32_t* directory,uint32_t virtual_addr,uint32_t phys_addr){
  uint32_t directory_offset = virtual_addr / (PAGE_ENTRY_COUNT * PAGE_TABLE_SIZE);
  uint32_t table_offset = (virtual_addr % (1024*4096) / 4096);
  uint32_t pde = directory[directory_offset];
  uint32_t* table = (uint32_t*) (pde & 0xfffff000);
  table[table_offset] = phys_addr;
}