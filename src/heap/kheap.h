//
// Created by bulbasaur on 20/12/24.
//
#include "heap.h"
#ifndef KHEAP_H
#define KHEAP_H
#define KERNEL_HEAP_START 0x1200000 //18 mb - 2 mb reserved for heap descriptor
#define KERNEL_HEAP_SIZE 6400000 //100 mb

void init_kheap();
uint32_t* kalloc(uint32_t);
void kfree(uint32_t*);
uint32_t* kzalloc(uint32_t size);
#endif //KHEAP_H
