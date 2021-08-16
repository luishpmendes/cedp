#!/bin/bash

mkdir -p statistics
mkdir -p solutions

timeLimit=3600
echo "timeLimit="$timeLimit
psiSize=20
echo "psiSize="$psiSize
k=500
echo "k="$k

Ts=(grid random)
ms=(5)
Bs=(05 10)
Ds=(05 10)
VEs=(25,24 49,48 100,99)

for T in ${Ts[@]}
do
    echo "T: "$T
    for m in ${ms[@]}
    do
        echo "m: "$m
        for B in ${Bs[@]}
        do
            echo "B: "$B
            for D in ${Ds[@]}
            do
                echo "D: "$D
                for VE in ${VEs[@]}
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

