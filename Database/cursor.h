#ifndef CURSOR_H
#define CURSOR_H

#include "common.h"

/**
 * create a cursor positioned at the beginning of the table
 * 
 * @param table a table to initialze to cursor to
 * @return a cursor to the beginning of the table
 */
Cursor* table_start(Table* table);

/**
 * finds position of given key, if not present, return positon where it should be inserted
 * 
 * @param table a table to find the key in
 * @param key the key to find
 * 
 * @return a cursor pointing to position of key or where it should go
 */
Cursor* table_find(Table* table, uint32_t key);

/**
 * advances cursor to the next node in the table
 * 
 * @param cursor a cursor to advance
 */
void cursor_advance(Cursor* cursor);

/**
 * grabs where the cursor points to
 * 
 * @param cursor a cursor
 * @return a pointer to the position described by cursor
 */
void* cursor_value(Cursor* cursor);

#endif /* CURSOR_H */
