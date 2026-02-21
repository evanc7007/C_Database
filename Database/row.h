#ifndef ROW_H
#define ROW_H

#include "common.h"
#include "constants.h"

void print_row(Row*);
void serialize_row(Row*, void*);
void deserialize_row(void*, Row*);

#endif /* ROW_H */
