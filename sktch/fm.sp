# FM patch
# Paul Batchelor
# August 2016
"fm: {" say
_dbfm "db/brian.db" cdbload

_ctrlfm 20 'ctrl' _dbfm cdb slist
_ctrlfm slick "freq1" print load 60 200 scale 0.001 port
_ctrlfm slick "amp1" print load 0 0.3 scale 0.001 port
1.01
_ctrlfm slick "mod1" print load 0 5 scale floor
_ctrlfm slick "index1" print load 1 3 scale
fm

_ctrlfm slick "freq2" print load 200 300 scale
_ctrlfm slick "amp2" print load 0 0.3 scale 0.001 port
_ctrlfm slick "car2" print load 0 3 scale
_ctrlfm slick "mod2" print load 0 3 scale
_ctrlfm slick "index2" print load 1 8 scale
fm
_ctrlfm slick "crossfade" print load cf
dup
_ctrlfm slick "feedback" print load 0 0.9 scale
_ctrlfm slick "delay_time" print load 0.01 0.5 scale
0.9 vdelay -5 ampdb * +
dup jcrev _ctrlfm slick "reverb_level" print load 0.4 2 scale 0.003 port * +
-6 ampdb *
"}" say
