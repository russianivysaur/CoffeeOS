//
// Created by bulbasaur on 18/12/24.
//

#include "gdt.h"
extern void load_gdt(uint32_t);
struct GDTRDescriptor gdtr_descriptor;
struct GDTDescriptor gdt_descriptors[DESCRIPTOR_COUNT];

void set_gdt_descriptor(uint16_t limit_1,uint16_t base_1,uint8_t base_2,uint8_t access_byte,
                        uint8_t limit_2_flags,uint8_t base_3,unsigned int offset){
  gdt_descriptors[offset].limit_1 = limit_1;
  gdt_descriptors[offset].base_1 = base_1;
  gdt_descriptors[offset].base_2 = base_2;
  gdt_descriptors[offset].access_byte = access_byte;
  gdt_descriptors[offset].limit_2_flags = limit_2_flags;
  gdt_descriptors[offset].base_3 = base_3;
}



void init_gdt(){
  //set null segment
  set_gdt_descriptor(0,0,0,0,0,0,0);

  //code seg
  set_gdt_descriptor(0xffff,0x0,0x0,0x9a,0xcf,0x0,1);

  //data seg
  set_gdt_descriptor(0xffff,0x0,0x0,0x92,0xcf,0x0,2);
  gdtr_descriptor.size = sizeof(gdt_descriptors) - 1;
  gdtr_descriptor.offset = (uint32_t) &gdt_descriptors;
  load_gdt((uint32_t) &gdtr_descriptor);
}