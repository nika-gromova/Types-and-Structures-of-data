#ifndef IO_H
#define IO_H

#include "my_tree.h"
#include "my_hash_table.h"

int export_to_dot(tree_elem *tree, FILE *f, const char *name);
int read_file(const char *file_name, tree_elem **tree, tree_elem **balanced_tree);
int read_file_hash(const char *file_name, hash_table *table, int *count);
void print_tree(tree_elem *tree);
void print_hash(hash_table table);
int count_elements(const char *file_name, int *count);
int search_in_file(const char *file, const char *searching, int *count_cmp);

#endif // IO_H
