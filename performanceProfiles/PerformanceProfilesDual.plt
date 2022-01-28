#! /usr/bin/gnuplot
set terminal epslatex colour
set grid
set output "performanceProfiles/dual.tex"
set xlabel "Deviation from the best bound"
set ylabel "\\% of instances"
set key right bottom
set xrange [1:]
set yrange [0:100]
set rmargin 0
set tmargin 0
plot "performanceProfiles/dual.csv" using 1:5 with linespoints dashtype 1 linewidth 3 linecolor 1 linetype 1 pointtype 1 title "CSF", \
     "performanceProfiles/dual.csv" using 1:3 with linespoints dashtype 2 linewidth 3 linecolor 2 linetype 2 pointtype 2 title "LGFF", \
     "performanceProfiles/dual.csv" using 1:4 with linespoints dashtype 5 linewidth 3 linecolor 5 linetype 5 pointtype 5 title "GRASP + CSF", \
     "performanceProfiles/dual.csv" using 1:2 with linespoints dashtype 6 linewidth 3 linecolor 6 linetype 6 pointtype 6 title "GRASP + LGFF"

