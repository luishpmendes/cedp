#! /usr/bin/gnuplot
set terminal epslatex colour
set grid
set output "performanceProfiles/dualV".V.".tex"
set title "Dual bound for instances with $|V| = ".V."$"
set xlabel "Deviation from the best bound"
set ylabel "\\% of instances"
set key right bottom
set xrange [1:]
set yrange [0:100]
plot "performanceProfiles/dualV".V.".csv" using 1:5 with steps linewidth 3 linecolor "dark-violet" title "CSF", \
     "performanceProfiles/dualV".V.".csv" using 1:3 with steps linewidth 3 linecolor "dark-spring-green" title "LGFF", \
     "performanceProfiles/dualV".V.".csv" using 1:4 with steps linewidth 3 linecolor "orange" title "GRASP + CSF", \
     "performanceProfiles/dualV".V.".csv" using 1:2 with steps linewidth 3 linecolor "light-goldenrod" title "GRASP + LGFF"

