#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <vector>

int main () {
    std::vector<unsigned int> primalBoundsBnBA,
                              primalBoundsBnBB,
                              primalBoundsBnCA,
                              primalBoundsBnCB,
                              primalBoundsGRASP;
    std::vector<double> ratiosBnBA,
                        ratiosBnBB,
                        ratiosBnCA,
                        ratiosBnCB,
                        ratiosGRASP;
    std::set<double> ratios;
    std::string type, solver;
    unsigned int m, D, V, E, U, A, UPrime, APrime, timeLimit, seed, 
                 solvingTime, solutionsFound, primalBound, isSolutionFeasible, 
                 totalIterations, firstSolutionIteration, firstSolutionTime, 
                 bestSolutionIteration, bestSolutionTime, notPartition, 
                 notConnected, dontRespectCapacity, notBalanced, notFeasible, 
                 fixedSolutions, localSearchCounter, n;
    double Dratio, B, dualBound, maximumDemand;

    while (std::cin >> type >> Dratio >> solver >> m >> D >> B >> V >> E >> U 
            >> A >> UPrime >> APrime >> maximumDemand >> timeLimit >> seed >> 
            solvingTime >> solutionsFound >> primalBound >> dualBound >> 
            isSolutionFeasible) {
        if (solver.compare("GRASPSolver") == 0 || 
                solver.compare("LagrangianHeuristicSolver1") == 0 || 
                solver.compare("LagrangianHeuristicSolver2") == 0) {
            std::cin >> totalIterations >> firstSolutionIteration >> 
                firstSolutionTime >> bestSolutionIteration >> bestSolutionTime 
                >> notPartition >> notConnected >> dontRespectCapacity >> 
                notBalanced >> notFeasible >> fixedSolutions;
            if (solver.compare("GRASPSolver") == 0) {
                std::cin >> localSearchCounter;
            }
        }

        if (solutionsFound == 0) {
            primalBound = UINT_MAX;
        }

        if (solver.compare("BnBSolverA") == 0) {
            primalBoundsBnBA.push_back(primalBound);
        } else if (solver.compare("BnBSolverB") == 0) {
            primalBoundsBnBB.push_back(primalBound);
        } else if (solver.compare("BnCSolverA") == 0) {
            primalBoundsBnCA.push_back(primalBound);
        } else if (solver.compare("BnCSolverB") == 0) {
            primalBoundsBnCB.push_back(primalBound);
        } else if (solver.compare("GRASPSolver") == 0) {
            primalBoundsGRASP.push_back(primalBound);
        }
    }

    n = 144;

    assert(primalBoundsBnBA.size() == n);
    assert(primalBoundsBnBB.size() == n);
    assert(primalBoundsBnCA.size() == n);
    assert(primalBoundsBnCB.size() == n);
    assert(primalBoundsGRASP.size() == n);

    for (unsigned int i = 0; i < n; i++) {
        unsigned int primalBoundBnBA,
                     primalBoundBnBB,
                     primalBoundBnCA,
                     primalBoundBnCB,
                     primalBoundGRASP,
                     bestPrimalBound;

        primalBoundBnBA = primalBoundsBnBA[i];
        primalBoundBnBB = primalBoundsBnBB[i];
        primalBoundBnCA = primalBoundsBnCA[i];
        primalBoundBnCB = primalBoundsBnCB[i];
        primalBoundGRASP = primalBoundsGRASP[i];

        bestPrimalBound = 0;

        if (bestPrimalBound < primalBoundBnBA && primalBoundBnBA < UINT_MAX) {
            bestPrimalBound = primalBoundBnBA;
        }

        if (bestPrimalBound < primalBoundBnBB && primalBoundBnBB < UINT_MAX) {
            bestPrimalBound = primalBoundBnBB;
        }

        if (bestPrimalBound < primalBoundBnCA && primalBoundBnCA < UINT_MAX) {
            bestPrimalBound = primalBoundBnCA;
        }

        if (bestPrimalBound < primalBoundBnCB && primalBoundBnCB < UINT_MAX) {
            bestPrimalBound = primalBoundBnCB;
        }

        if (bestPrimalBound < primalBoundGRASP && primalBoundGRASP < UINT_MAX) {
            bestPrimalBound = primalBoundGRASP;
        }

        if (primalBoundBnBA < UINT_MAX) {
            double ratioBnBA = ((double) bestPrimalBound)/((double) primalBoundBnBA);
            ratiosBnBA.push_back(ratioBnBA);
            ratios.insert(ratioBnBA);
        }

        if (primalBoundBnBB < UINT_MAX) {
            double ratioBnBB = ((double) bestPrimalBound)/((double) primalBoundBnBB);
            ratiosBnBB.push_back(ratioBnBB);
            ratios.insert(ratioBnBB);
        }

        if (primalBoundBnCA < UINT_MAX) {
            double ratioBnCA = ((double) bestPrimalBound)/((double) primalBoundBnCA);
            ratiosBnCA.push_back(ratioBnCA);
            ratios.insert(ratioBnCA);
        }

        if (primalBoundBnCB < UINT_MAX) {
            double ratioBnCB = ((double) bestPrimalBound)/((double) primalBoundBnCB);
            ratiosBnCB.push_back(ratioBnCB);
            ratios.insert(ratioBnCB);
        }

        if (primalBoundGRASP < UINT_MAX) {
            double ratioGRASP = ((double) bestPrimalBound)/((double) primalBoundGRASP);
            ratiosGRASP.push_back(ratioGRASP);
            ratios.insert(ratioGRASP);
        }
    }

    for (double ratio : ratios) {
        double percentageBnBA,
               percentageBnBB,
               percentageBnCA,
               percentageBnCB,
               percentageGRASP;

        percentageBnBA = 0.0;
        for (double ratioBnBA : ratiosBnBA) {
            if (ratioBnBA <= ratio) {
                percentageBnBA += 1.0;
            }
        }
        percentageBnBA *= 100.0/((double) n);

        percentageBnBB = 0.0;
        for (double ratioBnBB : ratiosBnBB) {
            if (ratioBnBB <= ratio) {
                percentageBnBB += 1.0;
            }
        }
        percentageBnBB *= 100.0/((double) n);

        percentageBnCA = 0.0;
        for (double ratioBnCA : ratiosBnCA) {
            if (ratioBnCA <= ratio) {
                percentageBnCA += 1.0;
            }
        }
        percentageBnCA *= 100.0/((double) n);

        percentageBnCB = 0.0;
        for (double ratioBnCB : ratiosBnCB) {
            if (ratioBnCB <= ratio) {
                percentageBnCB += 1.0;
            }
        }
        percentageBnCB *= 100.0/((double) n);

        percentageGRASP = 0.0;
        for (double ratioGRASP : ratiosGRASP) {
            if (ratioGRASP <= ratio) {
                percentageGRASP += 1.0;
            }
        }
        percentageGRASP *= 100.0/((double) n);

        std::cout << ratio << ", "
                  << percentageBnBA << ", "
                  << percentageBnBB << ", "
                  << percentageBnCA << ", "
                  << percentageBnCB << ", "
                  << percentageGRASP << std::endl;
    }

    return 0;
}

