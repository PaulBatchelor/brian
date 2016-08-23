_wav "jomox_wav" _ns cdb loadfile
_tempo get _kick slick "kick" print prop 
0 44100 "jomox_ini" _ns cdb _wav nsmp
_tempo get _snare slick "snare" print prop dup 
1 10 trand floor 44100 "jomox_ini" _ns cdb _wav nsmp 
_tempo get _hh slick "hh" print prop dup 
dup 11 13 trand 44100 "jomox_ini" _ns cdb _wav nsmp 
swap 0.1 1 trand * 
+ +
