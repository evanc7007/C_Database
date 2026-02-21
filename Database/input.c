#include "input.h"

InputBuffer* new_input_buffer(){
    InputBuffer *input_buffer = (InputBuffer*)safe_malloc(sizeof(InputBuffer));
    input_buffer->buffer_length = 1024;
    input_buffer->buffer = (char*)safe_malloc(input_buffer->buffer_length);
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt(){
    printf("db > ");
}

void read_input(InputBuffer* input_buffer){
if (fgets(input_buffer->buffer, input_buffer->buffer_length, stdin) == NULL) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Remove trailing newline
    input_buffer->input_length = strlen(input_buffer->buffer);
    if (input_buffer->buffer[input_buffer->input_length - 1] == '\n') {
        input_buffer->buffer[input_buffer->input_length - 1] = '\0';
        input_buffer->input_length--;
    }
    if (input_buffer->input_length > 0 &&
        input_buffer->buffer[input_buffer->input_length - 1] == '\r') {
        input_buffer->buffer[input_buffer->input_length - 1] = '\0';
        input_buffer->input_length--;
    }
}

void close_input_buffer(InputBuffer* input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}
