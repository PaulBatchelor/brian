#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "jsmn.h"
#include "brian.h"

int brian_parse_args(brian_data *bd, int argc, char **argvp[])
{
	char **argv = *argvp;
	argv++;
	argc--;
	while(argc){
		if(argv[0][0] != '-') {
			break;
		}
		switch(argv[0][1]) {
			case 't':
				printf("Running in test mode. I will not remember this one.\n");
				bd->write = 0; 
				break;
			default:
				break;
		}
		argv++;
		argc--;
	}
	*argvp = argv;
	return argc;
}


int brian_init(brian_data *bd) 
{
    brian_htable_create(&bd->root, 13);
    brian_htable_create(&bd->sketch_data, 128);
    bd->ht = &bd->root;
    bd->json_size = 0;
    bd->id = 0;
    memset(bd->name, 0, 128);
    memset(bd->timestamp, 0, 40);
	bd->write = 1;
    return BRIAN_OK;
}

int brian_register(brian_data *bd, brian_sketch *sktch)
{
    brian_uint i = 0;
    while(sktch[i].name != NULL) {
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

int main(int argc, char *argv[]) 
{
    brian_data bd;
    brian_init(&bd);
	argc = brian_parse_args(&bd, argc, &argv);

    if(argc < 2) {
        printf("error.\n");
        return 1;
    }
    brian_register(&bd, brian_get_sketches());

    if(brian_db_open(&bd, argv[1]) != BRIAN_OK) {
        fprintf(stderr, "There was a problem opening the database.\n");
        return 1;
    }
    brian_parse_filename(&bd, argv[0]);
    brian_parse_json(&bd, argv[0]);

    brian_list *lst = &bd.root.lst;
    brian_entry *entry = lst->root.next; 
    brian_get_max_id(&bd, "brian", &bd.id);
    bd.id++;

    //brian_uint tmp = 123456;
    //if(brian_get_sketch_id(&bd, "fm2", &tmp) != BRIAN_OK) {
    //    fprintf(stderr, "couldn't find an ID\n");
    //}

    brian_insert(&bd, lst, entry, "brian", 5);
    brian_db_close(&bd); 
    brian_clean(&bd);

    return 0;
}
