#include "defines.h"
#include "structure.h"
#include "io.h"
#include <stdio.h>

/**
 * @brief sort_keys_bubble Сортировка пузырьком таблицы ключей по указателям.
 * @param n [in] - количество элементов таблицы ключей
 * @param p_key [in] - указатель на массив указателей на стуктуры (ключи)
 */
void sort_keys_bubble(int n, struct key **p_key)
{
    struct key *tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (p_key[i]->value > p_key[j]->value)
            {
                tmp = p_key[i];
                p_key[i] = p_key[j];
                p_key[j] = tmp;
            }
        }
}

/**
 * @brief sort_keys_cocktail Сортировка Шейкер таблицы ключей по указателям.
 * @param n [in] - количество элементов таблицы ключей
 * @param p_key [in] - указатель на массив указателей на стуктуры (ключи)
 */
void sort_keys_cocktail(int n, struct key **p_key)
{
    struct key *tmp;
    int left = 0, right = n - 1;
    char flag = 1;
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (p_key[i]->value > p_key[i + 1]->value)
            {
                tmp = p_key[i];
                p_key[i] = p_key[i + 1];
                p_key[i + 1] = tmp;
                flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (p_key[i - 1]->value > p_key[i]->value)
            {
                tmp = p_key[i];
                p_key[i] = p_key[i - 1];
                p_key[i - 1] = tmp;
                flag = 1;
            }
        }
        left++;
    }
}

/**
 * @brief sort_keys_bubble2 Сортировка пузырьком таблицы ключей через массив.
 * @param n [in] - количество элементов таблицы ключей
 * @param key [in] - массив стуктур (ключи)
 */
void sort_keys_bubble_2(int n, struct key key[])
{
    struct key locals[n];
    for (int i = 0; i < n; i++)
        locals[i] = key[i];
    struct key tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (locals[i].value > locals[j].value)
            {
                tmp = locals[i];
                locals[i] = locals[j];
                locals[j] = tmp;
            }
        }
}

void sort_keys_cocktail_2(int n, struct key key[])
{
    struct key locals[n];
    for (int i = 0; i < n; i++)
        locals[i] = key[i];
    struct key tmp;
    int left = 0, right = n - 1;
    char flag = 1;
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (locals[i].value > locals[i + 1].value)
            {
                tmp = locals[i];
                locals[i] = locals[i + 1];
                locals[i + 1] = tmp;
                flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (locals[i - 1].value > locals[i].value)
            {
                tmp = locals[i];
                locals[i] = locals[i - 1];
                locals[i - 1] = tmp;
                flag = 1;
            }
        }
        left++;
    }
}

void sort_table_bubble(int n, struct car **p_table)
{
    struct car tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (p_table[i]->price > p_table[j]->price)
            {
                tmp = *p_table[i];
                *p_table[i] = *p_table[j];
                *p_table[j] = tmp;
            }
        }
}

void sort_table_bubble_2(int n, struct car table[])
{
    struct car cars[n];
    for (int i = 0; i < n; i++)
        cars[i] = table[i];
    struct car tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (cars[i].price > cars[j].price)
            {
                tmp = cars[i];
                cars[i] = cars[j];
                cars[j] = tmp;
            }
        }
}



void sort_table_cocktail(int n, struct car cars[])
{
    struct car table[n];
    for (int i = 0; i < n; i++)
        table[i] = cars[i];
    struct car tmp;
    int left = 0, right = n - 1;
    char flag = 1;
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (table[i].price > table[i + 1].price)
            {
                tmp = table[i];
                table[i] = table[i + 1];
                table[i + 1] = tmp;
                flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (table[i - 1].price > table[i].price)
            {
                tmp = table[i];
                table[i] = table[i - 1];
                table[i - 1] = tmp;
                flag = 1;
            }
        }
        left++;
    }
}
