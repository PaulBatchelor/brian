#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "brian.h"

static brian_val get_val(brian_val *val)
{
    /*TODO: do we need this many levels of entries?*/
    if(val->type == BRIAN_ENTRY) {
        brian_entry *e = val->ud;
        brian_entry *e2 = e->val.ud;
        brian_pair *p = e2->val.ud;
        return p->val;
    } else {
        return *val;
    }
}

static int tbl_brian(brian_data *bd, brian_array *ar)
{
    /* seed,top_file,sketch */
    brian_val tmp = get_val(&ar->val[1]);
    char *sketch = tmp.ud;
    tmp = get_val(&ar->val[0]);
    float *seed = tmp.ud;
    brian_uint iseed = (brian_uint) *seed;
    tmp = get_val(&ar->val[2]);
    char *top_file = tmp.ud;

    tmp = get_val(&ar->val[3]);
    brian_uint *sketch_id = tmp.ud;

    tmp = get_val(&ar->val[4]);
    brian_uint *fid = tmp.ud;
    
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
        bd->db, 
        "INSERT INTO brian VALUES(NULL, ?, ?, ?, ?, ?, ?, ?);",
        -1, 
        &stmt, NULL);

    sqlite3_bind_text(stmt, 1, 
        bd->name, strlen(bd->name), SQLITE_STATIC); 
    sqlite3_bind_text(stmt, 2, 
        bd->timestamp, strlen(bd->timestamp), SQLITE_STATIC); 
    sqlite3_bind_text(stmt, 3, 
        top_file, strlen(top_file), SQLITE_STATIC); 
    sqlite3_bind_int64(stmt, 4, iseed);
    sqlite3_bind_text(stmt, 5, 
        sketch, strlen(sketch), SQLITE_STATIC); 
    sqlite3_bind_int(stmt, 6, (brian_uint)*sketch_id);
    sqlite3_bind_int(stmt, 7, (brian_uint)*fid);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return BRIAN_OK;
}

static int tbl_fm2(brian_data *bd, brian_array *ar)
{
    /* clock, probability, release, feedback */ 
    printf("now we are at fm2!\n");
    brian_val tmp = get_val(&ar->val[0]);
    char *clock = tmp.ud;
    tmp = get_val(&ar->val[1]);
    char *prob = tmp.ud;
    tmp = get_val(&ar->val[2]);
    char *rel = tmp.ud;
    tmp = get_val(&ar->val[3]);
    char *fdbk  = tmp.ud;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
        bd->db, 
        "INSERT INTO fm2 VALUES(NULL, ?, ?, ?, ?, ?);",
        -1, 
        &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    sqlite3_bind_text(stmt, 2, 
        clock, strlen(clock), SQLITE_STATIC); 
    sqlite3_bind_text(stmt, 3, 
        prob, strlen(prob), SQLITE_STATIC); 
    sqlite3_bind_text(stmt, 4, 
        rel, strlen(rel), SQLITE_STATIC); 
    sqlite3_bind_text(stmt, 5, 
        fdbk, strlen(fdbk), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static brian_sketch sketches[] = {
    {"brian", 5, tbl_brian},
    {"fm2", 4, tbl_fm2},
    {NULL, 0, NULL},
};

brian_sketch * brian_get_sketches(void)
{
    return sketches;
}
