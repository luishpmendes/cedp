#!/bin/bash

IFS=",";

make clean;

echo "StatisticsCalculator";
make StatisticsCalculatorExec;

./bin/exec/StatisticsCalculatorExec < statistics/statistics.txt > statistics/stats.csv;

echo "StatisticsCalculatorT";
make StatisticsCalculatorTExec;

for T in grid random
do
    echo "T="$T;
    ./bin/exec/StatisticsCalculatorTExec -T $T < statistics/statistics.txt >> statistics/stats.csv;
done

echo "StatisticsCalculatorM";
make StatisticsCalculatorMExec;

for m in 5 10
do
    echo "m="$m;
    ./bin/exec/StatisticsCalculatorMExec -m $m < statistics/statistics.txt >> statistics/stats.csv;
done

echo "StatisticsCalculatorB";
make StatisticsCalculatorBExec;

for B in 0.5 1.0
do
    echo "B="$B;
    ./bin/exec/StatisticsCalculatorBExec -B $B < statistics/statistics.txt >> statistics/stats.csv;
done

echo "StatisticsCalculatorD";
make StatisticsCalculatorDExec;

for D in 0.5 1.0
do
    echo "D="$D;
    ./bin/exec/StatisticsCalculatorDExec -D $D < statistics/statistics.txt >> statistics/stats.csv;
done

echo "StatisticsCalculatorV";
make StatisticsCalculatorVExec;

for V in 25 49 100
do
    echo "V="$V;
    ./bin/exec/StatisticsCalculatorVExec -V $V < statistics/statistics.txt >> statistics/stats.csv;
done

echo "StatisticsCalculatorE";
make StatisticsCalculatorEExec;

for E in 24,48,99 32,66,140 40,84,180
do
    set $E;
    E1=$1;
    echo "E1="$E1;
    E2=$2;
    echo "E2="$E2;
    E3=$3;
    echo "E3="$E3;
    ./bin/exec/StatisticsCalculatorEExec -E1 $E1 -E2 $E2 -E3 $E3 < statistics/statistics.txt >> statistics/stats.csv;
done

make clean;

