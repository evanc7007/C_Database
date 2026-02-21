#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>

#ifndef O_BINARY
#define O_BINARY 0
#endif

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
#define TABLE_MAX_PAGES 100
#define INVALID_PAGE_NUM UINT32_MAX


/**
 * pager to access page cache and the external file
 */
typedef struct{
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

/**
 * a table with a pager and keeps track of B-tree's root node in the pager's page array
 */
typedef struct{
    Pager* pager;
    uint32_t root_page_num;
} Table;

/**
 * buffer to read input into
 */
typedef struct{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

/**
 * success value of an execution
 */
typedef enum{
    EXECUTE_SUCCESS,
    EXECUTE_DUPLICATE_KEY,
    EXECUTE_TABLE_FULL,
    EXECUTE_KEY_NOT_FOUND
} ExecuteResult;

/**
 * enum for differentiation between recognized meta commands and unrecognized
 */
typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

/**
 * enum for the different types of "exceptions" for a statement
 */
typedef enum{
    PREPARE_SUCCESS,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

/**
 * different types of statements implemented
 */
typedef enum{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_DELETE
} StatementType;

/**
 * stores each row of the table
 */
typedef struct{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

/**
 * a statement
 */
typedef struct{
    StatementType type;
    Row row_to_insert; // only used by insert statement
} Statement;

typedef struct{
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table; //indicates position one past the last element
} Cursor;

typedef enum{
    NODE_INTERNAL,
    NODE_LEAF
} NodeType;

/**
 * wrapper around malloc that makes sure of proper malloc
 * 
 * @param size size to malloc
 * @return a pointer to the allocation
 */
void* safe_malloc(size_t size);

#endif /* COMMON_H */
