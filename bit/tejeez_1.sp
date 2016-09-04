# tejeez 2011-09-18
# (t*(t>>5|t>>8))>>(t>>16)

_v var

# Expect a value from the stack
_v set

_t var
8000 metro 1 0 (sr 1000 *) 0 incr _t set

(_t get (_t get 5 >> _t get (_v get 1 9 scale) >> |) *)
(_t get 16 >>) >>

255 & 255 inv * 
