#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <ncurses.h>

typedef struct _win_border_struct {
    chtype  ls, rs, ts, bs, 
        tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

    int startx, starty;
    int height, width;
    WIN_BORDER border;
}WIN;

static int l_initscr(lua_State *L)
{
    initscr();
    return 0;
}

static int l_printw(lua_State *L)
{
    const char *str = lua_tostring(L, 1);
    printw(str);
    return 0;
}

static int l_refresh(lua_State *L)
{
    refresh();
    return 0;
}

static int l_getch(lua_State *L)
{
    char ch = getch();
    lua_pushinteger(L, ch);
    return 1;
}

static int l_endwin(lua_State *L)
{
    endwin();
    return 0;
}

static int l_noecho(lua_State *L)
{
    noecho();
    return 0;
}

static int l_curs_set(lua_State *L)
{
    int id = lua_tointeger(L, 1);
    curs_set(id);
    return 0;
}

static int l_cbreak(lua_State *L)
{
    cbreak();
    return 0;
}

static int l_newwin(lua_State *L)
{
    int h = lua_tointeger(L, 1);
    int w = lua_tointeger(L, 2);
    int y = lua_tointeger(L, 3);
    int x = lua_tointeger(L, 4);
    WINDOW *win = newwin(h, w, y, x);
    lua_pushlightuserdata(L, win);
    return 1;
}

static int l_box(lua_State *L)
{
    WINDOW *win = lua_touserdata(L, 1);
    int ch1 = lua_tointeger(L, 2);
    int ch2 = lua_tointeger(L, 3);
    box(win, ch1, ch2);
    return 0;
}

static int l_wrefresh(lua_State *L)
{
    WINDOW *win = lua_touserdata(L, 1);
    wrefresh(win);
    return 0;
}

static int l_delwin(lua_State *L)
{
    WINDOW *win = lua_touserdata(L, 1);
    delwin(win);
    return 0;
}

static int l_wborder(lua_State *L)
{
    WINDOW *win = lua_touserdata(L, 1);
    const char *ls = lua_tostring(L, 2);
    const char *rs = lua_tostring(L, 3);
    const char *ts = lua_tostring(L, 4);
    const char *bs = lua_tostring(L, 5);
    const char *tl = lua_tostring(L, 6);
    const char *tr = lua_tostring(L, 7);
    const char *bl = lua_tostring(L, 8);
    const char *br = lua_tostring(L, 9);
    wborder(win, *ls, *rs, *ts, *bs, *tl, *tr, *bl, *br);
    return 0;
}

static int l_mvprintw(lua_State *L)
{
    int y = lua_tointeger(L, 1);
    int x = lua_tointeger(L, 2);
    const char *str = lua_tostring(L, 3);
    mvprintw(y, x, str);
    return 0;
}

static int l_mvwprintw(lua_State *L)
{
    WINDOW *win = lua_touserdata(L, 1);
    int y = lua_tointeger(L, 2);
    int x = lua_tointeger(L, 3);
    const char *str = lua_tostring(L, 4);
    mvwprintw(win, y, x, str);
    return 0;
}

static int l_wattron(lua_State *L)
{
    WINDOW *win = lua_touserdata(L, 1);
    int attr = lua_tointeger(L, 2);
    wattron(win, attr);
    return 0;
}

static int l_wattroff(lua_State *L)
{
    WINDOW *win = lua_touserdata(L, 1);
    int attr = lua_tointeger(L, 2);
    wattroff(win, attr);
    return 0;
}

static int l_attron(lua_State *L)
{
    int attr = lua_tointeger(L, 1);
    attron(attr);
    return 0;
}

static int l_attroff(lua_State *L)
{
    int attr = lua_tointeger(L, 1);
    attroff(attr);
    return 0;
}

static int l_A_BOLD(lua_State *L)
{
    lua_pushinteger(L, A_BOLD);
    return 1;
}

static int l_A_REVERSE(lua_State *L)
{
    lua_pushinteger(L, A_REVERSE);
    return 1;
}

static int l_A_NORMAL(lua_State *L)
{
    lua_pushinteger(L, A_NORMAL);
    return 1;
}

static int l_clear(lua_State *L)
{
    clear();
    return 1;
}


static const struct luaL_Reg ncurses[] = { 
    {"initscr", l_initscr},
    {"printw", l_printw},
    {"refresh", l_refresh},
    {"getch", l_getch},
    {"endwin", l_endwin},
    {"noecho", l_noecho},
    {"curs_set", l_curs_set},
    {"cbreak", l_cbreak},
    {"newwin", l_newwin},
    {"box", l_box},
    {"wrefresh", l_wrefresh},
    {"wborder", l_wborder},
    {"delwin", l_delwin},
    {"mvprintw", l_mvprintw},
    {"mvwprintw", l_mvwprintw},
    {"wattron", l_wattron},
    {"wattroff", l_wattroff},
    {"attron", l_attron},
    {"attroff", l_attroff},
    {"A_BOLD", l_A_BOLD},
    {"A_REVERSE", l_A_REVERSE},
    {"A_NORMAL", l_A_NORMAL},
    {"clear", l_clear},
    {NULL, NULL}
};

int luaopen_ncurses(lua_State *L)
{
    lua_newtable(L);
    luaL_setfuncs(L, ncurses, 0);
    return 1;
}

