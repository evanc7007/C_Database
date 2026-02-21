#ifndef CURSOR_H
#define CURSOR_H

#include "common.h"

Cursor* table_start(Table*);
Cursor* table_find(Table*, uint32_t);
void cursor_advance(Cursor*);
void* cursor_value(Cursor*);

#endif /* CURSOR_H */
