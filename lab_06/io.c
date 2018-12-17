#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "io.h"
#include "my_tree.h"
#include "my_hash_table.h"

// Формирование графического представления дерева

void to_dot(tree_elem *tree, void *file)
{
    FILE *f = file;
    //printf("elem: %s\n", tree->word);
    if (tree->left)
    {
        //printf("left %s\n", tree->left->word);
        fprintf(f, "%s -> %s;\n", tree->word, tree->left->word);
    }
    if (tree->right)
    {
        //printf("right %s\n", tree->right->word);
        fprintf(f, "%s -> %s;\n", tree->word, tree->right->word);
    }
}

int export_to_dot(tree_elem *tree, FILE *f, const char *name)
{
    if (tree == NULL)
    {
        printf("tree is empty.\n");
        return 0;
    }
    fprintf(f, "digraph %s {\n", name);
    apply_pre(tree, to_dot, f);
    fprintf(f, "}\n");
    return 1;
}

// Чтение данных из файла и заполнение деревьев

int read_file(const char *file_name, tree_elem **tree, tree_elem **balanced_tree)
{
    tree_elem *in = NULL;
    char buf[MAX_STR_LEN + 1];
    int rc = OK;
    int length;
    FILE *f = fopen(file_name, "r");
    if (f)
    {
        while (rc == OK && fgets(buf, sizeof(buf), f))
        {
            length = strlen(buf);
            if (buf[length - 1] != '\n')
                rc = INPUT_ERROR;
            buf[length - 1] = '\0';
            length--;
            if (length > 0)
            {
                in = create_node_tree(buf);
                if (in)
                {
                    *tree = insert(*tree, in);
                    in = create_node_tree(buf);
                    if (in)
                    {
                        *balanced_tree = insert_balanced(*balanced_tree, in);
                    }
                    else
                    {
                        free_tree(*balanced_tree);
                        *balanced_tree = NULL;
                        rc = MEMORY_ERROR;
                    }
                }
                else
                {
                    free_tree(*tree);
                    *tree = NULL;
                    rc = MEMORY_ERROR;
                }
            }
        }
        fclose(f);
    }
    else
        return OPEN_FILE_ERROR;
    return rc;
}

int count_elements(const char *file_name, int *count)
{
    *count = 0;
    char buf[MAX_STR_LEN + 1];
    int rc = OK;
    int length;
    FILE *f = fopen(file_name, "r");
    if (f)
    {
        while (rc == OK && fgets(buf, sizeof(buf), f))
        {
            length = strlen(buf);
            if (buf[length - 1] != '\n')
                rc = INPUT_ERROR;
            buf[length - 1] = '\0';
            length--;
            if (length > 0)
            {
                (*count)++;
            }
        }
        fclose(f);
    }
    else
        return OPEN_FILE_ERROR;
    return rc;
}

int read_file_hash(const char *file_name, hash_table *table, int *count)
{
    t_node *in = NULL;
    *count = 0;
    char buf[MAX_STR_LEN + 1];
    int rc = OK;
    int length;
    FILE *f = fopen(file_name, "r");
    if (f)
    {
        while (rc == OK && fgets(buf, sizeof(buf), f))
        {
            length = strlen(buf);
            if (buf[length - 1] != '\n')
                rc = INPUT_ERROR;
            buf[length - 1] = '\0';
            length--;
            if (length > 0)
            {
                in = create_list_elem(buf);
                if (in)
                {
                    (*count) += insert_hash_table(table, in);
                }
                else
                {
                    free_hash_table(table);
                    rc = MEMORY_ERROR;
                }
            }
        }
        fclose(f);
    }
    else
        return OPEN_FILE_ERROR;
    return rc;
}

// Печать дерева (для отладки)

void print_tree(tree_elem *tree)
{
    if (!tree)
        return;
    printf("%s\n", tree->word);
    print_tree(tree->left);
    print_tree(tree->right);
}

void print_hash(hash_table table)
{
    t_node *cur;
    int iter = 0;
    printf("\nHash table:\n");
    for (int i = 0; i < table.size; i++)
    {
        printf("%3d|%-3s", i, "");
        cur = table.array[i];
        while (cur)
        {
            if (iter == 0)
                printf("%-5s->", cur->word);
            else
                printf("%s->", cur->word);
            iter++;
            cur = cur->next;
        }
        iter = 0;
        printf("\n");
    }
    printf("Table size = %d\n", table.size);
    printf("\n");
}
