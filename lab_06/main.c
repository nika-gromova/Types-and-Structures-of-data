#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "io.h"
#include "my_tree.h"
#include "my_hash_table.h"

void info(void)
{
    printf("1 - load data from file;\n");
    printf("2 - form bynary tree in graphic view;\n");
    printf("3 - form balance tree in graphic view;\n");
    printf("4 - build hash table;\n");
    printf("5 - print hash table;\n");
    printf("6 - restruct hash table;\n");
    printf("7 - search word;\n");
    printf("8 - outlays;\n");
    printf("9 - exit.\n");
}

int main(void)
{
    int rc = OK;
    tree_elem *tree = NULL;
    tree_elem *balanced_tree = NULL;
    hash_table table = { NULL, 0 };
    int choice = 0;
    int count_col = 0;
    int count_cmp = 0;
    char file[20];
    char buf[20];
    char *end = NULL;
    FILE *save;
    tree_elem *found_tree = NULL;
    t_node *found_hash = NULL;
    while (choice == 0)
    {
        info();
        if (scanf("%s", buf) == 1)
        {
            choice = strtol(buf, &end, 10);
            if (*end == '\0' && choice > 0 && choice < 10)
            {
                if (choice == 1)
                {
                    free_tree(tree);
                    free_tree(balanced_tree);
                    tree = NULL;
                    balanced_tree = NULL;
                    printf("Input file name:\n");
                    scanf("%s", file);
                    rc = read_file(file, &tree, &balanced_tree);
                    if (rc == OK)
                    {
                        printf("loaded!\n");
                    }
                    else
                        printf("something wrong with loading(%d)\n", rc);
                    choice = 0;
                }
                if (choice == 2)
                {
                    save = fopen("bynary_tree.gv", "w");
                    if (save)
                    {
                        export_to_dot(tree, save, "bynary_tree");
                        printf("saved in file 'bynary_tree.gv'\n");
                        fclose(save);
                    }
                    else
                        printf("something wrong with saving data\n");
                    choice = 0;
                }
                if (choice == 3)
                {
                    save = fopen("balanced_tree.gv", "w");
                    if (save)
                    {
                        if (export_to_dot(balanced_tree, save, "balanced_tree"))
                            printf("saved in file 'balanced_tree.gv'\n");
                        fclose(save);
                    }
                    else
                        printf("something wrong with saving data\n");
                    choice = 0;
                }
                if (choice == 4)
                {
                    free_hash_table(&table);
                    printf("Input file name:\n");
                    scanf("%s", file);
                    rc = count_elements(file, &(table.size));
                    if (rc == OK)
                    {
                        create_table(&table, table.size);
                        rc = read_file_hash(file, &table, &count_col);
                        if (rc == OK)
                        {
                            printf("loaded!\n");
                            printf("count of collussions: %d\n", count_col);
                        }
                        else
                            printf("something wrong with saving data\n");
                    }
                    choice = 0;
                }
                if (choice == 5)
                {
                    print_hash(table);
                    choice = 0;
                }
                if (choice == 6)
                {
                    count_col = restruct_hash_table(&table);
                    if (count_col < 0)
                        printf("some memory errors :(\n");
                    else
                        printf("restructed!\ncount of collussions: %d\n", count_col);
                    choice = 0;
                }
                if (choice == 7)
                {
                    printf("Input word for searching:\n");
                    scanf("%s", buf);
                    found_tree = search_tree(tree, buf, &count_cmp);
                    if (found_tree)
                    {
                        printf("found in bynary tree: %s\n", found_tree->word);
                        printf("number of comparisons: %d\n", count_cmp);
                        found_tree = search_tree(balanced_tree, buf, &count_cmp);
                        if (found_tree)
                        {
                            printf("found in balanced tree: %s\n", found_tree->word);
                            printf("number of comparisons: %d\n", count_cmp);
                            found_hash = search_hash(&table, buf, &count_cmp);
                            if (found_hash)
                            {
                                printf("found in hash: %s\n", found_hash->word);
                                printf("number of comparisons: %d\n", count_cmp);
                            }
                            else
                                rc = NOT_FOUND;
                        }
                        else
                            rc = NOT_FOUND;
                    }
                    else
                        rc = NOT_FOUND;
                    if (rc == NOT_FOUND)
                        printf("not found\n");
                    choice = 0;
                }
                if (choice == 8)
                {
                    choice = 0;
                }
                if (choice == 9)
                {
                    printf("Exit.\n");
                }
            }
            else
                printf("wrong menu choice\n");
        }
    }
    free_tree(tree);
    free_tree(balanced_tree);
    tree = NULL;
    balanced_tree = NULL;
    free_hash_table(&table);
    return rc;
}
