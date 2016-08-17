"plk: {" say
_dbplk "db/brian.db" cdbload
_sqlplk 20 "seq" _dbplk cdb slist
_clklplk 20 "clk" _dbplk cdb slist
_ctlplk 20 "ctrl" _dbplk cdb slist
_seqplk [ _sqlplk slick "seq" print ] gen_vals
_dryplk var
_clkplk var


[ _clklplk slick "clock" print load ]

0.7 maytrig _clkplk set

_clkplk get
_clkplk get 1 _seqplk tseq 55 62 rand floor "key" print  + mtof
_clkplk get 0.2 0.4 trand 300 pluck

_clkplk get 0.005 0.1 0.2 tenvx *

dup 0.8 _clkplk get 0.1 0.4 trand 0.5 64 smoothdelay
#3 15 1 randi inv 1 sine 0 1 biscale
[ _ctlplk slick "octave_level" print load ]
-1 -4 ampdb scale *
12 1024 512 pshift 2100 butlp 500 buthp
+

_dryplk set

_dryplk get
dup 3000 butlp 0.9 0.75 delay -9 ampdb * +

dup 0.93 0.97 rand 5000 10000 rand revsc drop
[ _ctlplk slick "reverb_level" print load ] 
-16 -6 scale ampdb 0.5 port *

_dryplk get 0.8 0.5 1.3 rand delay 1000 butlp -7 ampdb *
0.1 0.5 3 jitter 1024 512 pshift
+
_dryplk get +
-2 ampdb *
"}" say
