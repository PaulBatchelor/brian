# zitareverb

dup
#delay, ms
10 60 rand
#crossover freq
100 300 rand
# rt60_low
1.0 10 rand
# rt60_mid
1.0 10 rand
# damping
1000 10000 rand
# eq1 freq, level
200 500 rand -3 4 rand
# eq2 freq, level
1000 4000 rand -3 4 rand
# mix
0.5 1 rand
# level
1 4 rand
zitarev drop
