_wav "909_wav" _ns cdb loadfile
_tempo get _kick slick "kick" print prop 
0 44100 "909_ini" _ns cdb  _wav nsmp
_tempo get _snare slick "snare" print prop dup
1 44100 "909_ini" _ns cdb _wav nsmp 
swap 1000 10000 trand 1.3 1.0 wpkorg35 
_tempo get _hh slick "hh" print prop dup 
4 44100 "909_ini" _ns cdb _wav nsmp 
swap 0.1 1 trand * 
+ +
