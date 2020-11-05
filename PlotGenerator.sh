#!/bin/bash

mkdir -p plots;

IFS=",";

echo "PlotGenerator";
make PlotGeneratorExec;

N=30;

for solver in "BnBSolverA" "BnCSolverA" "BnBSolverB" "BnCSolverB" "GRASPSolver"
do
    echo "solver="$solver;
    for m in 5 10
    do
        echo "m="$m;
        for VE in 25,24 25,32 25,40 49,48 49,66 49,84 100,99 100,140 100,180
        do
            set $VE;
            V=$1;
            echo "V="$V;
            E=$2;
            echo "E="$E;
            for B in 0.5 1.0
            do
                echo "B="$B;
                for D in 0.5 1.0
                do
                    echo "D="$D;

                    solutionFilename="solutions/grid-m"$m"V"$V"E"$E"B"${B//.}"D"${D//.}$solver".sol";

                    echo $solutionFilename;

                    if [ -f $solutionFilename ]; then

                        ./bin/exec/PlotGeneratorExec --solver $solver -m $m -V $V -E $E -B ${B//.} -D ${D//.} --N $N;

                        gnuplot -e "solver = '$solver'; m = '$m'; V = '$V'; E = '$E'; B = '${B//.}';D = '${D//.}'; N = '$N'" plots/PlotGenerator.plt;
                    fi
                done
            done
        done
    done
done

make clean;

