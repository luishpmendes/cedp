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
plot "performanceProfiles/primalE".E.".csv" using 1:5 with steps linewidth 3 linecolor 1 title "CSF", \
     "performanceProfiles/primalE".E.".csv" using 1:3 with steps linewidth 3 linecolor 2 title "LGFF", \
     "performanceProfiles/primalE".E.".csv" using 1:7 with steps linewidth 3 linecolor 3 title "GRASP without filter", \
     "performanceProfiles/primalE".E.".csv" using 1:6 with steps linewidth 3 linecolor 4 title "GRASP with filter", \
     "performanceProfiles/primalE".E.".csv" using 1:4 with steps linewidth 3 linecolor 5 title "GRASP + CSF", \
     "performanceProfiles/primalE".E.".csv" using 1:2 with steps linewidth 3 linecolor 6 title "GRASP + LGFF"

