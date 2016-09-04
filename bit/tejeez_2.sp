# tejeez 2011-09-18
# t*(((t>>11)&(t>>8))&(123&(t>>3)))

# Expects a value from the stack
_v var
_v set

_t var _v get 8000 12000 scale metro 1 0 (sr 1000 *) 0 incr _t set

_t get
( (_t get 11 >>) (_t get 8 >>) &)
(_v get 12 123 scale (_t get 3 >>) & ) & *

255 & 255 inv * 
