#include "defines.h"
#include "structure.h"
#include "operations.h"

int add(char *filename, struct car tmp)
{
    int rc = OK;
    FILE *f = fopen(filename, "a");
    if (f)
    {
        fprintf(f, "%s|%s|%d|%s|%d|%d|%d|", tmp.model, tmp.country, tmp.price, tmp.color, tmp.mileage, tmp.repairs, tmp.owners);
        if (tmp.condition == 1)
            fprintf(f, "%.1f\n", tmp.years.new);
        else
            fprintf(f, "%d\n", tmp.years.old);
        fclose(f);
    }
    else
        rc = OPEN_FILE_ERROR;
    return rc;
}
