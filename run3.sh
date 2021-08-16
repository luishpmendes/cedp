#!/bin/bash

IFS=","
mkdir -p statistics
mkdir -p solutions

timeLimit=3600
echo "timeLimit="$timeLimit
psiSize=20
echo "psiSize="$psiSize
k=500
echo "k="$k

for T in grid random
do
    echo "T: "$T
    for m in 5
    do
        echo "m: "$m
        for B in 05 10
        do
            echo "B: "$B
            for D in 05 10
            do
                echo "D: "$D
                for VE in 25,40 49,84 100,180
                do
                    set $VE
                    V=$1
                    E=$2
                    echo "V: "$V
                    echo "E: "$E
                    instance="${T}-m${m}V${V}E${E}B${B}D${D}"
                    echo "instance: "$instance
                    warmStartPercentageTime=0.1
                    echo "warmStartPercentageTime="$warmStartPercentageTime
                    echo "BnBSolverA"
                    command="./bin/exec/BnBSolverExec "
                    command+="--instance instances/${instance}.in "
                    command+="--time-limit ${timeLimit} "
                    command+="--warm-start-percentage-time $warmStartPercentageTime "
                    command+="--m ${psiSize} "
                    command+="--k ${k} "
                    command+="--statistical-filter "
                    command+="--statistics statistics/${instance}BnBSolverA.stat "
                    command+="--solution solutions/${instance}BnBSolverA.sol "
                    echo "Start time: "$(date)
                    eval $command
                    echo "End time: "$(date)
                    echo "BnCSolverA"
                    command="./bin/exec/BnCSolverExec "
                    command+="--instance instances/${instance}.in "
                    command+="--time-limit ${timeLimit} "
                    command+="--warm-start-percentage-time $warmStartPercentageTime "
                    command+="--m ${psiSize} "
                    command+="--k ${k} "
                    command+="--statistical-filter "
                    command+="--statistics statistics/${instance}BnCSolverA.stat "
                    command+="--solution solutions/${instance}BnCSolverA.sol "
                    echo "Start time: "$(date)
                    eval $command
                    echo "End time: "$(date)
                    warmStartPercentageTime=0.0
                    echo "warmStartPercentageTime="$warmStartPercentageTime
                    echo "BnBSolverB"
                    command="./bin/exec/BnBSolverExec "
                    command+="--instance instances/${instance}.in "
                    command+="--time-limit ${timeLimit} "
                    command+="--warm-start-percentage-time $warmStartPercentageTime "
                    command+="--m ${psiSize} "
                    command+="--k ${k} "
                    command+="--statistical-filter "
                    command+="--statistics statistics/${instance}BnBSolverB.stat "
                    command+="--solution solutions/${instance}BnBSolverB.sol "
                    echo "Start time: "$(date)
                    eval $command
                    echo "End time: "$(date)
                    echo "BnCSolverB"
                    command="./bin/exec/BnCSolverExec "
                    command+="--instance instances/${instance}.in "
                    command+="--time-limit ${timeLimit} "
                    command+="--warm-start-percentage-time $warmStartPercentageTime "
                    command+="--m ${psiSize} "
                    command+="--k ${k} "
                    command+="--statistical-filter "
                    command+="--statistics statistics/${instance}BnCSolverB.stat "
                    command+="--solution solutions/${instance}BnCSolverB.sol "
                    echo "Start time: "$(date)
                    eval $command
                    echo "End time: "$(date)
                    echo "GRASPSolverA"
                    command="./bin/exec/GRASPSolverExec "
                    command+="--instance instances/${instance}.in "
                    command+="--time-limit ${timeLimit} "
                    command+="--m ${psiSize} "
                    command+="--k ${k} "
                    command+="--statistical-filter "
                    command+="--statistics statistics/${instance}GRASPA.stat "
                    command+="--solution solutions/${instance}GRASPA.sol "
                    echo "Start time: "$(date)
                    eval $command
                    echo "End time: "$(date)
                    echo "GRASPSolverB"
                    command="./bin/exec/GRASPSolverExec "
                    command+="--instance instances/${instance}.in "
                    command+="--time-limit ${timeLimit} "
                    command+="--m ${psiSize} "
                    command+="--k ${k} "
                    command+="--statistics statistics/${instance}GRASPB.stat "
                    command+="--solution solutions/${instance}GRASPB.sol "
                    echo "Start time: "$(date)
                    eval $command
                    echo "End time: "$(date)
                done
            done
        done
    done
done

echo "Finished";

