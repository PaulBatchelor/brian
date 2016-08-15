/* types */

enum {
BRIAN_OK,
BRIAN_NOT_OK,
BRIAN_STOP,
BRIAN_NORMAL,
BRIAN_PRESERVE
};

enum{
BRIAN_STRING,
BRIAN_FLOAT,
BRIAN_PAIR,
BRIAN_HTABLE,
BRIAN_ARRAY,
BRIAN_ENTRY,
BRIAN_SKETCH,
BRIAN_UINT,
BRIAN_NULL,
};

typedef uint32_t brian_uint;

typedef struct {
    brian_uint type;
    void *ud;
} brian_val;

typedef struct brian_entry {
    brian_val val;
    struct brian_entry *next;
} brian_entry;

typedef struct {
    brian_entry root;
    brian_uint size;
    brian_entry *last;
} brian_list;

typedef struct {
    brian_list *bl;
    brian_uint size;
    brian_list lst;
} brian_htable;

typedef struct {
    char *key;
    brian_val val;
} brian_pair;

typedef struct {
    brian_val *val;
    brian_uint size;
} brian_array;

typedef struct {
    brian_htable root;
    brian_htable *ht;
    brian_uint json_size;
    brian_htable sketch_data;
    brian_uint id;
    sqlite3 *db;
    char timestamp[40];
    char name[128];
} brian_data;

typedef int (* brian_setter)(brian_data *, brian_array *);

typedef struct {
    char *name;
    brian_uint nargs;
    brian_setter f;
} brian_sketch;

int brian_list_init(brian_list *bl);
brian_val brian_val_string(char *str, brian_uint len);
brian_val brian_val_pair(char *key, brian_uint klen, brian_val *val);
brian_val brian_val_htable(brian_htable *tbl);
brian_val brian_val_float(float flt);
brian_val brian_val_array(brian_array *ar);
brian_val brian_val_entry(brian_entry *entry);
brian_val brian_val_sketch(brian_sketch *sketch);
brian_val brian_val_uint(brian_uint val);
int brian_val_free(brian_val *val);
int brian_list_append(brian_list *bl, brian_entry **entry, brian_val *val);
int brian_list_append_string(brian_list *bl, char *str, brian_uint slen);
int brian_list_append_htable(brian_list *bl, brian_htable *tbl);
int brian_list_append_pair(brian_list *bl, 
        char *key, brian_uint klen, brian_val *val);
int brian_list_append_entry(brian_list *bl, brian_entry *entry);
        
int brian_list_destroy(brian_list *bl);
int brian_list_iterate(brian_list *bl, 
        void *ud, 
        int (* callback)(brian_val *, void *));

int brian_list_get_last(brian_list *bl, brian_entry **last);

int brian_htable_create(brian_htable *ht, brian_uint size);
int brian_htable_destroy(brian_htable *ht);
int brian_htable_search(brian_htable *ht, 
        char *key, brian_uint klen, brian_val **val);

int brian_htable_add_value(brian_htable *ht, 
        char *key, brian_uint klen, brian_val *val);
int brian_htable_add_string(brian_htable *ht, 
        char *key, brian_uint klen, char *val, brian_uint vlen);
int brian_htable_add_htable(brian_htable *ht, 
        char *key, brian_uint klen, brian_htable *tbl);
int brian_htable_add_atof(brian_htable *ht, 
        char *key, brian_uint klen, char *val, brian_uint vlen);
int brian_htable_add_array(brian_htable *ht, 
        char *key, brian_uint klen, brian_array *ar);
int brian_htable_add_sketch(brian_htable *ht, 
        char *key, brian_uint klen, brian_sketch *sktch);
int brian_htable_add_uint(brian_htable *ht, 
        char *key, brian_uint klen, brian_uint num);

int brian_array_create(brian_array *ar, brian_uint size);
int brian_array_destroy(brian_array *ar);

int brian_init(brian_data *bd);
int brian_register(brian_data *bd, brian_sketch *sktch);
int brian_clean(brian_data *bd);

int brian_get_max_id(brian_data *bd, char *name, brian_uint *id);
int brian_get_sketch_id(brian_data *bd, char *name, brian_uint *id);

int brian_db_open(brian_data *bd, char *dbname);
int brian_db_close(brian_data *bd);

brian_uint brian_insert(brian_data *bd, 
        brian_list *lst,
        brian_entry *entry, 
        char *tabname,
        brian_uint len);

int brian_parse_filename(brian_data *bd, char *filename);
int brian_parse_json(brian_data *bd, char *filename);

brian_sketch * brian_get_sketches(void);
