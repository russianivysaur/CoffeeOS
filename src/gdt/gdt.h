//
// Created by bulbasaur on 18/12/24.
//
#include <stdint.h>
#ifndef GDT_H
#define GDT_H
#define DESCRIPTOR_COUNT 3

struct GDTDescriptor {
  uint16_t limit_1;
  uint16_t base_1;
  uint8_t base_2;
  uint8_t access_byte;
  uint8_t limit_2_flags;
  uint8_t base_3;
} __attribute__((packed));

struct GDTRDescriptor{
    uint16_t size;
    uint32_t offset;
}__attribute__((packed));


void init_gdt();
#endif //GDT_H