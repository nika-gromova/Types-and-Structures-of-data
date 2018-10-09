#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>

void sort_keys_bubble(int n, struct key **p_key);
void sort_keys_bubble_2(int n, struct key key[]);
void sort_keys_cocktail(int n, struct key **p_key);
void sort_keys_cocktail_2(int n, struct key key[]);
void sort_table_bubble(int n, struct car **p_table);
void sort_table_cocktail(int n, struct car table[]);
void sort_table_bubble_2(int n, struct car table[]);

#endif // SORTING_H
