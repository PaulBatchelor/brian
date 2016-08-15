#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>
#include <regex.h>
#include "brian.h"

brian_val brian_val_string(char *str, brian_uint len)
{
    brian_val val;
    val.type = BRIAN_STRING;
    char *cpy = malloc(sizeof(char) * (len + 1));
    strncpy(cpy, str, len);
    /* Null terminator bit... */
    cpy[len] = 0;
    val.ud = cpy;
    return val;
}

brian_val brian_val_pair(char *key, brian_uint klen, brian_val *val)
{
    brian_val bval;
    bval.type = BRIAN_PAIR;
    brian_pair *pair = malloc(sizeof(brian_pair));
    pair->key = malloc(sizeof(char) * (klen +1));
    strncpy(pair->key, key, klen);
    pair->key[klen] = 0;

    pair->val = *val;

    bval.ud = pair;
    return bval;
}

brian_val brian_val_htable(brian_htable *tbl)
{
    brian_val val;
    val.type = BRIAN_HTABLE;
    val.ud = tbl;
    return val;
}

brian_val brian_val_float(float flt)
{
    brian_val val;
    val.type = BRIAN_FLOAT;
    float *ptr = malloc(sizeof(float));
    *ptr = flt;
    val.ud = ptr;
    return val;
}

brian_val brian_val_array(brian_array *ar)
{
    brian_val val;
    val.type = BRIAN_ARRAY;
    val.ud = ar;
    return val;
}

brian_val brian_val_entry(brian_entry *entry)
{
    brian_val val;
    val.type = BRIAN_ENTRY;
    val.ud = entry;
    return val;
}

brian_val brian_val_sketch(brian_sketch *sketch)
{
    brian_val val;
    val.type = BRIAN_SKETCH;
    val.ud = sketch;
    return val;
}

brian_val brian_val_uint(brian_uint num)
{
    brian_val val;
    val.type = BRIAN_UINT;
    brian_uint *ptr = malloc(sizeof(brian_uint));
    *ptr = num;
    val.ud = ptr;
    return val;
}

int brian_list_append(brian_list *bl, brian_entry **entry, brian_val *val)
{
    brian_entry *last = bl->last;
    *entry = malloc(sizeof(brian_entry));
    last->next = *entry;
    bl->last= *entry;
    bl->size++;
    //brian_entry *tmp = *entry;
    (**entry).val = *val;
    //tmp->val = *val;
    return BRIAN_OK;
}

int brian_val_free(brian_val *val)
{
    switch(val->type) {
        case BRIAN_PAIR: {
            brian_pair *pair = val->ud; 
            free(pair->key);
            brian_val_free(&pair->val);
            free(pair);
            break;
        }
        case BRIAN_HTABLE: 
            brian_htable_destroy((brian_htable *)val->ud);
            free(val->ud);
            break;
        case BRIAN_FLOAT: 
            free(val->ud);
            break;
        case BRIAN_ARRAY: {
            brian_array *ar = val->ud;
            brian_array_destroy(ar);
            free(val->ud);
            break;
        }
        case BRIAN_ENTRY:
            break;
        case BRIAN_SKETCH:
            break;
        case BRIAN_UINT:
            free(val->ud);
            break;
        default:
            free(val->ud);
            break;
    }
    return BRIAN_NOT_OK;
}

