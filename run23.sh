#!/bin/bash

mkdir -p statistics;
mkdir -p solutions;

timeLimit=3600;

echo "BnBSolver";
make BnBSolverExec;

for instance in grid-m10V25E40B10D05 grid-m10V100E140B10D05 random-m10V49E48B10D05 random-m10V100E180B10D05
do
    echo "Instance: "$instance;
    echo "Start time: "$(date);
    ./bin/exec/BnBSolverExec --instance "instances/"$instance".in" \
        --time-limit $timeLimit \
        --statistics "statistics/"$instance"BnBSolver.stat" \
        --solution "solutions/"$instance"BnBSolver.sol";
    echo "End time: "$(date);
done

echo "BnCSolver";
make BnCSolverExec;

for instance in grid-m10V25E40B10D05 grid-m10V100E140B10D05 random-m10V49E48B10D05 random-m10V100E180B10D05
do
    echo "Instance: "$instance;
    echo "Start time: "$(date);
    ./bin/exec/BnCSolverExec --instance "instances/"$instance".in" \
        --time-limit $timeLimit \
        --statistics "statistics/"$instance"BnCSolver.stat" \
        --solution "solutions/"$instance"BnCSolver.sol";
    echo "End time: "$(date);
done

echo "GRASPSolver";
make GRASPSolverExec;
m=10;
echo "m="$m;
k=100;
echo "k="$k;

for instance in grid-m10V25E40B10D05 grid-m10V100E140B10D05 random-m10V49E48B10D05 random-m10V100E180B10D05
do
    echo "Instance: "$instance;
    echo "Start time: "$(date);
    ./bin/exec/GRASPSolverExec --instance "instances/"$instance".in" \
        --time-limit $timeLimit --m $m --k $k \
        --statistics "statistics/"$instance"GRASPSolver.stat" \
        --solution "solutions/"$instance"GRASPSolver.sol";
    echo "End time: "$(date);
done

echo "Finished";
