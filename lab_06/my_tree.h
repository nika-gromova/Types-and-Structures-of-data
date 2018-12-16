#ifndef MY_TREE_H
#define MY_TREE_H

#include "defines.h"

typedef struct node_tree
{
    char word[MAX_STR_LEN + 1];
    unsigned char height;
    struct node_tree *left;
    struct node_tree *right;
} tree_elem;

void apply_pre(tree_elem *tree, void(*f)(tree_elem *, void*), void *arg);
tree_elem *create_node_tree(const char *word);
tree_elem *insert(tree_elem *tree, tree_elem *element);
tree_elem *search(tree_elem *tree, const char *word);
int height(tree_elem *tree);

#endif // MY_TREE_H
