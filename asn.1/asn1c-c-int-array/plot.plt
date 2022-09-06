set terminal png size 1000,300 enhanced font "Helvetica,20"
set output 'output.png'
set xlabel 'generation'
set ylabel 'time (ms)'
plot 'results.dat' using 1 with linespoints title 'encoding', \
     'results.dat' using 2 with linespoints title 'decoding'
