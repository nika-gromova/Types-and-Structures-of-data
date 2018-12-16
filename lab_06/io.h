#ifndef IO_H
#define IO_H

#include "my_tree.h"

void export_to_dot(tree_elem *tree, FILE *f, const char *name);
int read_file(const char *file_name, tree_elem **tree);

#endif // IO_H
