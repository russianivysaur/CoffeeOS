//
// Created by bulbasaur on 17/12/24.
//
#include <stddef.h>
#include <stdint.h>
#ifndef STDLIB_H
#define STDLIB_H
void memset(void* dst,int c,size_t len);
void itoa(int,uint8_t*);
uint32_t kalloc(uint32_t length);
void kfree(void* address,uint32_t length);
#endif //STDLIB_H
