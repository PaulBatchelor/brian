"{" say

# Comment this out to run with specific seed via -s flag
0 4294967295 rand srand

_db 'db/brian.db' cdbload
_choose 5 'brian/top.txt' slist

_sketch 20
_choose slick _db cdb "top_file" print slist

_sketch slick "sketch" print load 

"}" say
