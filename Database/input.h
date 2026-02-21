#ifndef INPUT_H
#define INPUT_H

#include "common.h"

/**
 * Initializes a new InputBuffer
 * 
 * @return a InputBuffer* that is initialized with buffer set to NULL
 */
InputBuffer* new_input_buffer();

/**
 * prompt for the REPL loop
 */
void print_prompt();

/**
 * read input from stdin and writes to InputBuffer, removing trailing newlin
 * 
 * @param input_buffer a InputBuffer* to write into
 */
void read_input(InputBuffer* input_buffer);

/**
 * Destructor for InputBuffer
 * 
 * @param input_buffer an InputBuffer to be freed
 */
void close_input_buffer(InputBuffer* input_buffer);

#endif /* INPUT_H */
