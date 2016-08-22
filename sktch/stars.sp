"stars: {" say
_db 'db/brian.db' cdbload
_seqlist  15 'seq' _db cdb slist
_mod 15 'mod' _db cdb slist
_seq _seqlist slick 'seq' print gen_vals

_tick var

_atk 0.5 2.1 rand "atk" print varset
_rel 1 3.5 rand "rel" print varset
_hold 0.9 varset
_key 57 69 rand floor "key" print varset

_amp 0.1 varset

_env var

30 70 rand "tempo" print bpm2dur dmetro _tick set

_tick get 6 15 rand 0 tdiv _atk get _hold get _rel get tenv _env set
0 _seq tget _key get + mtof _amp get
4 0
_env get 0.7 0.8 scale
gbuzz
_env get *

_tick get 6 15 rand 1 tdiv _atk get _hold get _rel get tenv _env set
1 _seq tget _key get + mtof _amp get
4 0
_env get 0.7 0.8 scale
gbuzz
_env get *

_tick get 6 11 rand 2 tdiv _atk get _hold get _rel get tenv _env set
2 _seq tget _key get + mtof _amp get
4 0
_env get 0.6 0.8 scale
gbuzz
_env get *

_tick get 6 15 rand 3 tdiv _atk get _hold get _rel get tenv _env set
3 _seq tget _key get + mtof _amp get
4 0
_env get 0.6 0.8 scale
gbuzz
_env get *

_tick get 6 13 rand 4 tdiv _atk get _hold get _rel get tenv _env set
4 _seq tget _key get + mtof _amp get
4 0
_env get 0.3 0.8 scale
gbuzz
_env get *

_tick get 10 26 rand 5 tdiv _atk get _hold get _rel get tenv _env set
5 _seq tget _key get + mtof _amp get
4 0
_env get 0.7 0.8 scale
gbuzz
_env get *


mix -10 ampdb *

dup _mod slick "fx" print load -20 -10 0.3 randi ampdb * +


dup dup 0.95 5000 10000 rand "rev_cutoff" print revsc drop -9 ampdb * +

0.001 0.01 -10 peaklim

"}" say
