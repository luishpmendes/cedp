#include "../solver/exact/branch-and-cut/BnCSolver.hpp"
#include <cassert>
#include <cfloat>

int main () {
    unsigned int timeLimit = 10;
    unsigned int seed = 0;
    double warmStartPercentageTime = 0.1;
    unsigned int m = 10;
    unsigned int k = 100;
    Instance instance;
    BnCSolver solver;

    instance = Instance("instances/exampleA.in");

    solver = BnCSolver(instance,
                       timeLimit,
                       seed,
                       warmStartPercentageTime,
                       m,
                       k,
                       true);

    assert(solver.getSolutionsCounter() == 0);
    assert(solver.getSolvingTime() == 0);
    assert(solver.getBestPrimalBound() == 0);
    assert(solver.getBestDualBound() == DBL_MAX);

    solver.solve();

    assert(solver.getSolutionsCounter() > 0);
    assert(solver.getBestPrimalBound() >= 2);
    assert(solver.getBestDualBound() < DBL_MAX);
    assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
    assert(solver.getBestPrimalSolution().isFeasible());
    assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());

    instance = Instance("instances/exampleB.in");

    solver = BnCSolver(instance,
                       timeLimit,
                       seed,
                       warmStartPercentageTime,
                       m,
                       k,
                       true);

    assert(solver.getSolutionsCounter() == 0);
    assert(solver.getSolvingTime() == 0);
    assert(solver.getBestPrimalBound() == 0);
    assert(solver.getBestDualBound() == DBL_MAX);

    solver.solve();

    assert(solver.getSolutionsCounter() > 0);
    assert(solver.getBestPrimalBound() >= 3);
    assert(solver.getBestDualBound() < DBL_MAX);
    assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
    assert(solver.getBestPrimalSolution().isFeasible());
    assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());

    instance = Instance("instances/exampleC.in");

    solver = BnCSolver(instance,
                       timeLimit,
                       seed,
                       warmStartPercentageTime,
                       m,
                       k,
                       true);

    assert(solver.getSolutionsCounter() == 0);
    assert(solver.getSolvingTime() == 0);
    assert(solver.getBestPrimalBound() == 0);
    assert(solver.getBestDualBound() == DBL_MAX);

    solver.solve();

    assert(solver.getSolutionsCounter() > 0);
    assert(solver.getBestPrimalBound() >= 12);
    assert(solver.getBestDualBound() < DBL_MAX);
    assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
    assert(solver.getBestPrimalSolution().isFeasible());
    assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());

    instance = Instance("instances/exampleD.in");

    solver = BnCSolver(instance,
                       timeLimit,
                       seed,
                       warmStartPercentageTime,
                       m,
                       k,
                       true);

    assert(solver.getSolutionsCounter() == 0);
    assert(solver.getSolvingTime() == 0);
    assert(solver.getBestPrimalBound() == 0);
    assert(solver.getBestDualBound() == DBL_MAX);

    solver.solve();

    assert(solver.getSolutionsCounter() > 0);
    assert(solver.getBestPrimalBound() >= 12);
    assert(solver.getBestDualBound() < DBL_MAX);
    assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
    assert(solver.getBestPrimalSolution().isFeasible());
    assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());

    instance = Instance("instances/exampleE.in");

    solver = BnCSolver(instance,
                       timeLimit,
                       seed,
                       warmStartPercentageTime,
                       m,
                       k,
                       true);

    assert(solver.getSolutionsCounter() == 0);
    assert(solver.getSolvingTime() == 0);
    assert(solver.getBestPrimalBound() == 0);
    assert(solver.getBestDualBound() == DBL_MAX);

    solver.solve();

    assert(solver.getSolutionsCounter() > 0);
    assert(solver.getBestPrimalBound() >= 230);
    assert(solver.getBestDualBound() < DBL_MAX);
    assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
    assert(solver.getBestPrimalSolution().isFeasible());
    assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());

    instance = Instance("instances/exampleF.in");

    solver = BnCSolver(instance,
                       timeLimit,
                       seed,
                       warmStartPercentageTime,
                       m,
                       k,
                       true);

    assert(solver.getSolutionsCounter() == 0);
    assert(solver.getSolvingTime() == 0);
    assert(solver.getBestPrimalBound() == 0);
    assert(solver.getBestDualBound() == DBL_MAX);

    solver.solve();

    assert(solver.getSolutionsCounter() > 0);
    assert(solver.getBestPrimalBound() >= 84);
    assert(solver.getBestDualBound() < DBL_MAX);
    assert(solver.getBestPrimalBound() <= solver.getBestDualBound());
    assert(solver.getBestPrimalSolution().isFeasible());
    assert(solver.getBestPrimalSolution().getValue() == solver.getBestPrimalBound());

    return 0;
}

