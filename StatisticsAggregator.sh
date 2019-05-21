#!/bin/bash

make StatisticsAggregatorExec;

IFS=",";
N=30;

for solver in "BnBSolver" "BnCSolver" "GRASPSolver"
do
    for type in "grid" "random"
    do
        for m in 5 10
        do
            for VE in 25,24 25,32 25,40 49,48 49,66 49,84 100,99 100,140 100,180
            do
                set $VE;
                V=$1;
                E=$2;
                for B in 0.5 1.0
                do
                    for D in 0.5 1.0
                    do
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

