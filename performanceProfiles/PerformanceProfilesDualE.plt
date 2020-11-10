#! /usr/bin/gnuplot
set terminal epslatex colour clip
set grid
set output "performanceProfiles/dualE".E.".tex"
set xlabel "Deviation from the best bound"
set ylabel "\\% of instances"
set key right bottom
set xrange [1:]
set yrange [0:100]
set lmargin 0
set rmargin 0
set bmargin 0
set tmargin 0
plot "performanceProfiles/dualE".E.".csv" using 1:5 with steps linewidth linecolor "dark-violet" 3 title "CSF", \
     "performanceProfiles/dualE".E.".csv" using 1:3 with steps linewidth linecolor "dark-spring-green" 3 title "LGFF", \
     "performanceProfiles/dualE".E.".csv" using 1:4 with steps linewidth linecolor "orange" 3 title "GRASP + CSF", \
     "performanceProfiles/dualE".E.".csv" using 1:2 with steps linewidth linecolor "light-goldenrod" 3 title "GRASP + LGFF"

