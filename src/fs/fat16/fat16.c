//
// Created by bulbasaur on 24/12/24.
//

#include "fat16.h"
#include "../../heap/kheap.h"

struct BiosParameterBlock* read_bpb(){
  uint8_t* buffer = (uint8_t*)kzalloc(100);
  lba_read(0,1,(uint16_t*)buffer);
  struct BiosParameterBlock* block = (struct BiosParameterBlock*)kzalloc(sizeof(struct BiosParameterBlock));
  block->oem_identifier[0] = buffer[3];
  block->oem_identifier[1] = buffer[4];
  block->oem_identifier[2] = buffer[5];
  block->oem_identifier[3] = buffer[6];
  block->oem_identifier[4] = buffer[7];
  block->oem_identifier[5] = buffer[8];
  block->oem_identifier[6] = buffer[9];
  block->oem_identifier[7] = buffer[10];
  block->bytes_per_sector = (((uint16_t)buffer[12]) << 8) | buffer[11];
  block->sectors_per_clustor = buffer[13];
  block->reserved_sectors = (((uint16_t)buffer[15]) << 8) | buffer[14];
  block->fat_count = buffer[16];
  block->root_directory_count = (((uint16_t)buffer[17]) << 8) | buffer[16];
  block->total_sectors = (((uint16_t)buffer[19]) << 8) | buffer[18];
  block->media_descriptor_type = buffer[20];
  block->sectors_per_fat = (((uint16_t)buffer[22]) << 8) | buffer[21];
  block->sectors_per_track = (((uint16_t)buffer[24]) << 8) | buffer[23];
  block->number_of_heads = (((uint16_t)buffer[26]) << 8) | buffer[25];
  return block;
}


