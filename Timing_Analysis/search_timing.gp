set xlabel 'Number of Tweets'
set ylabel 'Time Elapsed (s)'
plot 'MapAndVector_out.txt' using 1:3 with lines title "MapAndVector", \
'UnOrderedMapAndVector_out.txt' using 1:3 with lines title "UnOrderedMapAndVector"

set terminal png size 1024,768
set output "search_timing_plot.png"
replot
exit # and we’re done!