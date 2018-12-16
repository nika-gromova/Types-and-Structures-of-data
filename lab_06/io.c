#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "io.h"
#include "my_tree.h"

void to_dot(tree_elem *tree, void *file)
{
    FILE *f = file;
    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->word, tree->left->word);
    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->word, tree->right->word);
}

void export_to_dot(tree_elem *tree, FILE *f, const char *name)
{
    fprintf(f, "digraph %s {\n", name);
    apply_pre(tree, to_dot, f);
    fprintf(f, "}\n");
}

int read_file(const char *file_name, tree_elem **tree)
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
            in = create_node_tree(buf);
            if (in)
            {
                *tree = insert(*tree, in);
            }
            else
                rc = MEMORY_ERROR;
        }
        fclose(f);
    }
    else
        return OPEN_FILE_ERROR;
    return rc;
}
