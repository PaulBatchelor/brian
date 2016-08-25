#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "jsmn.h"
#include "brian.h"

static int parse_token(brian_data *bd, char *str, jsmntok_t *t, brian_uint i)
{
    /*this is a quick and dirty fix. look into this bug... */
    if(i + 1 > bd->json_size - 1) return 0;
    switch(t[i + 1].type) {
        case JSMN_PRIMITIVE:
            brian_htable_add_atof(bd->ht,
                &str[t[i].start],
                t[i].end - t[i].start,
                &str[t[i + 1].start],
                t[i + 1].end - t[i + 1].start);
            break;
        case JSMN_STRING:
            brian_htable_add_string(bd->ht,
                &str[t[i].start],
                t[i].end - t[i].start,
                &str[t[i + 1].start],
                t[i + 1].end - t[i + 1].start);
            break; 
        case JSMN_OBJECT: {
            brian_htable *tbl = malloc(sizeof(brian_htable));
            brian_htable_create(tbl, 16);
            brian_uint j = 0;
            brian_htable_add_htable(bd->ht,
                &str[t[i].start],
                t[i].end - t[i].start,
                tbl);
            brian_htable *prev = bd->ht;
            bd->ht = tbl;
            //printf("OBJ_START: %*.*s, size %d\n", 
            //    t[i].end - t[i].start,
            //    t[i].end - t[i].start,
            //    &str[t[i].start],
            //    t[i + 1].size 
            //    );
            int c = 0;
            int off = 0;
            for(j = 0; j < t[i + 1].size * 2; j +=2 ) {
                c = parse_token(bd, str, t, j + i + 2 + c);
                off += c;
            }
            bd->ht = prev;
            //printf("OBJ_END: %*.*s\n", 
            //    t[i].end - t[i].start,
            //    t[i].end - t[i].start,
            //    &str[t[i].start]
            //    );
            //printf("returning j as %d, off is %d\n", j, off);
            return j + c + off;
            break;
        }
        case JSMN_ARRAY: {
            /* TODO: implement array */  
            //brian_uint j = 0;
            //printf("array! of size %d\n", t[i + 1].size);
            //brian_array *ar = malloc(sizeof(brian_array));
            //brian_array_create(ar, t[i + 1].size);
            //brian_htable_add_array(bd->ht,
            //    &str[t[i].start],
            //    t[i].end - t[i].start,
            //    ar);

            //for(j = 0; j < t[i].size; j +=2 ) {
            //    j += parse_token(bd, str, t, j + i +2);
            //}
            //return j;
            break;
        }
        case JSMN_UNDEFINED:
            printf("this shouldn't happen!\n");
            break;
        default:
            break;
    }
    return 0;
}

int brian_parse_json(brian_data *bd, char *filename)
{
    FILE *fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_END);
    uint32_t size = ftell(fp);
    char *str = malloc(size + 1);
    fseek(fp, 0, SEEK_SET);
    fread(str, 1, size, fp);
    str[size] = 0;

	int i;
	int r;
    //brian_uint j;
	jsmn_parser p;
	jsmntok_t t[128]; 

    jsmn_init(&p);
	r = jsmn_parse(&p, str, size, t, sizeof(t)/sizeof(t[0]));

    bd->json_size = r;
	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		return 1;
	}

    for(i = 1; i < r; i+=2) {
        i += parse_token(bd, str, t, i);
    }

    free(str);
    fclose(fp);
    return 0;
}
