tmp = package.loadlib("tools/brian_browse/sqlite/sqlite.so", "luaopen_sqlite")
sqlite = tmp()

tmp = package.loadlib("tools/brian_browse/curses/ncurses.so", "luaopen_ncurses")
curses = tmp()

function quit(d)
    curses.endwin()
    return 0
end

function down(d)
    curses.mvprintw(d.pos, 1, " ")
    d.pos = math.min(d.pos + 1, d.size - 1)
    curses.mvprintw(d.pos, 1, ">")
    return 1
end

function up(d)
    curses.mvprintw(d.pos, 1, " ")
    d.pos = math.max(d.pos - 1, 1)
    curses.mvprintw(d.pos, 1, ">")
    return 1
end

function query(str)
    local db = sqlite.open("brian.db")

    local out = {}

    local stmt = sqlite.prepare(db, str)
    local tbl = {}

    while(sqlite.notdone(sqlite.step(stmt))) do
        tbl = {}
        for i = 1, sqlite.count(stmt)  do
            tbl[i] = sqlite.column(stmt, i - 1)

        end
        table.insert(out, tbl)
    end

    sqlite.finalize(stmt)
    sqlite.close(db)

    return out
end

function get_sketch_name(id)
    local str = "SELECT name from sketches where(id == %d);"
    str = string.format(str, id)
    local name = query(str)
    return name[1][1]
end

function print_page(d)
    for i, row in pairs(d.rows) do
        curses.mvprintw(i, 3, row[2])
    end
    d.pos = d.top_pos
    curses.mvprintw(d.top_pos, 1, ">")
end

function sel(d)
    curses.clear()
    local name = get_sketch_name(d.rows[d.pos + 1][7])
    curses.attron(curses.A_BOLD())
    curses.mvprintw(0, 0, name)
    curses.attroff(curses.A_BOLD())
    local qstr = string.format("SELECT * from %s WHERE(id == %d);",
        name, d.rows[d.pos + 1][8])
    local qval = query(qstr) 

    for k,v in pairs(qval[1]) do
        curses.mvprintw(k, 3, v)
    end

    d.top_pos = d.pos
    d.pos = 1
    curses.mvprintw(d.pos, 1, ">")
    d.page = 2
    return 1
end

function back(d)
    if (d.page == 1) then return 1 end
    d.page = 1
    curses.clear()
    print_page(d)
    return 1
end

local out = query("SELECT * FROM brian ORDER BY id DESC limit 20")


curses.initscr()
curses.noecho()
curses.curs_set(0)


tbl = {}
tbl['q'] = quit
tbl['j'] = down 
tbl['k'] = up
tbl['l'] = sel
tbl['h'] = back

run = 1
data = {}
data.rows = out
data.pos = 1
data.size = 20
data.page = 1
data.top_pos = 1

print_page(data)

while(run == 1) do
    ch = curses.getch()
    curses.refresh()
    if(type(tbl[string.char(ch)]) ~= 'nil') then
        run = tbl[string.char(ch)](data)
    end
end

curses.endwin()
