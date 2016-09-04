# visy 2011-09-18
# t*(((t>>9)|(t>>13))&(25&(t>>6)))

# Expect a value from the stack
_v var
_v set
_t var

_v get 8000 10000 scale metro 1 0 (sr 1000 *) 0 incr _t set

(_t get
((_t get 9 >> _t get (_v get 8 16 scale floor) >> |)
((_v get 1 64 scale) (_t get 6 >>) &) &) *)

255 & 255 inv * 
