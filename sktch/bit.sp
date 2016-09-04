"bit: {" say
_db "db/brian.db" cdbload
_ctrl 15 "ctrl" _db cdb slist
_bit 15 "bit" _db cdb slist
_mod 15 "mod" _db cdb slist

_ctrl slick "ctrl" print  render 
_bit slick "bit" print  render 
1 - 2 * dup
_mod slick "mod" print render 0 0.8 rand "crossfade" print cf
dcblk -3 ampdb *
"}" say
