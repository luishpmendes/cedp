#!/bin/bash

IFS=",";

make clean;

echo "PerformanceProfilesPrimal";
make PerformanceProfilesPrimalExec;

./bin/exec/PerformanceProfilesPrimalExec < statistics/statistics.txt \
        > performanceProfiles/primal.csv;
gnuplot performanceProfiles/PerformanceProfilesPrimal.plt;

echo "PerformanceProfilesDual";
make PerformanceProfilesDualExec;

./bin/exec/PerformanceProfilesDualExec < statistics/statistics.txt \
        > performanceProfiles/dual.csv;
gnuplot performanceProfiles/PerformanceProfilesDual.plt;

echo "PerformanceProfilesPrimalT";
make PerformanceProfilesPrimalTExec;

for T in grid random
do
    echo "T="$T;
    ./bin/exec/PerformanceProfilesPrimalTExec -T $T < statistics/statistics.txt \
        > "performanceProfiles/primalT"${T}".csv";
    gnuplot -e "T = '$T'" performanceProfiles/PerformanceProfilesPrimalT.plt;
done

echo "PerformanceProfilesDualT";
make PerformanceProfilesDualTExec;

for T in grid random
do
    echo "T="$T;
    ./bin/exec/PerformanceProfilesDualTExec -T $T < statistics/statistics.txt \
        > "performanceProfiles/dualT"${T}".csv";
    gnuplot -e "T = '$T'" performanceProfiles/PerformanceProfilesDualT.plt;
done

echo "PerformanceProfilesPrimalM";
make PerformanceProfilesPrimalMExec;

for m in 5 10
do
    echo "m="$m;
    ./bin/exec/PerformanceProfilesPrimalMExec -m $m < statistics/statistics.txt \
        > "performanceProfiles/primalM"${m}".csv";
    gnuplot -e "m = '$m'" performanceProfiles/PerformanceProfilesPrimalM.plt;
done

echo "PerformanceProfilesDualM";
make PerformanceProfilesDualMExec;

for m in 5 10
do
    echo "m="$m;
    ./bin/exec/PerformanceProfilesDualMExec -m $m < statistics/statistics.txt \
        > "performanceProfiles/dualM"${m}".csv";
    gnuplot -e "m = '$m'" performanceProfiles/PerformanceProfilesDualM.plt;
done

echo "PerformanceProfilesPrimalB";
make PerformanceProfilesPrimalBExec;

for B in 0.5 1.0
do
    echo "B="$B;
    ./bin/exec/PerformanceProfilesPrimalBExec -B $B < statistics/statistics.txt \
        > "performanceProfiles/primalB"${B}".csv";
    gnuplot -e "B = '$B'" performanceProfiles/PerformanceProfilesPrimalB.plt;
done

echo "PerformanceProfilesDualB";
make PerformanceProfilesDualBExec;

for B in 0.5 1.0
do
    echo "B="$B;
    ./bin/exec/PerformanceProfilesDualBExec -B $B < statistics/statistics.txt \
        > "performanceProfiles/dualB"${B}".csv";
    gnuplot -e "B = '$B'" performanceProfiles/PerformanceProfilesDualB.plt;
done

echo "PerformanceProfilesPrimalD";
make PerformanceProfilesPrimalDExec;

for D in 0.5 1.0
do
    echo "D="$D;
    ./bin/exec/PerformanceProfilesPrimalDExec -D $D < statistics/statistics.txt \
        > "performanceProfiles/primalD"${D}".csv";
    gnuplot -e "D = '$D'" performanceProfiles/PerformanceProfilesPrimalD.plt;
done

echo "PerformanceProfilesDualD";
make PerformanceProfilesDualDExec;

for D in 0.5 1.0
do
    echo "D="$D;
    ./bin/exec/PerformanceProfilesDualDExec -D $D < statistics/statistics.txt \
        > "performanceProfiles/dualD"${D}".csv";
    gnuplot -e "D = '$D'" performanceProfiles/PerformanceProfilesDualD.plt;
done

echo "PerformanceProfilesPrimalV";
make PerformanceProfilesPrimalVExec;

for V in 25 49 100
do
    echo "V="$V;
    ./bin/exec/PerformanceProfilesPrimalVExec -V $V < statistics/statistics.txt \
        > "performanceProfiles/primalV"${V}".csv";
    gnuplot -e "V = '$V'" performanceProfiles/PerformanceProfilesPrimalV.plt;
done

echo "PerformanceProfilesDualV";
make PerformanceProfilesDualVExec;

for V in 25 49 100
do
    echo "V="$V;
    ./bin/exec/PerformanceProfilesDualVExec -V $V < statistics/statistics.txt \
        > "performanceProfiles/dualV"${V}".csv";
    gnuplot -e "V = '$V'" performanceProfiles/PerformanceProfilesDualV.plt;
done

echo "PerformanceProfilesPrimalE";
make PerformanceProfilesPrimalEExec;

for E in 24,32,40 48,66,84 99,140,180
do
    set $E;
    E1=$1;
    echo "E1="$E1;
    E2=$2;
    echo "E2="$E2;
    E3=$3;
    echo "E3="$E3;
    ./bin/exec/PerformanceProfilesPrimalEExec -E1 $E1 -E2 $E2 -E3 $E3 \
        < statistics/statistics.txt > "performanceProfiles/primalE"${E1}".csv";
    gnuplot -e "E = '$E1'" performanceProfiles/PerformanceProfilesPrimalE.plt;
done

echo "PerformanceProfilesDualE";
make PerformanceProfilesDualEExec;

for E in 24,32,40 48,66,84 99,140,180
do
    set $E;
    E1=$1;
    echo "E1="$E1;
    E2=$2;
    echo "E2="$E2;
    E3=$3;
    echo "E3="$E3;
    ./bin/exec/PerformanceProfilesDualEExec -E1 $E1 -E2 $E2 -E3 $E3 \
        < statistics/statistics.txt > "performanceProfiles/dualE"${E1}".csv";
    gnuplot -e "E = '$E1'" performanceProfiles/PerformanceProfilesDualE.plt;
done

make clean;

