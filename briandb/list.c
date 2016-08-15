#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>
#include <regex.h>
#include "brian.h"

int brian_list_init(brian_list *bl)
{
    bl->size = 0;
    bl->last = &bl->root;
    return BRIAN_NOT_OK;
}

int brian_list_append_pair(brian_list *bl, 
        char *key, brian_uint klen, brian_val *val)
{
    brian_val pair = brian_val_pair(key, klen, val);
    brian_entry *new = NULL;
    return brian_list_append(bl, &new, &pair);
}

int brian_list_append_htable(brian_list *bl, brian_htable *tbl)
{
    brian_val val = brian_val_htable(tbl);
    brian_entry *new;
    return brian_list_append(bl, &new, &val);
}

int brian_list_append_string(brian_list *bl, char *str, brian_uint slen)
{
    brian_val val = brian_val_string(str, slen);
    brian_entry *new;
    brian_list_append(bl, &new, &val);
    //new->val = val;
    return BRIAN_NOT_OK;
}

int brian_list_append_entry(brian_list *bl, brian_entry *entry)
{
    brian_val val = brian_val_entry(entry);
    brian_entry *new;
    return brian_list_append(bl, &new, &val);
}

int brian_list_destroy(brian_list *bl)
{
    brian_uint i;
    brian_entry *entry = bl->root.next;
    brian_entry *next;
    for(i = 0; i < bl->size; i++) {
        next = entry->next;
        brian_val_free(&entry->val);
        free(entry);
        entry = next;        
    }
    return BRIAN_NOT_OK;
}

int brian_list_iterate(brian_list *bl, 
        void *ud, 
        int (* callback)(brian_val *, void *))
{
    brian_entry *entry = bl->root.next;
    brian_entry *next;
    int rc = BRIAN_OK;
    brian_uint i;
    for(i = 0; i < bl->size; i++) {
        next = entry->next;
        rc = callback(&entry->val, ud);
        if(rc == BRIAN_STOP) { break; }
        entry = next;
    }

    return rc;
}

int brian_list_get_last(brian_list *bl, brian_entry **last)
{
    *last = bl->last;
    return BRIAN_OK;
}

