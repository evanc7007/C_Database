#ifndef TABLE_H
#define TABLE_H

#include "common.h"

/**
 * opens a connection to the database
 * initializes pager data structure
 * initializes table data structure
 * 
 * @param filename the file to open
 * @return initialized table
 */
Table* db_open(const char* filename);

/**
 * closes connection to the database
 * flushes page cache
 * frees table and its pager
 * 
 * @param table table to free
 */
void db_close(Table* table);

#endif /* TABLE_H */
