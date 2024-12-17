//
// Created by bulbasaur on 17/12/24.
//

#include "idt.h"
#include <stdint.h>
#include "../stdlib/stdlib.h"

struct IDTDescriptor descriptors[INTERRUPT_COUNT];
struct IDTRDescriptor idtr;

void add_interrupt(uint16_t offset,void* handler_address){
  struct IDTDescriptor* descriptor = &descriptors[offset];
  descriptor -> offset_lower = (uint16_t) (((uint32_t)handler_address) & 0x0000ffff);
  descriptor -> segment_selector = 0x08; //kernel ka
  descriptor -> reserved = 0x0;
  descriptor -> flags = 0x8E;
  descriptor -> offset_higher =(uint16_t) (((uint32_t) handler_address) >> 16);
}

extern void load_idt(struct IDTRDescriptor*);

void init_idtr(){
  memset(descriptors,0,sizeof(descriptors));
  idtr.size = sizeof(descriptors) - 1;
  idtr.offset = (uint32_t) descriptors;
  load_idt(&idtr);
}