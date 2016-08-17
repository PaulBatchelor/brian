# shift between 16nth at quarter triplets
101 150 rand dup dup
bpm2dur dmetro 0.5 maytrig
swap 1.5 * bpm2dur dmetro
rot 4 * bpm2dur dmetro switch 0.1 0.9 (0.1 2 1 randh) randi maytrig
