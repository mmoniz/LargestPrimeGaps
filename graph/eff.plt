set title "Efficency for Max Gap of Primes"
set xlabel "Number of Processes (p)"
set ylabel "Efficency"
set key right
plot "eff1.txt" title 'N=10E6' with lines, \
"eff2.txt" title 'N=10E8' with lines, \
"eff3.txt" title 'N=10E9' with lines