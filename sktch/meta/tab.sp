"tab: {" say
_dbtab 'db/brian.db' cdbload
_sltab 20 'sktch' _dbtab cdb slist
_tabtab sr 10 * _sltab slick "file" print gen_sporth

_tabtab tbldur inv 0 phasor dup

0 1 2 1 1 3 jitter + randi
0.4 1 
3 dmetro 0.8 maytrig 0.1 0.2 10 rand switch 

randi cf 
0.3 1 2 4 rand randh dmetro 0.8 maygate 0.005 port cf

1 0 0 _tabtab tabread
dup -12 -7 rand floor 1024 512 pshift + -3 ampdb *
"}" say
