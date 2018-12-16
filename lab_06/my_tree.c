#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my_tree.h"

#define MAX(num1, num2) ((num1) > (num2) ? (num1) : (num2))
tree_elem *create_node_tree(const char *word)
{
    tree_elem *in = malloc(sizeof(tree_elem));
    if (in)
    {
        strcpy(in->word, word);
        in->height = 0;
        in->left = NULL;
        in->right = NULL;
    }
    return in;
}

tree_elem *insert(tree_elem *tree, tree_elem *element)
{
    int tmp;
    if (tree == NULL)
        return element;
    tmp = strcmp(tree->word, element->word);
    if (tmp > 0)
    {
        tree->left = insert(tree->left, element);
    }
    else if (tmp < 0)
    {
        tree->right = insert(tree->right, element);
    }
    return tree;
}

tree_elem *search(tree_elem *tree, const char *word)
{
    int tmp;
    while (tmp)
    {
        tmp = strcmp(tree->word, word);
        if (tmp == 0)
            return tree;
        if (tmp > 0)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return NULL;
}

void apply_pre(tree_elem *tree, void(*f)(tree_elem *, void*), void *arg)
{
    if (tree == NULL)
        return;
    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

int height(tree_elem *tree)
{
    int h1 = 0, h2 = 0;
    if (tree == NULL)
        return 0;
    if (tree->left)
    {
        h1 = height(tree->left);
    }
    if (tree->right)
    {
        h2 = height(tree->right);
    }
    return (MAX(h1, h2) + 1);
}

unsigned int get_height(tree_elem *node)
{
    return (node ? node->height : 0);
}

int bfactor(tree_elem *node)
{
    return get_height(node->right) - get_height(node->left);
}

void fix_hight(tree_elem *node)
{
    int h1 = get_height(node->left);
    int h2 = get_height(node->right);
    node->height = MAX(h1, h2) + 1;
}
