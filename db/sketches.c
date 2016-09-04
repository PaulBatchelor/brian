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

static int tbl_fm(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO fm VALUES(NULL,?,?,?,?,?,?,?,?,?,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *freq1 = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        freq1, strlen(freq1), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *amp1 = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        amp1, strlen(amp1), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *mod1 = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        mod1, strlen(mod1), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *index1 = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        index1, strlen(index1), SQLITE_STATIC); 
    tmp = get_val(&ar->val[4]);
    char *freq2 = tmp.ud;
    sqlite3_bind_text(stmt, 6, 
        freq2, strlen(freq2), SQLITE_STATIC); 
    tmp = get_val(&ar->val[5]);
    char *amp2 = tmp.ud;
    sqlite3_bind_text(stmt, 7, 
        amp2, strlen(amp2), SQLITE_STATIC); 
    tmp = get_val(&ar->val[6]);
    char *car2 = tmp.ud;
    sqlite3_bind_text(stmt, 8, 
        car2, strlen(car2), SQLITE_STATIC); 
    tmp = get_val(&ar->val[7]);
    char *mod2 = tmp.ud;
    sqlite3_bind_text(stmt, 9, 
        mod2, strlen(mod2), SQLITE_STATIC); 
    tmp = get_val(&ar->val[8]);
    char *index2 = tmp.ud;
    sqlite3_bind_text(stmt, 10, 
        index2, strlen(index2), SQLITE_STATIC); 
    tmp = get_val(&ar->val[9]);
    char *crossfade = tmp.ud;
    sqlite3_bind_text(stmt, 11, 
        crossfade, strlen(crossfade), SQLITE_STATIC); 
    tmp = get_val(&ar->val[10]);
    char *feedback = tmp.ud;
    sqlite3_bind_text(stmt, 12, 
        feedback, strlen(feedback), SQLITE_STATIC); 
    tmp = get_val(&ar->val[11]);
    char *delay_time = tmp.ud;
    sqlite3_bind_text(stmt, 13, 
        delay_time, strlen(delay_time), SQLITE_STATIC); 
    tmp = get_val(&ar->val[12]);
    char *reverb_level = tmp.ud;
    sqlite3_bind_text(stmt, 14, 
        reverb_level, strlen(reverb_level), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}


static int tbl_plk(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO plk VALUES(NULL,?,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *seq = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        seq, strlen(seq), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *clock = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        clock, strlen(clock), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *key = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        key, strlen(key), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *octave_level = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        octave_level, strlen(octave_level), SQLITE_STATIC); 
    tmp = get_val(&ar->val[4]);
    char *reverb_level = tmp.ud;
    sqlite3_bind_text(stmt, 6, 
        reverb_level, strlen(reverb_level), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_mince(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO mince VALUES(NULL,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *file = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        file, strlen(file), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    brian_uint *s_id = tmp.ud;
    sqlite3_bind_int64(stmt, 3, *s_id);
    tmp = get_val(&ar->val[2]);
    brian_uint *f_id = tmp.ud;
    sqlite3_bind_int64(stmt, 4, *f_id);
    
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_tab(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO tab VALUES(NULL,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *file = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        file, strlen(file), SQLITE_STATIC); 

    tmp = get_val(&ar->val[1]);
    brian_uint *s_id = tmp.ud;
    sqlite3_bind_int(stmt, 3, *s_id);
        
    
    tmp = get_val(&ar->val[2]);
    brian_uint *f_id = tmp.ud;
    sqlite3_bind_int(stmt, 4, *f_id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_stretch(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO stretch VALUES(NULL,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *file = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        file, strlen(file), SQLITE_STATIC); 

    tmp = get_val(&ar->val[1]);
    brian_uint *s_id = tmp.ud;
    sqlite3_bind_int(stmt, 3, *s_id);
        
    
    tmp = get_val(&ar->val[2]);
    brian_uint *f_id = tmp.ud;
    sqlite3_bind_int(stmt, 4, *f_id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_crystalline(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO crystalline VALUES(NULL,?,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *feedback = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        feedback, strlen(feedback), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *tempo = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        tempo, strlen(tempo), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *drywet = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        drywet, strlen(drywet), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *probability = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        probability, strlen(probability), SQLITE_STATIC); 
    tmp = get_val(&ar->val[4]);
    char *seq = tmp.ud;
    sqlite3_bind_text(stmt, 6, 
        seq, strlen(seq), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_kltz(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO kltz VALUES(NULL,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *tempo = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        tempo, strlen(tempo), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *probability = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        probability, strlen(probability), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *feedback = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        feedback, strlen(feedback), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *resonance = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        resonance, strlen(resonance), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_distant(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO distant VALUES(NULL,?,?,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *pitch = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        pitch, strlen(pitch), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *tempo = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        tempo, strlen(tempo), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *brightness = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        brightness, strlen(brightness), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *detune = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        detune, strlen(detune), SQLITE_STATIC); 
    tmp = get_val(&ar->val[4]);
    char *seq = tmp.ud;
    sqlite3_bind_text(stmt, 6, 
        seq, strlen(seq), SQLITE_STATIC); 
    tmp = get_val(&ar->val[5]);
    char *key = tmp.ud;
    sqlite3_bind_text(stmt, 7, 
        key, strlen(key), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}


static int tbl_mold(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO mold VALUES(NULL,?,?,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *clk1 = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        clk1, strlen(clk1), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *fx1 = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        fx1, strlen(fx1), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *clk2 = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        clk2, strlen(clk2), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *fx2 = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        fx2, strlen(fx2), SQLITE_STATIC); 
    tmp = get_val(&ar->val[4]);
    char *crossfade = tmp.ud;
    sqlite3_bind_text(stmt, 6, 
        crossfade, strlen(crossfade), SQLITE_STATIC); 
    tmp = get_val(&ar->val[5]);
    char *fx3 = tmp.ud;
    sqlite3_bind_text(stmt, 7, 
        fx3, strlen(fx3), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_stars(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO stars VALUES(NULL,?,?,?,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *seq = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        seq, strlen(seq), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *atk = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        atk, strlen(atk), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *rel = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        rel, strlen(rel), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *key = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        key, strlen(key), SQLITE_STATIC); 
    tmp = get_val(&ar->val[4]);
    char *tempo = tmp.ud;
    sqlite3_bind_text(stmt, 6, 
        tempo, strlen(tempo), SQLITE_STATIC); 
    tmp = get_val(&ar->val[5]);
    char *fx = tmp.ud;
    sqlite3_bind_text(stmt, 7, 
        fx, strlen(fx), SQLITE_STATIC); 
    tmp = get_val(&ar->val[6]);
    char *rev_cutoff = tmp.ud;
    sqlite3_bind_text(stmt, 8, 
        rev_cutoff, strlen(rev_cutoff), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_loop(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO loop VALUES(NULL,?,?,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *tempo = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        tempo, strlen(tempo), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *drum = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        drum, strlen(drum), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *kick = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        kick, strlen(kick), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *snare = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        snare, strlen(snare), SQLITE_STATIC); 
    tmp = get_val(&ar->val[4]);
    char *hh = tmp.ud;
    sqlite3_bind_text(stmt, 6, 
        hh, strlen(hh), SQLITE_STATIC); 
    tmp = get_val(&ar->val[5]);
    char *drumfx = tmp.ud;
    sqlite3_bind_text(stmt, 7, 
        drumfx, strlen(drumfx), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_waveset(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO waveset VALUES(NULL,?,?,?,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *file = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        file, strlen(file), SQLITE_STATIC); 

    tmp = get_val(&ar->val[1]);
    brian_uint *s_id = tmp.ud;
    sqlite3_bind_int(stmt, 3, *s_id);
    
    tmp = get_val(&ar->val[2]);
    brian_uint *f_id = tmp.ud;
    sqlite3_bind_int(stmt, 4, *f_id);

    tmp = get_val(&ar->val[3]);
    char *stretch = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        stretch, strlen(stretch), SQLITE_STATIC); 
    tmp = get_val(&ar->val[4]);
    char *mod = tmp.ud;
    sqlite3_bind_text(stmt, 6, 
        mod, strlen(mod), SQLITE_STATIC); 
    tmp = get_val(&ar->val[5]);
    char *decay = tmp.ud;
    sqlite3_bind_text(stmt, 7, 
        decay, strlen(decay), SQLITE_STATIC); 
    tmp = get_val(&ar->val[6]);
    char *amp = tmp.ud;
    sqlite3_bind_text(stmt, 8, 
        amp, strlen(amp), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static int tbl_starloop(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO starloop VALUES(NULL,?,?,?,?,?);",
         -1, 
         &stmt, NULL);

    sqlite3_bind_int64(stmt, 1, bd->id);

    tmp = get_val(&ar->val[0]);
    brian_uint *s_id_loop = tmp.ud;
    sqlite3_bind_int(stmt, 2, *s_id_loop);
    
    tmp = get_val(&ar->val[1]);
    brian_uint *f_id_loop = tmp.ud;
    sqlite3_bind_int(stmt, 3, *f_id_loop);
    
    tmp = get_val(&ar->val[2]);
    brian_uint *s_id_star = tmp.ud;
    sqlite3_bind_int(stmt, 4, *s_id_star);
    
    tmp = get_val(&ar->val[3]);
    brian_uint *f_id_star = tmp.ud;
    sqlite3_bind_int(stmt, 5, *f_id_star);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}


/*

*/
static int tbl_bit(brian_data *bd, brian_array *ar)
{
    brian_val tmp;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO bit VALUES(NULL,?,?,?,?,?);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
    tmp = get_val(&ar->val[0]);
    char *ctrl = tmp.ud;
    sqlite3_bind_text(stmt, 2, 
        ctrl, strlen(ctrl), SQLITE_STATIC); 
    tmp = get_val(&ar->val[1]);
    char *bit = tmp.ud;
    sqlite3_bind_text(stmt, 3, 
        bit, strlen(bit), SQLITE_STATIC); 
    tmp = get_val(&ar->val[2]);
    char *mod = tmp.ud;
    sqlite3_bind_text(stmt, 4, 
        mod, strlen(mod), SQLITE_STATIC); 
    tmp = get_val(&ar->val[3]);
    char *crossfade = tmp.ud;
    sqlite3_bind_text(stmt, 5, 
        crossfade, strlen(crossfade), SQLITE_STATIC); 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}

static brian_sketch sketches[] = {
    {"brian", 5, tbl_brian},
    {"fm2", 4, tbl_fm2},
    {"fm", 13, tbl_fm},
    {"plk", 5, tbl_plk},
    {"mince", 3, tbl_mince},
    {"tab", 3, tbl_tab},
    {"stretch", 3, tbl_stretch},
    {"crystalline", 5, tbl_crystalline},
    {"kltz", 4, tbl_kltz},
    {"distant", 6, tbl_distant},
    {"mold", 6, tbl_mold},
    {"stars", 7, tbl_stars},
    {"loop", 6, tbl_loop},
    {"waveset", 7, tbl_waveset},
    {"starloop", 4, tbl_starloop},
    {"bit",4,tbl_bit},
    {NULL, 0, NULL},
};

brian_sketch * brian_get_sketches(void)
{
    return sketches;
}
