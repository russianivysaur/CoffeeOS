//
// Created by bulbasaur on 17/12/24.
//

#include "idt.h"
#include <stdint.h>
#include "../stdlib/stdlib.h"

struct IDTDescriptor idt_descriptors[INTERRUPT_COUNT];
struct IDTRDescriptor idtr;

void add_interrupt(uint16_t offset,void* handler_address){
  struct IDTDescriptor* descriptor = &idt_descriptors[offset];
  descriptor -> offset_lower = (uint16_t) (((uint32_t)handler_address) & 0x0000ffff);
  descriptor -> segment_selector = 0x10; //kernel ka
  descriptor -> reserved = 0x0;
  descriptor -> flags = 0x8E;
  descriptor -> offset_higher =(uint16_t) (((uint32_t) handler_address) >> 16);
}

extern void load_idt(struct IDTRDescriptor*);

void init_idt(){
  memset(idt_descriptors,0,sizeof(idt_descriptors));
  idtr.size = sizeof(idt_descriptors) - 1;
  idtr.offset = (uint32_t) idt_descriptors;
  load_idt(&idtr);
}