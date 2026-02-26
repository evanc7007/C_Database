#ifndef BTREE_H
#define BTREE_H

#include "common.h"
#include "constants.h"

/**
 * Accessor for number of cells in a leaf node
 * 
 * @param node a node in the table
 * @return the pointer pointing to the memory
 *  in the node storing number of cells
 */
uint32_t* leaf_node_num_cells(void* node);

/**
 * Accessor for a specific cell in a leaf node
 * 
 * @param node a node in the table
 * @param cell_num which cell to retrieve
 * @return the pointer pointing to memory
 *  in the node for the cell_numth cell
 */
void* leaf_node_cell(void* node, uint32_t cell_num);

/**
 * Accessor for the key for a cell in a leaf node
 * 
 * @param node a node in the table
 * @param cell_num which cell to retrieve key for
 * @return the pointer pointing to memory
 *  in the node for the cell_numth cell's key
 */
uint32_t* leaf_node_key(void* node, uint32_t cell_num);

/**
 * Accessor for the value for a cell in a leaf node
 * 
 * @param node a node in the table
 * @param cell_num which cell to retrieve value for
 * @return the pointer pointing to memory
 *  in the node for the cell_numth cell's value
 */
void* leaf_node_value(void* node, uint32_t cell_num);

/**
 * Initializer for a new leaf node
 * 
 * @param node a node to initialize
 */
void initialize_leaf_node(void* node);

/**
 * Initializer for a new internal node
 * 
 * @param node a node to initialize
 */
void initialize_internal_node(void* node);

/**
 * Insert a key value pair into a leaf node
 * 
 * @param cursor cursor to where the pair should be inserted
 * @param key the key to insert
 * @param value a type row to insert along with key
 */
void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);

/**
 * Delete a cell from a leaf node by shifting all following
 * cells left to overwrite it, then decrementing the cell count
 *
 * @param node the leaf node to delete from
 * @param cell_num the index of the cell to delete
 */
void leaf_node_delete(void* node, uint32_t cell_num);

/**
 * Prints constants of interest
 */
void print_constants();

/**
 * Use binary search to search for the key in the leaf node
 * 
 * @param table the table
 * @param page_num the page to search in
 * @param key key to search for
 * @return Cursor pointing to the position of the key,
 *  position of another key to move, or
 *  one past the last key
 */
Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t key);

/**
 * Accessor for the node type
 * 
 * @param node a node
 * @return NodeType stating if it is internal node or leaf
 */
NodeType get_node_type(void* node);

/**
 * set the node type for the node
 * 
 * @param node the node
 * @param type either internal or leaf
 */
void set_node_type(void* node, NodeType type);

/**
 * Create a new node and move half the cells over.
 * Insert the new value in one of the two nodes
 * Update parent or create a new parent.
 * 
 * @param cursor cursor pointing to the node
 * @param key key to add
 * @param value value to add
 */
void leaf_node_split_and_insert(Cursor* cursor, uint32_t key, Row* value);

/**
 * Create a new root by splitting,
 * old root is copied to new page becoming left child
 * and point to right child
 * 
 * @param table the table
 * @param right_child_page_num page number of the new right child
 */
void create_new_root(Table* table, uint32_t right_child_page_num);

/**
 * Accessor for number of keys in an internal node
 * 
 * @param node a node in the table
 * @return the pointer pointing to the memory
 *  in the node storing number of keys
 */
uint32_t* internal_node_num_keys(void* node);

/**
 * Accessor for rightmost child in an internal node
 * 
 * @param node a node in the table
 * @return the pointer pointing to the memory
 *  in the node for the rightmost child
 */
uint32_t* internal_node_right_child(void* node);

/**
 * Accessor for the cell_numth cell in the node
 * 
 * @param node a node in the table
 * @param cell_num the index to access
 * @return the pointer pointing to the memory
 *  in the node for the cell_numth cell
 */
uint32_t* internal_node_cell(void* node, uint32_t cell_num);

/**
 * Accessor for the child_numth child in the node
 * 
 * @param node a node in the table
 * @param child_num the index to access
 * @return the pointer pointing to the memory
 *  in the node for the child_numth child
 */
uint32_t* internal_node_child(void* node, uint32_t child_num);

/**
 * Accessor for the key_numth key in the node
 * 
 * @param node a node in the table
 * @param key_num the index to access
 * @return the pointer pointing to the memory
 *  in the node for the key_numth key
 */
uint32_t* internal_node_key(void* node, uint32_t key_num);

/**
 * find the maximum key in any subtree
 * 
 * @param pager the pager
 * @param node the node
 * @return the largest key in the subtree
 */
uint32_t get_node_max_key(Pager* pager, void* node);

/**
 * @param node the node to check
 * @return if the node is a root node
 */
bool is_node_root(void* node);

/**
 * set the node to be root or not
 * 
 * @param node the node
 * @param is_root what to set to
 */
void set_node_root(void* node, bool is_root);

/**
 * indent for print
 * 
 * @param level level of indentation
 */
void indent(uint32_t level);

/**
 * Prints out a representation of the btree
 * 
 * @param pager the pager
 * @param page_num root of the printed tree
 * @param indentation_level how much to indent
 */
void print_tree(Pager* pager, uint32_t page_num, uint32_t indentation_level);

/**
 * return index of child which should contain key using binary search
 * 
 * @param node the node
 * @param key the key to search for
 * @return index of child with key
 */
uint32_t internal_node_find_child(void* node, uint32_t key);

/**
 * finds child that should contain given key using binary search
 * 
 * @param table the table
 * @param page_num page number to start at
 * @param key key to find
 * @return a cursor pointing to the search result
 */
Cursor* internal_node_find(Table* table, uint32_t page_num, uint32_t key);

/**
 * Access the pointer to the next leaf node
 * 
 * @param node the node to find the next leaf for
 * @return the memory where the pointer to next leaf is stored
 */
uint32_t* leaf_node_next_leaf(void* node);

/**
 * Access the pointer to the parent node
 * 
 * @param node the node to find the parent for
 * @return the memory where the pointer to parent is stored
 */
uint32_t* node_parent(void* node);

/**
 * replace key in internal node with a new value
 * 
 * @param node the node
 * @param old_key the key to change
 * @param new_key the new key to display
 */
void update_internal_node_key(void* node, uint32_t old_key, uint32_t new_key);

/**
 * Split a internal node into two and insert a new child.
 * Upper half of keys are moved to a new node, new child is inserted
 * into whichever node its key belongs in, and the parent is updated.
 * If the root is split, a new root is created.
 *
 * @param table the table
 * @param parent_page_num page number of the full internal node to split
 * @param child_page_num page number of the new child to insert
 */
void internal_node_split_and_insert(Table* table, uint32_t parent_page_num, uint32_t child_page_num);

/**
 * add new child key pair to parent that corresponds to child
 * 
 * @param table the table
 * @param parent_page_num the page number of parent
 * @param child_page_num the child's page number
 */
void internal_node_insert(Table* table, uint32_t parent_page_num, uint32_t child_page_num);

#endif /* BTREE_H */
