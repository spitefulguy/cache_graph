set terminal postscript eps;
set output "graph.ps"
set xlabel "working set size, kb"
set ylabel "CPU cycles"
set xtics 256
set xtics add (32, 64, 128)
set mytics
set grid
set title "Data access time"
set linestyle 1 lt 1 lc 1 lw 3 pt 2 ps 1
set linestyle 2 lt 1 lc 2 lw 3 pt 2 ps 1
plot "output_linear" using 1:2 title "Linear access" with lines linestyle 1, \
"output_random" using 1:2 title "Random access" with lines linestyle 2
