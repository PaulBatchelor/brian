require("math")
math.randomseed(os.time())

cons = 
{"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "r", "s", "t", "v", 
"w", "z"}

vow = 
{"a", "e", "i", "o", "u", "y"}

wordlist = {}

function syl()
    return cons[math.random(#cons)] .. vow[math.random(#vow)]
end

function word()
    str = ""
    for i=1,math.random(3) do
        str = str .. syl()
    end
    if(math.random() > 0.2) then
        str = str .. cons[math.random(#cons)]
    end
    return str
end


function sentence()
    local str = word()
    str = str:gsub("^%l", string.upper)
    nwords = math.random(10)
    local punc = {",", ":", ";"}
    local ending = {".", ".", ".", "!", "?", "..."}
    table.insert(wordlist, word())
    curword = str 
    prevword = str 
    for i=1,nwords do

        if(math.random() < 0.7) then
            curword = word() 
            table.insert(wordlist, curword)
        else
            curword = wordlist[math.random(#wordlist)] 
        end

        str = str .. " " .. curword

        prevword = curword

        if(i ~= nwords and math.random() < 0.1) then
           str = str .. punc[math.random(#punc)] 
        end
    end
    return str .. ending[math.random(#ending)] .. " "
end

function paragraph()
    str = ""
    for i = 1, math.random(10) do
        str = str .. sentence()
    end
    return str .. "\n"
end

print(word())
