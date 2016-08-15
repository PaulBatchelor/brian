#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h>
#include <regex.h>
#include "brian.h"

int brian_init(brian_data *bd) 
{
    brian_htable_create(&bd->root, 13);
    brian_htable_create(&bd->sketch_data, 128);
    bd->ht = &bd->root;
    bd->json_size = 0;
    bd->id = 0;
    memset(bd->name, 0, 128);
    memset(bd->timestamp, 0, 40);
    return BRIAN_OK;
}

int brian_register(brian_data *bd, brian_sketch *sktch)
{
    brian_uint i = 0;
    while(sktch[i].name != NULL) {
        printf("Adding sketch %s\n", sktch[i].name);
        brian_htable_add_sketch(&bd->sketch_data, 
            sktch[i].name, strlen(sktch[i].name), &sktch[i]);
        i++;
    }
    return BRIAN_OK;
}

int brian_clean(brian_data *bd) 
{
    brian_htable_destroy(&bd->root);
    brian_htable_destroy(&bd->sketch_data);
    return BRIAN_OK;
}

