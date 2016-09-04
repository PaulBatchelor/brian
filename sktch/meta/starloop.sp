"starloop: {" say 
_db "db/brian.db" cdbload
_sktch 20 "sktch" _db cdb slist
7 _sktch sget render -4 ampdb * dcblk
6 _sktch sget render 500 buthp dcblk 
3 8 rand dmetro 0.8 maytrig tick + tog 1.4 1 0.5 1.4 adsr  *
dup
10 20 rand inv 1 sine 300 8000 biscale 0.1 moogladder bal -3 ampdb *
+ 

0.001 0.2 -10 peaklim -0.4 ampdb clip 
"}" say 
