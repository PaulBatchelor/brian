"mince: {" say
_dbmince 'db/brian.db' cdbload
_slmince 20 'sktch' _dbmince cdb slist
_tabmince sr 5 15 rand * [ _slmince slick ] "file" print gen_sporth

_tabmince tbldur inv 
-1 1 0.3 randi *

0 _tabmince tbldur 8 25 rand randh 

2 5 rand dmetro 0.3 0.8 rand maygate 0.05 0.2 rand port cf

0 phasor _tabmince tbldur *
1 1 4 rand floor _tabmince mincer 
"}" say
