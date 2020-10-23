#!/bin/bash

mkdir -p statistics;
mkdir -p solutions;

timeLimit=3600;
echo "timeLimit="$m;
warmStartPercentageTime=0.1;
echo "warmStartPercentageTime="$warmStartPercentageTime;
m=10;
echo "m="$m;
k=100;
echo "k="$k;

echo "BnBSolverA";

for instance in grid-m10V25E24B05D05 grid-m10V25E32B05D10 grid-m10V25E40B10D05 \
                grid-m10V49E48B10D10 grid-m5V49E84B05D05 grid-m5V100E99B05D10 \
                grid-m5V100E140B10D05 grid-m5V100E180B10D10 \
                random-m10V25E24B05D05 random-m10V25E32B05D10 \
                random-m10V25E40B10D05 random-m10V49E48B10D10 \
                random-m5V49E84B05D05 random-m5V100E99B05D10 \
                random-m5V100E140B10D05 random-m5V100E180B10D10
do
    echo "Instance: "$instance;
    echo "Start time: "$(date);
    ./bin/exec/BnBSolverExec \
        --instance "instances/"$instance".in" \
        --time-limit $timeLimit \
        --warm-start-percentage-time $warmStartPercentageTime \
        --m $m --k $k \
        --statistics "statistics/"$instance"BnBSolverA.stat" \
        --solution "solutions/"$instance"BnBSolverA.sol";
    echo "End time: "$(date);
done

echo "BnCSolverA";

for instance in grid-m10V25E24B05D05 grid-m10V25E32B05D10 grid-m10V25E40B10D05 \
                grid-m10V49E48B10D10 grid-m5V49E84B05D05 grid-m5V100E99B05D10 \
                grid-m5V100E140B10D05 grid-m5V100E180B10D10 \
                random-m10V25E24B05D05 random-m10V25E32B05D10 \
                random-m10V25E40B10D05 random-m10V49E48B10D10 \
                random-m5V49E84B05D05 random-m5V100E99B05D10 \
                random-m5V100E140B10D05 random-m5V100E180B10D10
do
    echo "Instance: "$instance;
    echo "Start time: "$(date);
    ./bin/exec/BnCSolverExec \
        --instance "instances/"$instance".in" \
        --time-limit $timeLimit \
        --warm-start-percentage-time $warmStartPercentageTime \
        --m $m --k $k \
        --statistics "statistics/"$instance"BnCSolverA.stat" \
        --solution "solutions/"$instance"BnCSolverA.sol";
    echo "End time: "$(date);
done

warmStartPercentageTime=0.0;
echo "warmStartPercentageTime="$warmStartPercentageTime;

echo "BnBSolverB";

for instance in grid-m10V25E24B05D05 grid-m10V25E32B05D10 grid-m10V25E40B10D05 \
                grid-m10V49E48B10D10 grid-m5V49E84B05D05 grid-m5V100E99B05D10 \
                grid-m5V100E140B10D05 grid-m5V100E180B10D10 \
                random-m10V25E24B05D05 random-m10V25E32B05D10 \
                random-m10V25E40B10D05 random-m10V49E48B10D10 \
                random-m5V49E84B05D05 random-m5V100E99B05D10 \
                random-m5V100E140B10D05 random-m5V100E180B10D10
do
    echo "Instance: "$instance;
    echo "Start time: "$(date);
    ./bin/exec/BnBSolverExec \
        --instance "instances/"$instance".in" \
        --time-limit $timeLimit \
        --warm-start-percentage-time $warmStartPercentageTime \
        --m $m --k $k \
        --statistics "statistics/"$instance"BnBSolverB.stat" \
        --solution "solutions/"$instance"BnBSolverB.sol";
    echo "End time: "$(date);
done

echo "BnCSolverB";

for instance in grid-m10V25E24B05D05 grid-m10V25E32B05D10 grid-m10V25E40B10D05 \
                grid-m10V49E48B10D10 grid-m5V49E84B05D05 grid-m5V100E99B05D10 \
                grid-m5V100E140B10D05 grid-m5V100E180B10D10 \
                random-m10V25E24B05D05 random-m10V25E32B05D10 \
                random-m10V25E40B10D05 random-m10V49E48B10D10 \
                random-m5V49E84B05D05 random-m5V100E99B05D10 \
                random-m5V100E140B10D05 random-m5V100E180B10D10
do
    echo "Instance: "$instance;
    echo "Start time: "$(date);
    ./bin/exec/BnCSolverExec \
        --instance "instances/"$instance".in" \
        --time-limit $timeLimit \
        --warm-start-percentage-time $warmStartPercentageTime \
        --m $m --k $k \
        --statistics "statistics/"$instance"BnCSolverB.stat" \
        --solution "solutions/"$instance"BnCSolverB.sol";
    echo "End time: "$(date);
done

echo "GRASPSolver";

for instance in grid-m10V25E24B05D05 grid-m10V25E32B05D10 grid-m10V25E40B10D05 \
                grid-m10V49E48B10D10 grid-m5V49E84B05D05 grid-m5V100E99B05D10 \
                grid-m5V100E140B10D05 grid-m5V100E180B10D10 \
                random-m10V25E24B05D05 random-m10V25E32B05D10 \
                random-m10V25E40B10D05 random-m10V49E48B10D10 \
                random-m5V49E84B05D05 random-m5V100E99B05D10 \
                random-m5V100E140B10D05 random-m5V100E180B10D10
do
    echo "Instance: "$instance;
    echo "Start time: "$(date);
    ./bin/exec/GRASPSolverExec \
        --instance "instances/"$instance".in" \
        --time-limit $timeLimit --m $m --k $k \
        --statistics "statistics/"$instance"GRASPSolver.stat" \
        --solution "solutions/"$instance"GRASPSolver.sol";
    echo "End time: "$(date);
done

echo "Finished";

