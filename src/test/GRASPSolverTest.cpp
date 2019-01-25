#include "../solver/metaheuristic/grasp/GRASPSolver.hpp"
#include <cassert>
#include <cfloat>

int main () {
    unsigned int timeLimit = 5;
    double m = 10;
    unsigned int k = 100;
    Instance instance;
    GRASPSolver solver;

    for (unsigned int seed = 0; seed < 5; seed ++) {
        instance = Instance("instances/exampleA.in");

        solver = GRASPSolver(instance, timeLimit, seed, m, k);

        assert(solver.getSolutionsCounter() == 0);
        assert(solver.getSolvingTime() == 0);
        assert(solver.getBestPrimalBound() == 0);
        assert(solver.getBestDualBound() == DBL_MAX);

        solver.solve();

        assert(solver.getSolutionsCounter() > 0);
        assert(solver.getBestPrimalBound() >= 2);
        assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
        assert(solver.getBestDualBound() == DBL_MAX);
        assert(solver.getBestPrimalSolution().isFeasible());
        assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());
        assert(solver.getIterationsCounter() > k);
        assert(solver.getFirstSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getBestSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getFirstSolutionIteration() <= solver.getBestSolutionIteration());
        assert(solver.getNotPartitionSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotConnectedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotRespectsCapacitySolutionsCounter() <=
                solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotBalancedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getFixedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getLocalSearchCounter() > k);
        assert(solver.getLocalSearchCounter() <= solver.getSolutionsCounter());

        instance = Instance("instances/exampleB.in");

        solver = GRASPSolver(instance, timeLimit, seed, m, k);

        assert(solver.getSolutionsCounter() == 0);
        assert(solver.getSolvingTime() == 0);
        assert(solver.getBestPrimalBound() == 0);
        assert(solver.getBestDualBound() == DBL_MAX);

        solver.solve();

        assert(solver.getSolutionsCounter() > 0);
        assert(solver.getBestPrimalBound() >= 3);
        assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
        assert(solver.getBestDualBound() == DBL_MAX);
        assert(solver.getBestPrimalSolution().isFeasible());
        assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());
        assert(solver.getIterationsCounter() > k);
        assert(solver.getFirstSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getBestSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getFirstSolutionIteration() <= solver.getBestSolutionIteration());
        assert(solver.getNotPartitionSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotConnectedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotRespectsCapacitySolutionsCounter() <=
                solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotBalancedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getFixedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getLocalSearchCounter() > k);
        assert(solver.getLocalSearchCounter() <= solver.getSolutionsCounter());

        instance = Instance("instances/exampleC.in");

        solver = GRASPSolver(instance, timeLimit, seed, m, k);

        assert(solver.getSolutionsCounter() == 0);
        assert(solver.getSolvingTime() == 0);
        assert(solver.getBestPrimalBound() == 0);
        assert(solver.getBestDualBound() == DBL_MAX);

        solver.solve();

        assert(solver.getSolutionsCounter() > 0);
        assert(solver.getBestPrimalBound() >= 12);
        assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
        assert(solver.getBestDualBound() == DBL_MAX);
        assert(solver.getBestPrimalSolution().isFeasible());
        assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());
        assert(solver.getIterationsCounter() > k);
        assert(solver.getFirstSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getBestSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getFirstSolutionIteration() <= solver.getBestSolutionIteration());
        assert(solver.getNotPartitionSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotConnectedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotRespectsCapacitySolutionsCounter() <=
                solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotBalancedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getFixedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getLocalSearchCounter() > k);
        assert(solver.getLocalSearchCounter() <= solver.getSolutionsCounter());

        instance = Instance("instances/exampleD.in");

        solver = GRASPSolver(instance, timeLimit, seed, m, k);

        assert(solver.getSolutionsCounter() == 0);
        assert(solver.getSolvingTime() == 0);
        assert(solver.getBestPrimalBound() == 0);
        assert(solver.getBestDualBound() == DBL_MAX);

        solver.solve();

        assert(solver.getSolutionsCounter() > 0);
        assert(solver.getBestPrimalBound() >= 12);
        assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
        assert(solver.getBestDualBound() == DBL_MAX);
        assert(solver.getBestPrimalSolution().isFeasible());
        assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());
        assert(solver.getIterationsCounter() > k);
        assert(solver.getFirstSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getBestSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getFirstSolutionIteration() <= solver.getBestSolutionIteration());
        assert(solver.getNotPartitionSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotConnectedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotRespectsCapacitySolutionsCounter() <=
                solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotBalancedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getFixedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getLocalSearchCounter() > k);
        assert(solver.getLocalSearchCounter() <= solver.getSolutionsCounter());

        instance = Instance("instances/exampleE.in");

        solver = GRASPSolver(instance, timeLimit, seed, m, k);

        assert(solver.getSolutionsCounter() == 0);
        assert(solver.getSolvingTime() == 0);
        assert(solver.getBestPrimalBound() == 0);
        assert(solver.getBestDualBound() == DBL_MAX);

        solver.solve();

        assert(solver.getSolutionsCounter() > 0);
        assert(solver.getBestPrimalBound() >= 230);
        assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
        assert(solver.getBestDualBound() == DBL_MAX);
        assert(solver.getBestPrimalSolution().isFeasible());
        assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());
        assert(solver.getIterationsCounter() > k);
        assert(solver.getFirstSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getBestSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getFirstSolutionIteration() <= solver.getBestSolutionIteration());
        assert(solver.getNotPartitionSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotConnectedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotRespectsCapacitySolutionsCounter() <=
                solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotBalancedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getFixedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getLocalSearchCounter() > k);
        assert(solver.getLocalSearchCounter() <= solver.getSolutionsCounter());

        instance = Instance("instances/exampleF.in");

        solver = GRASPSolver(instance, timeLimit, seed, m, k);

        assert(solver.getSolutionsCounter() == 0);
        assert(solver.getSolvingTime() == 0);
        assert(solver.getBestPrimalBound() == 0);
        assert(solver.getBestDualBound() == DBL_MAX);

        solver.solve();

        assert(solver.getSolutionsCounter() > 0);
        assert(solver.getBestPrimalBound() >= 84);
        assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
        assert(solver.getBestDualBound() == DBL_MAX);
        assert(solver.getBestPrimalSolution().isFeasible());
        assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());
        assert(solver.getIterationsCounter() > k);
        assert(solver.getFirstSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getBestSolutionIteration() <= solver.getIterationsCounter());
        assert(solver.getFirstSolutionIteration() <= solver.getBestSolutionIteration());
        assert(solver.getNotPartitionSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotConnectedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotRespectsCapacitySolutionsCounter() <=
                solver.getNotFeasibleSolutionsCounter());
        assert(solver.getNotBalancedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getFixedSolutionsCounter() <= solver.getNotFeasibleSolutionsCounter());
        assert(solver.getLocalSearchCounter() > k);
        assert(solver.getLocalSearchCounter() <= solver.getSolutionsCounter());
    }

    return 0;
}

