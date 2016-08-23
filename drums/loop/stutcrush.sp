_div 128 "2 0.1 8 0.3 16 0.1 32 0.4 64 0.1" gen_rand
_rep "3 5 7 8" gen_vals


_clk get 20 inv 1 sine 0 0.8 biscale maytrig _tempo get 
(_clk get 1 _div tseq) 
(_clk get 1 _rep tseq) 
1.0 rpt

100 buthp

3 dup inv 0.1 0.0 dist 
0.3 clip 
0.001 0.001 -25 peaklim 
