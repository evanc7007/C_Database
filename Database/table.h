#ifndef TABLE_H
#define TABLE_H

#include "common.h"

Table* db_open(const char*);
void db_close(Table*);

#endif /* TABLE_H */
