"waveset: {" say
_db 'db/brian.db' cdbload
_sl 20 'sktch' _db cdb slist
_mod 10 'mod' _db cdb slist


[ _sl slick  "file" print load ]

3 8 rand floor "stretch" print 5.0 waveset

[ _mod slick "mod" print load ]

dup dup 0.4 0.97 rand "decay" print 1000 10000 rand revsc 
drop -30 -15 rand "amp" print ampdb * dcblk + 

"}" say
