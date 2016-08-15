#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>
#include <regex.h>
#include "brian.h"

int brian_array_create(brian_array *ar, brian_uint size)
{
    ar->val = malloc(sizeof(brian_val) * size);
    ar->size = size;
    return BRIAN_OK;
}

int brian_array_destroy(brian_array *ar)
{
    brian_uint i;
    int rc = BRIAN_OK;
    for(i = 0; i < ar->size; i++) rc = brian_val_free(&ar->val[i]);
    free(ar->val);
    return rc;
}
