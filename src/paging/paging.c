#include "paging.h"
#include "../heap/kheap.h"

static uint32_t* curr_directory;

uint32_t* create_directory(){
  uint8_t flags = 0x0 | PAGE_PRESENT | PAGE_WRITABLE | PAGE_ALL_ACCESS;
  uint32_t* directory = kzalloc(sizeof(uint32_t) * PAGE_ENTRY_COUNT);
  uint32_t offset = 0;
  for(int directory_offset=0;directory_offset<PAGE_ENTRY_COUNT;directory_offset++){
    uint32_t* table = kzalloc(sizeof(uint32_t) * PAGE_ENTRY_COUNT);
    for(int table_offset=0;table_offset<PAGE_ENTRY_COUNT;table_offset++){
      table[table_offset] = (uint32_t) (offset + (table_offset*PAGE_SIZE)) | flags;
    }
    offset += (PAGE_SIZE * PAGE_ENTRY_COUNT);
    directory[directory_offset] = ((uint32_t)table) | flags;
  }
  return directory;
}

void switch_directory(uint32_t* directory){
  curr_directory = directory;
}

void init_paging(){
  load_page_directory(curr_directory);
  enable_paging();
}

void map_vaddr(uint32_t* directory,void* v_addr,uint32_t p_addr){
  uint32_t directory_index = (uint32_t)v_addr / (PAGE_ENTRY_COUNT * PAGE_SIZE);
  uint32_t table_index = ((uint32_t)v_addr % (PAGE_ENTRY_COUNT * PAGE_SIZE)) / PAGE_SIZE;
  uint32_t entry = directory[directory_index];
  uint32_t *table = (uint32_t *)(entry & 0xfffff000);
  uint8_t flags = 0x0 | PAGE_PRESENT | PAGE_WRITABLE | PAGE_ALL_ACCESS;
  table[table_index] = p_addr | flags;
}