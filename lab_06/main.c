#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "io.h"
#include "my_tree.h"

void info(void)
{
    printf("1 - load data from file;\n");
    printf("2 - form tree in graphic view;\n");
    printf("3 - balance tree;\n");
    printf("4 - build hash table;\n");
    printf("5 - print hash table;\n");
    printf("6 - search word'\n");
    printf("7 - outlays;\n");
    printf("8 - exit.\n");
}

int main(void)
{
    int rc = OK;
    tree_elem *tree = NULL;
    int choice = 0;
    char file[20];
    char buf[20];
    char *end = NULL;
    FILE *save;

    while (choice == 0)
    {
        info();
        if (scanf("%s", buf) == 1)
        {
            choice = strtol(buf, &end, 10);
            if (*end == '\0' && choice > 0 && choice < 9)
            {
                if (choice == 1)
                {
                    printf("Input file name:\n");
                    scanf("%s", file);
                    rc = read_file(file, &tree);
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
                    save = fopen("graph.gv", "w");
                    if (save)
                    {
                        export_to_dot(tree, save, "my_tree");
                        printf("saved in file graph.hv\n");
                        fclose(save);
                    }
                    else
                        printf("something wrong with saving data\n");
                    choice = 0;
                }
                if (choice == 3)
                {
                    choice = 0;
                }
                if (choice == 4)
                {
                    choice = 0;
                }
                if (choice == 5)
                {
                    choice = 0;
                }
                if (choice == 6)
                {
                    choice = 0;
                }
                if (choice == 7)
                {
                    choice = 0;
                }
                if (choice == 8)
                {
                    printf("Exit.\n");
                }
            }
            else
                printf("wrong menu choice\n");
        }
    }

    return rc;
}
