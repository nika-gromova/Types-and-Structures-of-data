#ifndef STRUCTURE_H
#define STRUCTURE_H

#define MAX_LENGTH 15

struct car
{
    char model[MAX_LENGTH + 1];
    char country[MAX_LENGTH + 1];
    char color[MAX_LENGTH + 1];
    unsigned int price;
    unsigned int mileage;
    unsigned int repairs;
    unsigned int owners;
    char condition; // 1 - new; 2 - old
    union
    {
        float new;
        int old;
    } years;
};

struct key
{
    int index;
    unsigned int value;
};

#endif // STRUCTURE_H
