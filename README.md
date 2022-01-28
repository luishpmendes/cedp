# The Capacitated and Economic Districting Problem (CEDP)

This repository contains the source code of the methodologies, the benchmark of instances, and the results obtained for the CEDP.

## Methodologies

The following methodologies are available:

* Exact
  - Cut-Set Formulation (CSF)
  - Line Graph Flow Formulation (LGFF)
* Metaheuristic
  - Greedy Randomized Adaptive Search Procedure (GRASP)

## Benchmark of Instances

The instances of the benchmark created for CEDP were classified according to the topology T of the graph, the number of districts m, the maximum allowed unbalance factor B, the maximum capacity D of the districts, the number of vertices |V| and the graph density concerning the number of edges |E|.

A total of 144 instances were generated, using the following values: 
* T ∈ {grid, random},
* m ∈ {5, 10},
* B ∈ {1/2, 1},
* D ∈ {((1 + B)<span style="text-decoration:overline">d</span><sub>ℰ</sub>)/2 , (1 + B)<span style="text-decoration:overline">d</span><sub>ℰ</sub>},
* |V| ∈ {25, 49, 100},
* |E| ∈ {sparse, medium, dense}.

The profit values were randomly chosen from the interval [0, m |E| - 1] with uniform distribution.

## Results

The metrics adopted in this work to compare methodologies in terms of solution quality are the primal and dual bounds, the number of feasible solutions, the optimality gap, and the number of optimal solutions found.
