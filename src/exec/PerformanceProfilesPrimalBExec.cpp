#include "ArgumentParser.hpp"
#include <cassert>
#include <cmath>
#include <climits>
#include <iostream>
#include <set>
#include <vector>

#ifndef EPSILON
#define EPSILON 1E-3
#endif

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("-B")) {
        std::vector<unsigned int> primalBoundsBnB, primalBoundsBnC, primalBoundsGRASP;
        std::vector<double> ratiosBnB, ratiosBnC, ratiosGRASP;
        std::set<double> ratios;
        std::string type, solver;
        unsigned int m, D, V, E, U, A, UPrime, APrime, timeLimit, seed, 
                     solvingTime, solutionsFound, primalBound, 
                     isSolutionFeasible, totalIterations, 
                     firstSolutionIteration, firstSolutionTime, 
                     bestSolutionIteration, bestSolutionTime, notPartition, 
                     notConnected, dontRespectCapacity, notBalanced, 
                     notFeasible, fixedSolutions, localSearchCounter, n;
        double Dratio, B, dualBound, maximumDemand, balance;

        balance = stod(argParser.getCmdOption("-B"));

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

            if (solutionsFound == 0) {
                primalBound = UINT_MAX;
            }

            if (fabs(balance - B) < EPSILON) {
                if (solver.compare("BnBSolver") == 0) {
                    primalBoundsBnB.push_back(primalBound);
                } else if (solver.compare("BnCSolver") == 0) {
                    primalBoundsBnC.push_back(primalBound);
                } else if (solver.compare("GRASPSolver") == 0) {
                    primalBoundsGRASP.push_back(primalBound);
                }
            }
        }

        assert(primalBoundsBnB.size() == 72);
        assert(primalBoundsBnB.size() == primalBoundsBnC.size());
        assert(primalBoundsBnC.size() == primalBoundsGRASP.size());

        n = 72;
    
        for (unsigned int i = 0; i < n; i++) {
            unsigned int primalBoundBnB, primalBoundBnC, primalBoundGRASP, bestPrimalBound;

            primalBoundBnB = primalBoundsBnB[i];
            primalBoundBnC = primalBoundsBnC[i];
            primalBoundGRASP = primalBoundsGRASP[i];

            bestPrimalBound = 0;

            if (bestPrimalBound < primalBoundBnB && primalBoundBnB < UINT_MAX) {
                bestPrimalBound = primalBoundBnB;
            }

            if (bestPrimalBound < primalBoundBnC && primalBoundBnC < UINT_MAX) {
                bestPrimalBound = primalBoundBnC;
            }

            if (bestPrimalBound < primalBoundGRASP && primalBoundGRASP < UINT_MAX) {
                bestPrimalBound = primalBoundGRASP;
            }

            if (primalBoundBnB < UINT_MAX) {
                double ratioBnB = ((double) bestPrimalBound)/((double) primalBoundBnB);
                ratiosBnB.push_back(ratioBnB);
                ratios.insert(ratioBnB);
            }

            if (primalBoundBnC < UINT_MAX) {
                double ratioBnC = ((double) bestPrimalBound)/((double) primalBoundBnC);
                ratiosBnC.push_back(ratioBnC);
                ratios.insert(ratioBnC);
            }

            if (primalBoundGRASP < UINT_MAX) {
                double ratioGRASP = ((double) bestPrimalBound)/((double) primalBoundGRASP);
                ratiosGRASP.push_back(ratioGRASP);
                ratios.insert(ratioGRASP);
            }
        }

        for (double ratio : ratios) {
            double percentageBnB, percentageBnC, percentageGRASP;

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

            percentageGRASP = 0.0;
            for (double ratioGRASP : ratiosGRASP) {
                if (ratioGRASP <= ratio) {
                    percentageGRASP += 1.0;
                }
            }
            percentageGRASP *= 100.0/((double) n);

            std::cout << ratio << ", " << percentageBnB << ", " << 
                percentageBnC << ", " << percentageGRASP << std::endl;
        }
    }

    return 0;
}

