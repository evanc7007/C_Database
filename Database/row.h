#ifndef ROW_H
#define ROW_H

#include "common.h"
#include "constants.h"

/**
 * prints a row
 * 
 * @param row a row from a table to print
 */
void print_row(Row* row);

/**
 * writes a row into the destination
 * 
 * @param row a row
 * @param destination where to write to
 */
void serialize_row(Row* row, void* destination);

/**
 * reads from source to write into a row
 * 
 * @param source where to read from
 * @param row a row
 */
void deserialize_row(void* source, Row* row);

#endif /* ROW_H */
