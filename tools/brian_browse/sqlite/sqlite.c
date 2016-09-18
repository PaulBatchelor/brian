#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <sqlite3.h>

static int l_open(lua_State *L)
{
    sqlite3 *db;
    const char *file = lua_tostring(L, 1);
    int rc = sqlite3_open(file, &db);
    if(rc) {
        /* TODO: error check */
    }
    lua_pushlightuserdata(L, db); 
    return 1;
}

static int l_close(lua_State *L)
{
    sqlite3 *db = lua_touserdata(L, 1);
    sqlite3_close(db);
    return 0;
}

static int l_finalize(lua_State *L)
{
    sqlite3_stmt *stmt = lua_touserdata(L, 1);
    sqlite3_finalize(stmt);
    return 0;
}

static int l_prepare(lua_State *L)
{
    sqlite3 *db = lua_touserdata(L, 1);
    const char *str = lua_tostring(L, 2);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, str, -1, &stmt, NULL);

    lua_pushlightuserdata(L, stmt); 
    return 1;
}

static int l_step(lua_State *L)
{
    sqlite3_stmt *stmt = lua_touserdata(L, 1);
    int rc = sqlite3_step(stmt);
    lua_pushinteger(L, rc);
    return 1;
}

static int l_count(lua_State *L)
{
    sqlite3_stmt *stmt = lua_touserdata(L, 1);
    int count = sqlite3_column_count(stmt);
    lua_pushinteger (L, count);
    return 1;
}

static int l_column(lua_State *L)
{
    sqlite3_stmt *stmt = lua_touserdata(L, 1);
    int col = lua_tointeger(L, 2);
    switch(sqlite3_column_type(stmt, col)) {
        case SQLITE_INTEGER: {
            long num = sqlite3_column_int64(stmt, col);
            lua_pushnumber(L, num);
            break;
        }
        case SQLITE_FLOAT:{
            double num = sqlite3_column_double(stmt, col);
            lua_pushnumber(L, num);
            break;
        }
        case SQLITE_TEXT: {
            const char *str = sqlite3_column_text(stmt, col);
            lua_pushstring(L, str); 
            break;
        }
        default:
            lua_pushnil(L);
            break;
    }
    return 1;
}

static int l_notdone(lua_State *L)
{
    int rc = lua_tointeger(L, 1);
    if(rc != SQLITE_DONE)  {
        lua_pushboolean(L, 1);
    } else {
        lua_pushboolean(L, 0);
    }
    return 1;
}

static const struct luaL_Reg sqlite[] = { 
    {"open", l_open},
    {"close", l_close},
    {"prepare", l_prepare},
    {"finalize", l_finalize},
    {"step", l_step},
    {"count", l_count},
    {"column", l_column},
    {"notdone", l_notdone},
    {NULL, NULL}
};

int luaopen_sqlite(lua_State *L)
{
    lua_newtable(L);
    luaL_setfuncs(L, sqlite, 0);
    return 1;
}

