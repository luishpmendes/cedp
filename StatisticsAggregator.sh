#!/bin/bash

make StatisticsAggregatorExec;

IFS=",";
N=30;

for solver in "BnBSolverA" "BnCSolverA" "BnBSolverB" "BnCSolverB" "GRASPSolver"
do
    echo "solver="$solver;
    for type in "grid" "random"
    do
        echo "type="$type;
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

                        ./bin/exec/StatisticsAggregatorExec --solver $solver \
                            --type $type -D $D \
                            < "statistics/"$type"-m"$m"V"$V"E"$E"B"${B//.}"D"${D//.}$solver".stat" \
                            >> statistics/statistics.txt;
                    done;
                done;
            done;
        done;
    done;
done;

