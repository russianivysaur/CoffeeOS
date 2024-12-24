//
// Created by bulbasaur on 24/12/24.
//
#include <stdint.h>
#include "drivers/ata/ata.h"
#ifndef FAT16_H
#define FAT16_H

struct BiosParameterBlock{
  uint64_t oem_identifier;
  uint16_t bytes_per_sector;
  uint8_t sectors_per_clustor;
  uint16_t reserved_sectors;
  uint8_t fat_count;
  uint16_t root_directory_count;
  uint16_t total_sectors;
  uint8_t media_descriptor_type;
  uint16_t sectors_per_fat;
  uint16_t sectors_per_track;
  uint16_t number_of_heads;
  uint32_t number_of_hidden_sectors;
  uint32_t large_sector_count;
};

#endif //FAT16_H
