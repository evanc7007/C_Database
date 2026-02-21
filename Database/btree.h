#ifndef BTREE_H
#define BTREE_H

#include "common.h"
#include "constants.h"

uint32_t* leaf_node_num_cells(void*);
void* leaf_node_cell(void*, uint32_t);
uint32_t* leaf_node_key(void*, uint32_t);
void* leaf_node_value(void*, uint32_t);
void initialize_leaf_node(void*);
void initialize_internal_node(void*);
void leaf_node_insert(Cursor*, uint32_t, Row*);
void leaf_node_delete(void*, uint32_t);
void print_constants();
Cursor* leaf_node_find(Table*, uint32_t, uint32_t);
NodeType get_node_type(void*);
void set_node_type(void*, NodeType);
void leaf_node_split_and_insert(Cursor*, uint32_t, Row*);
void create_new_root(Table*, uint32_t);
uint32_t* internal_node_num_keys(void*);
uint32_t* internal_node_right_child(void*);
uint32_t* internal_node_cell(void*, uint32_t);
uint32_t* internal_node_child(void*, uint32_t);
uint32_t* internal_node_key(void*, uint32_t);
uint32_t get_node_max_key(Pager*, void*);
bool is_node_root(void*);
void set_node_root(void*, bool);
void indent(uint32_t);
void print_tree(Pager*, uint32_t, uint32_t);
uint32_t internal_node_find_child(void*, uint32_t);
Cursor* internal_node_find(Table*, uint32_t, uint32_t);
uint32_t* leaf_node_next_leaf(void*);
uint32_t* node_parent(void*);
void update_internal_node_key(void*, uint32_t, uint32_t);
void internal_node_split_and_insert(Table*, uint32_t, uint32_t);
void internal_node_insert(Table*, uint32_t, uint32_t);

#endif /* BTREE_H */
