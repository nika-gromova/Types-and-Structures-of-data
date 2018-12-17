#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_hash_table.h"

// Функции для генерирования простых чисел

int is_simple(int num)
{
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

int generate_simple(int num)
{
    for (int i = 1;; i++)
    {
        if (i > num)
        {
            if (is_simple(i))
                return i;
        }
    }
    return 0;
}

// Функции для освобождения памяти из-под хэш-таблицы

void free_list(t_node *head)
{
    t_node *tmp;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

void free_hash_table(hash_table *table)
{
    if (table->array == NULL)
        return;
    for (int i = 0; i < table->size; i++)
        free_list(table->array[i]);
    free(table->array);
    table->array = NULL;
}

// Функции для добавления элемента в хэш-таблицу

t_node *create_list_elem(const char *word)
{
    t_node *in = malloc(sizeof(t_node));
    if (in)
    {
        strcpy(in->word, word);
        in->next = NULL;
    }
    return in;
}

void create_table(hash_table *table, int size)
{
    table->array = calloc(size, sizeof(t_node *));
    if (table->array)
        table->size = size;
    else
        table->size = 0;
}

int get_index(const char *word, int size)
{
    if (word == NULL)
        return 0;
    int sum = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        sum += (int)(word[i]);
    }
    return sum % size;
}

t_node *add_to_tail(t_node *head, t_node *element)
{
    if (head == NULL)
        return element;
    t_node *cur = head;
    while (cur->next)
        cur = cur->next;
    cur->next = element;
    return head;
}

int insert_hash_table(hash_table *table, t_node *element)
{
    int index = get_index(element->word, table->size);
    if (table->array[index] == NULL)
    {
        table->array[index] = element;
        return 0;
    }
    else
    {
        table->array[index] = add_to_tail(table->array[index], element);
    }
    return 1;
}

int restruct_hash_table(hash_table *table)
{
    int new_size = generate_simple(table->size);
    t_node *tmp_array = malloc(table->size * sizeof(t_node));
    t_node *cur = NULL;
    int j = 0;
    int count = 0;
    if (tmp_array)
    {
        for (int i = 0; i < table->size && j < table->size; i++)
        {
            cur = table->array[i];
            while (cur)
            {
                tmp_array[j] = *cur;
                cur = cur->next;
                j++;
            }
        }
        free_hash_table(table);
        create_table(table, new_size);
        if (table->size != 0)
        {
            for (int i = 0; i < j && count >= 0; i++)
            {
                cur = create_list_elem(tmp_array[i].word);
                if (cur)
                {
                    count += insert_hash_table(table, cur);
                }
                else
                {
                    free_hash_table(table);
                    count = -1;
                }
            }
        }
        else
            count = -1;
    }
    else
        count = -1;
    return count;
}


t_node *search_hash(hash_table *table, const char *word, int *count_cmp)
{
    *count_cmp = 0;
    if (table->array == NULL)
        return NULL;
    int index = get_index(word, table->size);
    t_node *cur;
    cur = table->array[index];

    if (cur == NULL)
    {
        (*count_cmp)++;
        return NULL;
    }
    while (cur)
    {
        (*count_cmp)++;
        if (strcmp(cur->word, word) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}
