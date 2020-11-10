#! /usr/bin/gnuplot
set terminal epslatex colour clip
set grid
set output "performanceProfiles/primalE".E.".tex"
set xlabel "Deviation from the best bound"
set ylabel "\\% of instances"
set key right bottom
set xrange [1:]
set yrange [0:100]
set lmargin 0
set rmargin 0
set bmargin 0
set tmargin 0
plot "performanceProfiles/primalE".E.".csv" using 1:5 with steps linewidth 3 linecolor "dark-violet"title "CSF", \
     "performanceProfiles/primalE".E.".csv" using 1:3 with steps linewidth 3 linecolor "dark-spring-green" title "LGFF", \
     "performanceProfiles/primalE".E.".csv" using 1:6 with steps linewidth 3 linecolor "skyblue" title "GRASP", \
     "performanceProfiles/primalE".E.".csv" using 1:4 with steps linewidth 3 linecolor "orange" title "GRASP + CSF", \
     "performanceProfiles/primalE".E.".csv" using 1:2 with steps linewidth 3 linecolor "light-goldenrod" title "GRASP + LGFF"

