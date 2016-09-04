# viznut 2011-09-18
# t*(((t>>12)|(t>>8))&(63&(t>>4)))

# Expect a value 
_v var
_v set

_t var
8000 metro 1 0 (sr 1000 *) 0 incr _t set

_t get
(_t get 12 >> _t get 8 >>  |)
(_v get 0 255 scale floor (_t get 4 >>) &) & *

255 & 255 inv * 
