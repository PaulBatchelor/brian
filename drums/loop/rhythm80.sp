_wav "hohner_wav" _ns cdb loadfile
_tempo get _kick slick "kick" print prop 
0 44100 "hohner_ini" _ns cdb _wav nsmp
_tempo get _snare slick "snare" print prop dup 
1 3 trand floor 44100 "hohner_ini" _ns cdb _wav nsmp 
_tempo get _hh slick "hh" print prop dup 
3 44100 "hohner_ini" _ns cdb _wav nsmp 
swap 0.1 1 trand * 
+ +
