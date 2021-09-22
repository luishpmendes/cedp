#! /usr/bin/gnuplot
set terminal epslatex colour clip size 3,3
set key off
set size square
set xrange [0:(sqrt(V)-0.5)]
set yrange [0:(sqrt(V)-0.5)]
set format x ""
set format y ""
set lmargin 0
set rmargin 0
set bmargin 0
set tmargin 0

array cores[10]
cores[1] = "#FF0000"
cores[2] = "#0000FF"
cores[3] = "#FFFF00"
cores[4] = "#FF00FF"
cores[5] = "#00FF00"
cores[6] = "#00FFFF"
cores[7] = "#FF9900"
cores[8] = "#9900FF"
cores[9] = "#00FF99"
cores[10] = "#FF0099"

if (solver eq "BnCSolverB") {
        titulo = "CSF"
}
if (solver eq "BnBSolverB") {
    titulo = "LGFF"
}
if (solver eq "GRASPB") {
    titulo = "GRASP without filter"
}
if (solver eq "GRASPA") {
    titulo = "GRASP with filter"
}
if (solver eq "BnCSolverA") {
        titulo = "GRASP + CSF"
}
if (solver eq "BnBSolverA") {
    titulo = "GRASP + LGFF"
}

set title titulo

set output "plots/grid-m".m."V".V."E".E."B".B."D".D.solver.".tex"
district = "plots/grid-m".m."V".V."E".E."B".B."D".D.solver."District"
vertices = "plots/grid-m".m."V".V."E".E."B".B."D".D.solver.".txt"

plot for [i=0:m-1] district.i.".txt" with lines linetype 1 linewidth 3 linecolor rgbcolor cores[i+1] title "$\\mathcal{E}_{".(i+1)."}$", vertices using 1:2 with points pointtype 7 pointsize 0.3 linecolor rgb "black" notitle

