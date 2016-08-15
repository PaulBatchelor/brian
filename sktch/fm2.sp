"fm2: {" say
_dbfm2 'db/brian.db' cdbload
_sqfm2 20 'seq' _dbfm2 cdb slist
_ctlfm2 20 'ctrl' _dbfm2 cdb slist
_clkfm2 20 'clk' _dbfm2 cdb slist

_seqfm2 _sqfm2 slick "seq" print gen_vals

_dryfm2 var
_tickfm2 var

_clkfm2 slick "clock" print load dup _tickfm2 set
_ctlfm2 slick "probability" print load 0.1 0.9 scale
maytrig tick + dup
1 dmetro 0.4 maygate _seqfm2 tseq 50 67 rand floor + 0.12 0.1 3 jitter +
0.001 0.01 rand port mtof
0.5 1 1 4 rand floor 0.001 +
_tickfm2 get 0.3 2 7 rand trand
fm

swap 0.001 0.1 rand dup 1.1 * _ctlfm2 slick "release" print 
load 0.05 0.5 scale tenvx *

dup
_ctlfm2 slick "feedback" print load 0.4 0.8 scale
0.3 1.8 rand delay -8 ampdb * 1000 butlp + dup _dryfm2 set

dup 8 20 rand 8 20 rand 1000 10000 rand zrev 1 1 sine 0 1 biscale cf
dup 0.2 0.7 rand
0.1 1 rand
1 sine 0 0.005 0.01 rand biscale 0.02 + 0.2 vdelay 0.1 0.8 rand cf
-9 -2.5 rand ampdb *
dup 0.8 1.5 delay -6 ampdb 300 buthp * +
_dryfm2 get +
-1 ampdb *
"}" say
