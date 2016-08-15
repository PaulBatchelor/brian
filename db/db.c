#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>
#include <regex.h>
#include "brian.h"

int brian_db_open(brian_data *bd, char *dbname)
{
    if(sqlite3_open(dbname, &bd->db) != SQLITE_OK) 
        return BRIAN_NOT_OK;
    else 
        return BRIAN_OK;
}

int brian_db_close(brian_data *bd)
{
    sqlite3_close(bd->db);
    return BRIAN_NOT_OK;
}

int brian_get_max_id(brian_data *bd, char *name, brian_uint *id)
{
    char msg[256];
    sprintf(msg, "SELECT MAX(id) from %s;", name);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
        bd->db, 
        msg,
        -1, 
        &stmt, NULL);
    int rc = BRIAN_NOT_OK;
    if(sqlite3_step(stmt) != SQLITE_DONE) {
        *id = 0;
        rc = BRIAN_NOT_OK;
    } else {
        *id = sqlite3_column_int(stmt, 0);
        rc = BRIAN_OK;
    }
    sqlite3_finalize(stmt);

    return rc;
}

int brian_get_sketch_id(brian_data *bd, char *name, brian_uint *id)
{
    char msg[256];
    sprintf(msg, "SELECT id FROM sketches WHERE(name=\"%s\");", name);
    printf("SQL statement is\n\t%s\n", msg);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
        bd->db, 
        msg,
        -1, 
        &stmt, NULL);

    int rc = BRIAN_NOT_OK;

    /* TODO: make this error code actually work */ 
    sqlite3_step(stmt);
    *id = sqlite3_column_int(stmt, 0);
    rc = BRIAN_OK;

    sqlite3_finalize(stmt);

    return rc;
}

brian_uint brian_insert(brian_data *bd, 
        brian_list *lst,
        brian_entry *entry, 
        char *tabname,
        brian_uint len) 
{
    brian_entry *next;
    brian_entry *tmp;
    brian_uint i;
    brian_array ar;
    brian_sketch *sktch;
    brian_val *val;
    brian_uint id;
    
    if(brian_htable_search(&bd->sketch_data, tabname, len, &val) == BRIAN_OK) {
        printf("found table '%s'\n", tabname);
        sktch = val->ud;
    } else {
        printf("could not find table %s!\n", tabname);
    }

    brian_get_max_id(bd, tabname, &id);
    id++;
    brian_array_create(&ar, sktch->nargs);
    brian_pair *p;
    for(i = 0; i < sktch->nargs; i++) {
        next = entry->next;
        tmp = entry->val.ud;
        p = tmp->val.ud; 
        if(p->val.type == BRIAN_HTABLE) {
            printf("found another HTABLE called %s\n", p->key);
            brian_htable *ht = p->val.ud;

            brian_uint sketch_id = 123;
            if(brian_get_sketch_id(bd, p->key, &sketch_id) != BRIAN_OK) {
                printf("ERROR: could not find table %s\n", p->key);
            }
            ar.val[i] = brian_val_uint(sketch_id);

            i++;
            brian_uint fid = brian_insert(bd, 
                &ht->lst, 
                ht->lst.root.next, 
                p->key, strlen(p->key));
            ar.val[i] = brian_val_uint(fid);
        } else {
            ar.val[i] = brian_val_entry(entry);
        }
        entry = next;
    }
    sktch->f(bd, &ar);
    brian_array_destroy(&ar);
    return id;
}

int brian_parse_filename(brian_data *bd, char *filename)
{
    regex_t reg;
    regmatch_t pmatch[3];
    char *str = "(.*)"
    "-([0-9][0-9][0-9][0-9]"
    "-[0-9][0-9]-[0-9][0-9]"
    "_[0-9][0-9][0-9][0-9])\\.json";
    regcomp(&reg, str, REG_EXTENDED);
    regexec(&reg, filename, 3, pmatch, 0);
    size_t size = (pmatch[1].rm_eo - pmatch[1].rm_so);
    strncpy(bd->name, filename, size);
    strncpy(bd->timestamp, 
        filename + size + 1, 
        (pmatch[2].rm_eo - pmatch[2].rm_so));
    printf("the name is %s, the timestamp is %s\n", 
        bd->name, bd->timestamp);
    regfree(&reg);
    return BRIAN_OK;
}
