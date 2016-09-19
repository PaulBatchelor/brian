tmp = package.loadlib("tools/brian_browse/sqlite/sqlite.so", "luaopen_sqlite")
sqlite = tmp()

tmp = package.loadlib("tools/brian_browse/curses/ncurses.so", "luaopen_ncurses")
curses = tmp()

function quit(d)
    if (d.page == 3) then return 1 end
    curses.endwin()
    return 0
end

function down(d)
    if (d.page == 3) then return 1 end
    curses.mvprintw(d.pos, 1, " ")
    d.pos = math.min(d.pos + 1, d.size)
    curses.mvprintw(d.pos, 1, ">")
    return 1
end

function up(d)
    if (d.page == 3) then return 1 end
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
    curses.clear()
    for i, row in pairs(d.rows) do
        curses.mvprintw(i, 3, row[2])
    end
    d.pos = d.top_pos
    curses.mvprintw(d.top_pos, 1, ">")
end

function sel(d)
    if (d.page ~= 1) then return 1 end
    curses.clear()
    local name = get_sketch_name(d.rows[d.pos][7])
    curses.attron(curses.A_BOLD())
    curses.mvprintw(0, 0, d.rows[d.pos][2])
    curses.attroff(curses.A_BOLD())
    local qstr = string.format("SELECT * from %s WHERE(id == %d);",
        name, d.rows[d.pos][8])
    local qval = query(qstr) 

    if(qval[1] == nil) then
        curses.mvprintw(1, 3, qstr)
    else
        for k,v in pairs(qval[1]) do
            curses.mvprintw(k, 3, v)
        end
    end 

    d.sketch = d.rows[d.pos]
    d.top_pos = d.pos
    d.pos = 1
    curses.mvprintw(d.pos, 1, ">")
    d.page = 2

    curses.mvprintw(d.size, 0, name)
    return 1
end

function back(d)
    if (d.page == 1) then return 1 end
    d.page = 1
    curses.clear()
    print_page(d)
    return 1
end

function get_wav_file(pfx, tbl)
    return string.format("%s%s-%s.wav", 
        pfx, tbl[2], tbl[3])
end

function play(d)
    if(d.page == 2) then
        cmd = string.format("aplay %s 2> /dev/null &", get_wav_file(d.prefix, d.sketch))
        os.execute(cmd)
    end
    return 1
end

function stop(d)
    os.execute("killall aplay 2> /dev/null")
    return 1
end

function lock(d)
    if(d.page == 3) then
        d.page = 1
        print_page(d)
    else
	d.page = 3
        curses.clear()
        curses.mvprintw(0, 0, "Screen is locked. Hit 'L' to unlock") 
    end
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
tbl['p'] = play
tbl['s'] = stop
tbl['L'] = lock

run = 1
data = {}
data.rows = out
data.pos = 1
data.size = 20
data.page = 1
data.top_pos = 1
data.sketch = nil
data.prefix = "../smp/brian/"

print_page(data)

while(run == 1) do
    ch = curses.getch()
    curses.refresh()
    if(type(tbl[string.char(ch)]) ~= 'nil') then
        run = tbl[string.char(ch)](data)
    end
end

curses.endwin()
