#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structure.h"

void print_data(struct car **table, int n);
int input_str(char *str, struct car *table_element);
int read_data(char *file_name, struct car *table[], int n);
int save_data(char *filename, struct car **table, int n);
void print_keys(struct key **table, int n);
void print_table_with_keys(struct key **keys, struct car **table, int n);
int input_car(struct car *cur);
void print_car(struct car elem);
void print_sep(int n);
int read_line(char *str, int n);

#endif // IO_H
