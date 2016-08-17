"mold : {" say
_dbmold "db/brian.db" cdbload
_clkmold 10 "clk" _dbmold cdb slist
_modmold 10 "mod" _dbmold cdb slist
_ctrlmold 10 "ctrl" _dbmold cdb slist


_clkmold slick "clk1" print load dup

0.001 0.01 0.001 tenvx
swap 1000 3000 trand 0.4 sine *

_modmold slick "fx1" print load

_clkmold slick "clk2" print load dup
0.001 0.005 0.003 tenvx
swap -0.3 0.3 rot 1000 10000 trand randh *
_modmold slick "fx2" print load

_ctrlmold slick "crossfade" print load 0.1 0.9 scale cf

_modmold slick "fx3" print load
"}" say
