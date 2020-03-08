#! /usr/bin/gnuplot
set terminal epslatex colour
set grid
set output "performanceProfiles/primalM".m.".tex"
set xlabel "Deviation from the best bound"
set ylabel "\\% of instances"
set key right bottom
set xrange [1:]
set yrange [0:100]
set rmargin 0
set tmargin 0
plot "performanceProfiles/primalM".m.".csv" using 1:2 with steps linewidth 3 title "B\\&B", "performanceProfiles/primalM".m.".csv" using 1:3 with steps linewidth 3 title "B\\&C", "performanceProfiles/primalM".m.".csv" using 1:4 with steps linewidth 3 title "GRASP"

