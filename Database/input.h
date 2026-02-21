#ifndef INPUT_H
#define INPUT_H

#include "common.h"

InputBuffer* new_input_buffer();
void print_prompt();
void read_input(InputBuffer*);
void close_input_buffer(InputBuffer*);

#endif /* INPUT_H */
