"loop: {" say
_db "db/brian.db" cdbload
_ns "db/nsmp.db" cdbload

_t 7 "tempo" _db cdb slist

_tempo [ _t slick eval "tempo" print ] varset

_dry var

_kick 5 "kick" _db cdb slist
_snare 5 "snare" _db cdb slist
_hh 5 "hh" _db cdb slist

_drum 5  "drum" _db cdb slist

[ _drum slick "drum" print load ]

_dry set

_dry get 

_drumfx 5 "drumfx" _db cdb slist

_clk var
_tempo get 2 * bpm2dur dmetro _clk set

[ _drumfx slick "drumfx" print load ]

_dry get 0.1 0.9 rand cf

"}" say
