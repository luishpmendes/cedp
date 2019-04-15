#!/bin/bash

IFS=",";

mkdir -p graphs;
mkdir -p instances;

echo "InstanceGenerator";
make GraphGeneratorExec;
make InstanceGeneratorExec;

maxDemand=100;

echo "Grid"

for VE in 25,24 25,32 25,40 49,48 49,66 49,84 100,99 100,140 100,180
do
    set $VE;
    V=$1;
    echo "V="$V;
    E=$2;
    echo "E="$E;
    ./bin/exec/GraphGeneratorExec -V $V -E $E --grid --euclidean \
        --max-demand $maxDemand > "graphs/grid-V"$V"E"$E".in";
    for m in 5 10
    do
        echo "m="$m;
        for B in 0.5 1.0
        do
            echo "B="$B;
            for D in 0.5 1.0
            do
                echo "D="$D;

                ./bin/exec/InstanceGeneratorExec -m $m -B $B -D $D < \
                    "graphs/grid-V"$V"E"$E".in" > \
                    "instances/grid-m"$m"V"$V"E"${E}"B"${B//.}"D"${D//.}".in";
            done
        done
    done
done

echo "Random"


for VE in 25,24 25,32 25,40 49,48 49,66 49,84 100,99 100,140 100,180
do
    set $VE;
    V=$1;
    echo "V="$V;
    E=$2;
    echo "E="$E;
    ./bin/exec/GraphGeneratorExec -V $V -E $E --euclidean \
        --max-demand $maxDemand > "graphs/random-V"$V"E"$E".in";
    for m in 5 10
    do
        echo "m="$m;
        for B in 0.5 1.0
        do
            echo "B="$B;
            for D in 0.5 1.0
            do
                echo "D="$D;

                ./bin/exec/InstanceGeneratorExec -m $m -B $B -D $D < \
                    "graphs/random-V"$V"E"$E".in" > \
                    "instances/random-m"$m"V"$V"E"${E}"B"${B//.}"D"${D//.}".in";
            done
        done
    done
done

make clean;

