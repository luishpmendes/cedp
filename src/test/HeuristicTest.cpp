#include "../solver/heuristic/constructive/GreedyConstructiveHeuristic.hpp"
#include "../solver/heuristic/fixer/SolutionFixer.hpp"
#include "../solver/heuristic/localsearch/LocalSearchHeuristic.hpp"
#include <cassert>

int main () {
    unsigned int seed;
    Instance instance;
    Solution constructedSolution;
    Solution improvedSolution;
    GreedyConstructiveHeuristic gcHeuristic;
    LocalSearchHeuristic lsHeuristic;
    unsigned int timeLimit = 10;

    for (seed = 0; seed < 100; seed++) {
        instance = Instance("instances/exampleA.in");
        gcHeuristic = GreedyConstructiveHeuristic(instance, seed, 0.05);
        lsHeuristic = LocalSearchHeuristic(instance, seed);
        constructedSolution = gcHeuristic.constructSolution(timeLimit);

        if (!constructedSolution.isFeasible()) {
            constructedSolution = SolutionFixer::fixSolution(constructedSolution, timeLimit);
        }

        if (constructedSolution.isFeasible()) {
            improvedSolution = lsHeuristic.improveSolution(constructedSolution, timeLimit);

            assert(improvedSolution.isFeasible());
            assert(improvedSolution.getValue() >= constructedSolution.getValue());
        }

        instance = Instance("instances/exampleB.in");
        gcHeuristic = GreedyConstructiveHeuristic(instance, seed, 0.05);
        lsHeuristic = LocalSearchHeuristic(instance, seed);
        constructedSolution = gcHeuristic.constructSolution(timeLimit);

        if (!constructedSolution.isFeasible()) {
            constructedSolution = SolutionFixer::fixSolution(constructedSolution, timeLimit);
        }

        if (constructedSolution.isFeasible()) {
            improvedSolution = lsHeuristic.improveSolution(constructedSolution, timeLimit);

            assert(improvedSolution.isFeasible());
            assert(improvedSolution.getValue() >= constructedSolution.getValue());
        }

        instance = Instance("instances/exampleC.in");
        gcHeuristic = GreedyConstructiveHeuristic(instance, seed, 0.05);
        lsHeuristic = LocalSearchHeuristic(instance, seed);
        constructedSolution = gcHeuristic.constructSolution(timeLimit);

        if (!constructedSolution.isFeasible()) {
            constructedSolution = SolutionFixer::fixSolution(constructedSolution, timeLimit);
        }

        if (constructedSolution.isFeasible()) {
            improvedSolution = lsHeuristic.improveSolution(constructedSolution, timeLimit);

            assert(improvedSolution.isFeasible());
            assert(improvedSolution.getValue() >= constructedSolution.getValue());
        }

        instance = Instance("instances/exampleD.in");
        gcHeuristic = GreedyConstructiveHeuristic(instance, seed, 0.05);
        lsHeuristic = LocalSearchHeuristic(instance, seed);
        constructedSolution = gcHeuristic.constructSolution(timeLimit);

        if (!constructedSolution.isFeasible()) {
            constructedSolution = SolutionFixer::fixSolution(constructedSolution, timeLimit);
        }

        if (constructedSolution.isFeasible()) {
            improvedSolution = lsHeuristic.improveSolution(constructedSolution, timeLimit);

            assert(improvedSolution.isFeasible());
            assert(improvedSolution.getValue() >= constructedSolution.getValue());
        }

        instance = Instance("instances/exampleE.in");
        gcHeuristic = GreedyConstructiveHeuristic(instance, seed, 0.05);
        lsHeuristic = LocalSearchHeuristic(instance, seed);
        constructedSolution = gcHeuristic.constructSolution(timeLimit);

        if (!constructedSolution.isFeasible()) {
            constructedSolution = SolutionFixer::fixSolution(constructedSolution, timeLimit);
        }

        if (constructedSolution.isFeasible()) {
            improvedSolution = lsHeuristic.improveSolution(constructedSolution, timeLimit);

            assert(improvedSolution.isFeasible());
            assert(improvedSolution.getValue() >= constructedSolution.getValue());
        }

        instance = Instance("instances/exampleF.in");
        gcHeuristic = GreedyConstructiveHeuristic(instance, seed, 0.05);
        lsHeuristic = LocalSearchHeuristic(instance, seed);
        constructedSolution = gcHeuristic.constructSolution(timeLimit);

        if (!constructedSolution.isFeasible()) {
            constructedSolution = SolutionFixer::fixSolution(constructedSolution, timeLimit);
        }

        if (constructedSolution.isFeasible()) {
            improvedSolution = lsHeuristic.improveSolution(constructedSolution, timeLimit);

            assert(improvedSolution.isFeasible());
            assert(improvedSolution.getValue() >= constructedSolution.getValue());
        }
    }

    return 0;
}

