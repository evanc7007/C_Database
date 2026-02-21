#ifndef PAGER_H
#define PAGER_H

#include "common.h"
#include "constants.h"

/**
 * opens database file and keeps track of of its size
 * initializes page cache to all NULL
 * 
 * @param filename database file to open
 * @return initialized Pager
 */
Pager* pager_open(const char* filename);

/**
 * gets the page from the pager, handles cache miss
 * 
 * @param pager the pager
 * @param page_num the page number to fetch
 * 
 * @return a page
 */
void* get_page(Pager* pager, uint32_t page_num);

/**
 * flush page cache to disk
 * 
 * @param pager the pager
 * @param page_num the page to flush
 */
void pager_flush(Pager* pager, uint32_t page_num);

/**
 * get an unused page
 * 
 * @param pager the pager
 * 
 * @return a page number is isn't used
 */
uint32_t get_unused_page_num(Pager* pager);

#endif /* PAGER_H */
