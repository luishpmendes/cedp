#include "ArgumentParser.hpp"
#include <cstdio>
#include <iostream>
#include <string>

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("--type") && argParser.cmdOptionExists("--solver")) {
        std::string type, solver;
        unsigned int m, D, V, E, U, A, UPrime, APrime, timeLimit, seed, 
                     solvingTime, solutionsFound, bestPrimalBound, 
                     isSolutionFeasible, totalIterations, 
                     firstSolutionIteration, firstSolutionTime, 
                     bestSolutionIteration, bestSolutionTime, notPartition, 
                     notConnected, dontRespectCapacity, notBalanced, 
                     notFeasible, fixedSolutions, localSearchCounter;
        double B, bestDualBound, maximumDemand, Dratio;

        type = argParser.getCmdOption("--type");
        solver = argParser.getCmdOption("--solver");
        Dratio = stod(argParser.getCmdOption("-D"));

        scanf("m: %u\n", &m);
        scanf("D: %u\n", &D);
        scanf("B: %lf\n", &B);
        scanf("|V|: %u\n", &V);
        scanf("|E|: %u\n", &E);
        scanf("|U|: %u\n", &U);
        scanf("|A|: %u\n", &A);
        scanf("|U'|: %u\n", &UPrime);
        scanf("|A'|: %u\n", &APrime);
        scanf("Maximum demand: %lf\n", &maximumDemand);
        scanf("Time limit: %us\n", &timeLimit);
        scanf("Seed: %u\n", &seed);
        scanf("Solving time: %us\n", &solvingTime);
        scanf("Solutions found: %u\n", &solutionsFound);
        scanf("Best primal bound: %u\n", &bestPrimalBound);
        scanf("Best dual bound: %lf\n", &bestDualBound);
        scanf("Is solution feasible: %u\n", &isSolutionFeasible);

        if (solver.compare("GRASPSolver") == 0 || 
                solver.compare("LagrangianHeuristicSolver1") == 0 || 
                solver.compare("LagrangianHeuristicSolver2") == 0) {
            scanf("Total iterations: %u\n", &totalIterations);
            scanf("First solution iteration: %u\n", &firstSolutionIteration);
            scanf("First solution time: %u\n", &firstSolutionTime);
            scanf("Best solution iteration: %u\n", &bestSolutionIteration);
            scanf("Best solution time: %u\n", &bestSolutionTime);
            scanf("Solutions that are not partition: %u\n", &notPartition);
            scanf("Solutions that are not connected: %u\n", &notConnected);
            scanf("Solutions that do not respects the capacity: %u\n", &dontRespectCapacity);
            scanf("Solutions that are not balanced: %u\n", &notBalanced);
            scanf("Solutions that are not feasible: %u\n", &notFeasible);
            scanf("Solutions that were fixed: %u\n", &fixedSolutions);
            if (solver.compare("GRASPSolver") == 0) {
                scanf("Local search counter: %u\n", &localSearchCounter);
            }
        }

        std::cout << type << " " << Dratio << " " << solver << " " << m << " " 
            << D << " " << B << " " << V << " " << E << " " << U << " " << A 
            << " " << UPrime << " " << APrime << " " << maximumDemand << " " 
            << timeLimit << " " << seed << " " << solvingTime << " " << 
            solutionsFound << " " << bestPrimalBound << " " << bestDualBound 
            << " " << isSolutionFeasible;

        if (solver.compare("GRASPSolver") == 0 || 
                solver.compare("LagrangianHeuristicSolver1") == 0 || 
                solver.compare("LagrangianHeuristicSolver2") == 0) {
            std::cout << " " << totalIterations << " " << 
                firstSolutionIteration << " " << firstSolutionTime << " " << 
                bestSolutionIteration << " " << bestSolutionTime << " " <<
                notPartition << " " << notConnected << " " << 
                dontRespectCapacity << " " << notBalanced << " " << 
                notFeasible << " " << fixedSolutions;
            if (solver.compare("GRASPSolver") == 0) {
                std::cout << " " << localSearchCounter;
            }
        }

        std::cout << std::endl;
    }
}

