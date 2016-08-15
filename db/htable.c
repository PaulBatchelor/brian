#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>
#include <regex.h>
#include "brian.h"

static brian_uint brian_hash(brian_htable *ht, const char *str, brian_uint len)
{
    uint32_t h = 5381;
    brian_uint i;
    for(i = 0; i < len; i++) {
    //while(*str)
    //{
        h = ((h << 5) + h) ^ str[0];
        h %= 0x7FFFFFFF;
        str++;
    //}
    }

    return h % ht->size;
}

int brian_htable_create(brian_htable *ht, brian_uint size)
{
    brian_uint i;
    ht->bl = malloc(sizeof(brian_list) * size);
    ht->size = size;

    for(i = 0; i < size; i++) brian_list_init(&ht->bl[i]);

    brian_list_init(&ht->lst);

    return BRIAN_OK;
}

int brian_htable_destroy(brian_htable *ht)
{
    brian_uint i;
    for(i = 0; i < ht->size; i++) {
        brian_list_destroy(&ht->bl[i]);
    }
    brian_list_destroy(&ht->lst);
    free(ht->bl);
    return BRIAN_OK;
}

int brian_htable_add_value(brian_htable *ht, 
        char *key, brian_uint klen, brian_val *val)
{
    brian_uint pos = brian_hash(ht, key, klen);
    brian_list *lst = &ht->bl[pos];
    int rc = brian_list_append_pair(lst, key, klen, val);
    brian_entry *entry = NULL;
    brian_list_get_last(lst, &entry);
    /* TODO: make this linked list optional (by default) */
    rc = brian_list_append_entry(&ht->lst, entry);
    return rc;
}

int brian_htable_add_string(brian_htable *ht, 
        char *key, brian_uint klen, char *val, brian_uint vlen)
{
    brian_val bval = brian_val_string(val, vlen);
    return brian_htable_add_value(ht, key, klen, &bval);
}

int brian_htable_add_htable(brian_htable *ht, 
        char *key, brian_uint klen, brian_htable *tbl)
{
    brian_val val = brian_val_htable(tbl);
    return brian_htable_add_value(ht, key, klen, &val);
}

int brian_htable_add_atof(brian_htable *ht, 
        char *key, brian_uint klen, char *val, brian_uint vlen)
{
    char *endptr = val + vlen;
    float tmp = strtod(val, &endptr);
    brian_val flt = brian_val_float(tmp);
    return brian_htable_add_value(ht, key, klen, &flt);
}

int brian_htable_add_array(brian_htable *ht, 
        char *key, brian_uint klen, brian_array *ar)
{
    brian_val val = brian_val_array(ar);
    return brian_htable_add_value(ht, key, klen, &val);
}

int brian_htable_add_sketch(brian_htable *ht, 
        char *key, brian_uint klen, brian_sketch *sktch)
{
    brian_val val = brian_val_sketch(sktch); 
    return brian_htable_add_value(ht, key, klen, &val);
}

typedef struct {
    brian_val *val;
    char *key;
    brian_uint rc;
} brian_search_d;

static int brian_search(brian_val *val, void *ud) 
{
    brian_search_d *bs = ud;
    brian_pair *pair = val->ud;
    char *key = pair->key;
    if(!strcmp(key, bs->key)) {
        bs->val = &pair->val;
        bs->rc = BRIAN_OK;
        return BRIAN_STOP;
    }
    return BRIAN_OK;
}


int brian_htable_search(brian_htable *ht, 
        char *key, brian_uint klen, brian_val **val)
{
    brian_uint pos = brian_hash(ht, key, klen);
    brian_list *lst = &ht->bl[pos];
    brian_search_d bs;
    bs.rc = BRIAN_NOT_OK;
    bs.key = key;
    brian_list_iterate(lst, &bs, brian_search);
    *val = bs.val;
    return bs.rc;
}

