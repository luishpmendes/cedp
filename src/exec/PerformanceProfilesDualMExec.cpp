#include "ArgumentParser.hpp"
#include <cassert>
#include <cfloat>
#include <iostream>
#include <set>
#include <vector>

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("-m")) {
        std::vector<double> dualBoundsBnB, dualBoundsBnC, ratiosBnB, ratiosBnC;
        std::set<double> ratios;
        std::string type, solver;
        unsigned int m, D, V, E, U, A, UPrime, APrime, timeLimit, seed, 
                     solvingTime, solutionsFound, primalBound, 
                     isSolutionFeasible, totalIterations, 
                     firstSolutionIteration, firstSolutionTime, 
                     bestSolutionIteration, bestSolutionTime, notPartition, 
                     notConnected, dontRespectCapacity, notBalanced, 
                     notFeasible, fixedSolutions, localSearchCounter, n, M;
        double Dratio, B, dualBound, maximumDemand;

        M = stoul(argParser.getCmdOption("-m"));

        while (std::cin >> type >> Dratio >> solver >> m >> D >> B >> V >> E 
                >> U >> A >> UPrime >> APrime >> maximumDemand >> timeLimit >> 
                seed >> solvingTime >> solutionsFound >> primalBound >> 
                dualBound >> isSolutionFeasible) {
            if (solver.compare("GRASPSolver") == 0 || 
                    solver.compare("LagrangianHeuristicSolver1") == 0 || 
                    solver.compare("LagrangianHeuristicSolver2") == 0) {
                std::cin >> totalIterations >> firstSolutionIteration >> 
                    firstSolutionTime >> bestSolutionIteration >> 
                    bestSolutionTime >> notPartition >> notConnected >> 
                    dontRespectCapacity >> notBalanced >> notFeasible >> 
                    fixedSolutions;
                if (solver.compare("GRASPSolver") == 0) {
                    std::cin >> localSearchCounter;
                }
            }

            if (M == m) {
                if (solver.compare("BnBSolver") == 0) {
                    dualBoundsBnB.push_back(dualBound);
                } else if (solver.compare("BnCSolver") == 0) {
                    dualBoundsBnC.push_back(dualBound);
                }
            }
        }

        assert(dualBoundsBnB.size() == 72);
        assert(dualBoundsBnB.size() == dualBoundsBnC.size());

        n = 72;

        for (unsigned int i = 0; i < n; i++) {
            double dualBoundBnB, dualBoundBnC, bestDualBound;

            dualBoundBnB = dualBoundsBnB[i];
            dualBoundBnC = dualBoundsBnC[i];

            bestDualBound = DBL_MAX;

            if (bestDualBound > dualBoundBnB && dualBoundBnB >= 0.0) {
                bestDualBound = dualBoundBnB;
            }

            if (bestDualBound > dualBoundBnC && dualBoundBnC >= 0.0) {
                bestDualBound = dualBoundBnC;
            }

            if (dualBoundBnB >= 0.0) {
                double ratioBnB = dualBoundBnB/bestDualBound;
                ratiosBnB.push_back(ratioBnB);
                ratios.insert(ratioBnB);
            }

            if (dualBoundBnC >= 0.0) {
                double ratioBnC = dualBoundBnC/bestDualBound;
                ratiosBnC.push_back(ratioBnC);
                ratios.insert(ratioBnC);
            }
        }

        for (double ratio : ratios) {
            double percentageBnB, percentageBnC;

            percentageBnB = 0.0;
            for (double ratioBnB : ratiosBnB) {
                if (ratioBnB <= ratio) {
                    percentageBnB += 1.0;
                }
            }
            percentageBnB *= 100.0/((double) n);

            percentageBnC = 0.0;
            for (double ratioBnC : ratiosBnC) {
                if (ratioBnC <= ratio) {
                    percentageBnC += 1.0;
                }
            }
            percentageBnC *= 100.0/((double) n);

            std::cout << ratio << ", " << percentageBnB << ", " << percentageBnC << std::endl;
        }
    }

    return 0;
}

