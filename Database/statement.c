#include "statement.h"
#include "btree.h"
#include "cursor.h"
#include "table.h"
#include "row.h"
#include "input.h"
#include "pager.h"
#include "constants.h"

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table){
    if(strcmp(input_buffer->buffer, ".exit") == 0){
        db_close(table);
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else if(strcmp(input_buffer->buffer, ".help") == 0){
        printf("Commands:\n");
        printf("  .exit       - Close the database and exit\n");
        printf("  .btree      - Print the B-tree structure\n");
        printf("  .constants  - Print internal constants\n");
        printf("  .help       - Show this help\n");
        printf("SQL:\n");
        printf("  insert <id> <username> <email> - Insert a row\n");
        printf("  select                         - Print all rows\n");
        printf("  delete <id>                    - Delete a row\n");
        return META_COMMAND_SUCCESS;
    } else if(strcmp(input_buffer->buffer, ".btree") == 0){
        printf("Tree:\n");
        print_tree(table->pager, 0, 0);
        return META_COMMAND_SUCCESS;
    } else if(strcmp(input_buffer->buffer, ".constants") == 0){
        printf("Constants:\n");
        print_constants();
        return META_COMMAND_SUCCESS;
    } else{
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement){
    statement->type = STATEMENT_INSERT;

    char* keyword = strtok(input_buffer->buffer, " ");
    char* id_string = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");

    if(id_string == NULL || username == NULL || email == NULL){
        return PREPARE_SYNTAX_ERROR;
    }

    int id = atoi(id_string);
    if(id < 0){
        return PREPARE_NEGATIVE_ID;
    }
    if(strlen(username) > COLUMN_USERNAME_SIZE){
        return PREPARE_STRING_TOO_LONG;
    }
    if(strlen(email) > COLUMN_EMAIL_SIZE){
        return PREPARE_STRING_TOO_LONG;
    }

    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}

PrepareResult prepare_delete(InputBuffer* input_buffer, Statement* statement){
    statement->type = STATEMENT_DELETE;

    char* keyword = strtok(input_buffer->buffer, " ");
    char* id_string = strtok(NULL, " ");

    if(id_string == NULL){
        return PREPARE_SYNTAX_ERROR;
    }

    int id = atoi(id_string);
    if(id < 0){
        return PREPARE_NEGATIVE_ID;
    }

    statement->row_to_insert.id = id;

    return PREPARE_SUCCESS;
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement){
    if(strncasecmp(input_buffer->buffer, "insert", 6) == 0){
        return prepare_insert(input_buffer, statement);
    }
    if(strncasecmp(input_buffer->buffer, "delete", 6) == 0){
        return prepare_delete(input_buffer, statement);
    }
    if(strcasecmp(input_buffer->buffer, "select") == 0){
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult execute_insert(Statement* statement, Table* table){
    Row* row_to_insert = &(statement->row_to_insert);
    uint32_t key_to_insert = row_to_insert->id;
    Cursor* cursor = table_find(table, key_to_insert);

    void* node = get_page(table->pager, cursor->page_num);
    uint32_t num_cells = (*leaf_node_num_cells(node));

    if(cursor->cell_num < num_cells){
        uint32_t key_at_index = *leaf_node_key(node, cursor->cell_num);
        if(key_at_index == key_to_insert){
            free(cursor);
            return EXECUTE_DUPLICATE_KEY;
        }
    }

    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

    free(cursor);

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table){
    Cursor* cursor = table_start(table);

    Row row;

    while(!(cursor->end_of_table)){
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }

    free(cursor);

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_delete(Statement* statement, Table* table){
    uint32_t key = statement->row_to_insert.id;
    Cursor* cursor = table_find(table, key);

    void* node = get_page(table->pager, cursor->page_num);
    uint32_t num_cells = *leaf_node_num_cells(node);

    if(cursor->cell_num >= num_cells ||
       *leaf_node_key(node, cursor->cell_num) != key){
        free(cursor);
        return EXECUTE_KEY_NOT_FOUND;
    }

    leaf_node_delete(node, cursor->cell_num);

    free(cursor);

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table){
    switch(statement->type){
        case (STATEMENT_INSERT):
            return execute_insert(statement, table);
        case (STATEMENT_SELECT):
            return execute_select(statement, table);
        case (STATEMENT_DELETE):
            return execute_delete(statement, table);
    }
}
