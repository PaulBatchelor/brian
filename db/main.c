#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "jsmn.h"
#include "brian.h"

int main(int argc, char *argv[]) 
{
    if(argc < 2) {
        printf("error.\n");
        return 1;
    }
    brian_data bd;
    brian_init(&bd);
    brian_register(&bd, brian_get_sketches());

    if(brian_db_open(&bd, "brian.db") != BRIAN_OK) {
        fprintf(stderr, "There was a problem opening the database.\n");
        return 1;
    }
    brian_parse_filename(&bd, argv[1]);
    brian_parse_json(&bd, argv[1]);

    brian_list *lst = &bd.root.lst;
    brian_entry *entry = lst->root.next; 
    brian_get_sketch_id(&bd, "brian", &bd.id);
    bd.id++;

    brian_uint tmp = 123456;
    if(brian_get_sketch_id(&bd, "fm2", &tmp) != BRIAN_OK) {
        fprintf(stderr, "couldn't find an ID\n");
    }

    brian_insert(&bd, lst, entry, "brian", 5);
    brian_db_close(&bd); 
    brian_clean(&bd);

    return 0;
}
