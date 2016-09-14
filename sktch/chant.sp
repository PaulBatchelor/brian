(
'chant: {' say
'env' 4096 '0.5 0.5 270 0.5' gen_composite
'sine' 4096 gen_sine

'forms_oo' '400 750 2400 2600 2900' gen_vals
'amp_oo' '0 -11 -21 -20 -40' gen_vals
'bw_oo' '40 80 100 120 120' gen_vals

'forms_ee' '400 1620 2400 2800 3100' gen_vals
'amp_ee' '0 -12 -9 -12 -18' gen_vals
'bw_ee' '40 80 100 120 120' gen_vals


0 1 3 randi 0 1 biscale 3 pset

_db 'db/brian.db' cdbload

_seq 15 'seq' _db cdb slist

'scale'
_seq slick 'sequence' print

gen_vals

0.5 1.5 rand "rate" print  metro 0.4 0.6 rand "prob" print maytrig tick +

dup dup 1 0 3 0 incr 2 eq *
swap

1 'scale' tseq 12 min dup 0.1 port switch
0.1 1 10 jitter + 38 49 rand floor 'key' print + mtof 0 pset

0.5 1 pset

1 p 0 p
0 'forms_oo' tget 3 p * 0 'forms_ee' tget 1 3 p - * +
1
0 'bw_oo' tget 3 p * 0 'bw_ee' tget 1 3 p - * +
0.001 0.001 0.02 0 100 'env' 'sine' fof
0 'amp_oo' tget 3 p * 0 'amp_ee' tget 1 3 p - * + ampdb *

1 p 0 p
1 'forms_oo' tget 3 p * 1 'forms_ee' tget 1 3 p - * +
1
1 'bw_oo' tget 3 p * 1 'bw_ee' tget 1 3 p - * +
0.001 0.001 0.02 0 100 'env' 'sine' fof
1 'amp_oo' tget 3 p * 1 'amp_ee' tget 1 3 p - * + ampdb * +

1 p 0 p
2 'forms_oo' tget 3 p * 2 'forms_ee' tget 1 3 p - * +
1
2 'bw_oo' tget 3 p * 2 'bw_ee' tget 1 3 p - * +
0.001 0.001 0.02 0 100 'env' 'sine' fof
2 'amp_oo' tget 3 p * 2 'amp_ee' tget 1 3 p - * + ampdb * +

1 p 0 p
3 'forms_oo' tget 3 p * 3 'forms_ee' tget 1 3 p - * +
1
3 'bw_oo' tget 3 p * 3 'bw_ee' tget 1 3 p - * +
0.001 0.001 0.02 0 100 'env' 'sine' fof
3 'amp_oo' tget 3 p * 3 'amp_ee' tget 1 3 p - * + ampdb * +

1 p 0 p
4 'forms_oo' tget 3 p * 4 'forms_ee' tget 1 3 p - * +
1
4 'bw_oo' tget 3 p * 4 'bw_ee' tget 1 3 p - * +
0.001 0.001 0.02 0 100 'env' 'sine' fof
4 'amp_oo' tget 3 p * 4 'amp_ee' tget 1 3 p - * + ampdb * +

0 p 0.1 tri +

4000 butlp

0.8 *
dup dup 11 6 10000 zrev 0.03 * drop 500 buthp +

'}' say
)
