//
// Created by bulbasaur on 24/12/24.
//

#include "fat16.h"
#include "heap/kheap.h"

struct BiosParameterBlock read_bpb(){
  uint8_t* buffer = (uint8_t*)kzalloc(100);
  lba_read(0,1,(uint16_t*)buffer);
  struct BiosParameterBlock block;
  block.oem_identifier = 0;
  block.bytes_per_sector = 0;
  block.sectors_per_clustor = 0;
  block.reserved_sectors = 0;
  block.fat_count = 0;
  block.root_directory_count = 0;
  block.total_sectors = 0;
  block.media_descriptor_type = 0;
  block.sectors_per_fat = 0;
  block.sectors_per_track = 0;
  block.number_of_heads = 0;
  block.number_of_hidden_sectors = 0;
  block.large_sector_count = 0;
  return block;
}