#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my_tree.h"

#define MAX(num1, num2) ((num1) > (num2) ? (num1) : (num2))

// стандартные функции для бинарного дерева

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

unsigned char get_height(tree_elem *node)
{
    return (node ? node->height : 0);
}

tree_elem *insert(tree_elem *tree, tree_elem *element)
{
    int tmp;
    if (tree == NULL)
    {
        element->height = 1;
        return element;
    }
    tmp = strcmp(tree->word, element->word);
    if (tmp > 0)
    {
        tree->left = insert(tree->left, element);
    }
    else if (tmp < 0)
    {
        tree->right = insert(tree->right, element);
    }
    tree->height = (MAX(get_height(tree->left), get_height(tree->right)) + 1);
    return tree;
}

tree_elem *search_tree(tree_elem *tree, const char *word, int *count_cmp)
{
    int tmp;
    *count_cmp = 0;
    while (tree)
    {
        tmp = strcmp(tree->word, word);
        (*count_cmp)++;
        if (tmp == 0)
            return tree;
        (*count_cmp)++;
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

// Балансировка

int bfactor(tree_elem *node)
{
    return get_height(node->right) - get_height(node->left);
}

void fix_hight(tree_elem *node)
{
    unsigned char h1 = get_height(node->left);
    unsigned char h2 = get_height(node->right);
    node->height = MAX(h1, h2) + 1;
}

tree_elem *rotate_right(tree_elem *node)
{
    tree_elem *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    fix_hight(node);
    fix_hight(tmp);
    return tmp;
}

tree_elem *rotate_left(tree_elem *node)
{
    tree_elem *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    fix_hight(node);
    fix_hight(tmp);
    return tmp;
}

tree_elem *balance(tree_elem *node)
{
    fix_hight(node);
    if (bfactor(node) == 2)
    {
        if (bfactor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if (bfactor(node) == -2)
    {
        if (bfactor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    return node;
}

tree_elem *insert_balanced(tree_elem *tree, tree_elem *element)
{
    int tmp;
    if (tree == NULL)
    {
        element->height = 1;
        return element;
    }
    tmp = strcmp(tree->word, element->word);
    if (tmp > 0)
    {
        tree->left = insert(tree->left, element);
    }
    else if (tmp < 0)
    {
        tree->right = insert(tree->right, element);
    }
    tree->height = (MAX(get_height(tree->left), get_height(tree->right)) + 1);
    return balance(tree);
}

// Освобождение памяти из-под дерева

void free_tree(tree_elem *tree)
{
    if (tree != NULL)
    {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}
