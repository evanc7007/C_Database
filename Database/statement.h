#ifndef STATEMENT_H
#define STATEMENT_H

#include "common.h"

/**
 * wrapper to handle the different meta commands
 * 
 * @param input_buffer an InputBuffer
 * @param table the current table
 * 
 * @return a MetaCommandResult indicating if the meta command was executed
 * properly or if it is unrecognized. exits the program on .exit
 */
MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);

/**
 * prepares for insert by preparing a row to insert
 * 
 * @param input_buffer the InputBuffer
 * @param statement the statement to be prepared
 * @return PrepareResult the success value of this function
 */
PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);

/**
 * prepares for delete by parsing the id to delete
 * 
 * @param input_buffer the InputBuffer
 * @param statement the statement to be prepared
 * @return PrepareResult the success value of this function
 */
PrepareResult prepare_delete(InputBuffer* input_buffer, Statement* statement);

/**
 * determines which statement is being run and prepares it
 * 
 * @param input_buffer an InputBuffer
 * @param statement the statement that determines the type of statement
 * @return  a PrepareResult stating if it was successful
 */
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

/**
 * executes an insert into the table if it is not a duplicate key
 * 
 * @param statement a statement including the row to insert
 * @param table the table to insert to
 * 
 * @return ExecuteResult on if the execute was successful
 */
ExecuteResult execute_insert(Statement* statement, Table* table);

/**
 * executes select and prints every row from the table
 * 
 * @param statement a statement
 * @param table the table to run select on
 * 
 * @return EXECUTE_SUCCESS on success
 */
ExecuteResult execute_select(Statement*, Table*);

/**
 * executes a delete from the table if the key exists
 * 
 * @param statement a statement including the row to delete
 * @param table the table to delete from
 * 
 * @return ExecuteResult on if the execute was successful
 */
ExecuteResult execute_delete(Statement*, Table*);

/**
 * determines which statement is getting executed and executes it
 * 
 * @param statement the statement that determines the type of statement
 * @param table a table to execute the statement on
 * @return a ExecuteResult stating if it was successful
 */
ExecuteResult execute_statement(Statement* statement, Table* table);

#endif /* STATEMENT_H */
