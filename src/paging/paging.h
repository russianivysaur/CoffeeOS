//
// Created by bulbasaur on 21/12/24.
//
#include <stdint.h>
#ifndef PAGING_H
#define PAGING_H
void extern load_page_directory(uint32_t*);
void init_paging();
#endif //PAGING_H
