#ifndef MY_HASH_TABLE_H
#define MY_HASH_TABLE_H

#include "defines.h"

typedef struct table_n
{
    char word[MAX_STR_LEN + 1];
    struct table_n *next;
} t_node;

typedef struct table
{
    t_node **array;
    int size;
} hash_table;


int generate_simple(int num);
t_node *create_list_elem(const char *word);
void create_table(hash_table *table, int size);
int insert_hash_table(hash_table *table, t_node *element);
int restruct_hash_table(hash_table *table);
void free_hash_table(hash_table *table);
t_node *search_hash(hash_table *table, const char *word, int *count_cmp);

#endif // MY_HASH_TABLE_H
