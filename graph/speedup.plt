set title "Speed Up for Max Gap of Primes"
set xlabel "Number of Processes (p)"
set ylabel "Speed Up"
set key left
plot "speedup1.txt" title 'N=10E6' with lines, \
"speedup2.txt" title 'N=10E8' with lines, \
"speedup3.txt" title 'N=10E9' with lines