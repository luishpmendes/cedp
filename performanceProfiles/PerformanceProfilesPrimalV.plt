#! /usr/bin/gnuplot
set terminal epslatex colour
set grid
set output "performanceProfiles/primalV".V.".tex"
set title "Primal bound for instances with $|V| = ".V."$"
set xlabel "Deviation from the best bound"
set ylabel "\\% of instances"
set key right bottom
set xrange [1:]
set yrange [0:100]
plot "performanceProfiles/primalV".V.".csv" using 1:5 with steps linewidth 3 linecolor 1 title "CSF", \
     "performanceProfiles/primalV".V.".csv" using 1:3 with steps linewidth 3 linecolor 2 title "LGFF", \
     "performanceProfiles/primalV".V.".csv" using 1:7 with steps linewidth 3 linecolor 3 title "GRASP without filter", \
     "performanceProfiles/primalV".V.".csv" using 1:6 with steps linewidth 3 linecolor 4 title "GRASP with filter", \
     "performanceProfiles/primalV".V.".csv" using 1:4 with steps linewidth 3 linecolor 5 title "GRASP + CSF", \
     "performanceProfiles/primalV".V.".csv" using 1:2 with steps linewidth 3 linecolor 6 title "GRASP + LGFF"

