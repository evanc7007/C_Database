#ifndef STATEMENT_H
#define STATEMENT_H

#include "common.h"

MetaCommandResult do_meta_command(InputBuffer*, Table*);
PrepareResult prepare_insert(InputBuffer*, Statement*);
PrepareResult prepare_delete(InputBuffer*, Statement*);
PrepareResult prepare_statement(InputBuffer*, Statement*);
ExecuteResult execute_insert(Statement*, Table*);
ExecuteResult execute_select(Statement*, Table*);
ExecuteResult execute_delete(Statement*, Table*);
ExecuteResult execute_statement(Statement*, Table*);

#endif /* STATEMENT_H */
