//
// Created by bulbasaur on 17/12/24.
//
#include <stdint.h>
#ifndef IDT_H
#define IDT_H

#define INTERRUPT_COUNT 100

void add_interrupt(uint16_t,void*);
void init_idtr();

//table descriptor
struct IDTRDescriptor{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

//entry descriptor 8 bytes
struct IDTDescriptor{
  uint16_t offset_lower;
  uint16_t segment_selector;
  uint8_t reserved;
  uint8_t flags;
  uint16_t offset_higher;
}  __attribute__((packed));
#endif //IDT_H
