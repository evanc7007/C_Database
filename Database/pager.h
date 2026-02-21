#ifndef PAGER_H
#define PAGER_H

#include "common.h"
#include "constants.h"

Pager* pager_open(const char*);
void* get_page(Pager*, uint32_t);
void pager_flush(Pager*, uint32_t);
uint32_t get_unused_page_num(Pager*);

#endif /* PAGER_H */
