#include <cassert>
#include <cfloat>
#include <iostream>
#include <set>
#include <vector>

int main () {
    std::vector<double> dualBoundsBnBA,
                        dualBoundsBnBB,
                        dualBoundsBnCA,
                        dualBoundsBnCB,
                        ratiosBnBA,
                        ratiosBnBB,
                        ratiosBnCA,
                        ratiosBnCB;
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

        if (solver.compare("BnBSolverA") == 0) {
            dualBoundsBnBA.push_back(dualBound);
        } else if (solver.compare("BnBSolverB") == 0) {
            dualBoundsBnBB.push_back(dualBound);
        } else if (solver.compare("BnCSolverA") == 0) {
            dualBoundsBnCA.push_back(dualBound);
        } else if (solver.compare("BnCSolverB") == 0) {
            dualBoundsBnCB.push_back(dualBound);
        }
    }

    n = 144;

    assert(dualBoundsBnBA.size() == n);
    assert(dualBoundsBnBB.size() == n);
    assert(dualBoundsBnCA.size() == n);
    assert(dualBoundsBnCB.size() == n);

    for (unsigned int i = 0; i < n; i++) {
        double dualBoundBnBA,
               dualBoundBnBB,
               dualBoundBnCA,
               dualBoundBnCB,
               bestDualBound;

        dualBoundBnBA = dualBoundsBnBA[i];
        dualBoundBnBB = dualBoundsBnBB[i];
        dualBoundBnCA = dualBoundsBnCA[i];
        dualBoundBnCB = dualBoundsBnCB[i];

        bestDualBound = DBL_MAX;

        if (bestDualBound > dualBoundBnBA && dualBoundBnBA >= 0.0) {
            bestDualBound = dualBoundBnBA;
        }

        if (bestDualBound > dualBoundBnBB && dualBoundBnBB >= 0.0) {
            bestDualBound = dualBoundBnBB;
        }

        if (bestDualBound > dualBoundBnCA && dualBoundBnCA >= 0.0) {
            bestDualBound = dualBoundBnCA;
        }

        if (bestDualBound > dualBoundBnCB && dualBoundBnCB >= 0.0) {
            bestDualBound = dualBoundBnCB;
        }

        if (dualBoundBnBA >= 0.0) {
            double ratioBnBA = dualBoundBnBA/bestDualBound;
            ratiosBnBA.push_back(ratioBnBA);
            ratios.insert(ratioBnBA);
        }

        if (dualBoundBnBB >= 0.0) {
            double ratioBnBB = dualBoundBnBB/bestDualBound;
            ratiosBnBB.push_back(ratioBnBB);
            ratios.insert(ratioBnBB);
        }

        if (dualBoundBnCA >= 0.0) {
            double ratioBnCA = dualBoundBnCA/bestDualBound;
            ratiosBnCA.push_back(ratioBnCA);
            ratios.insert(ratioBnCA);
        }

        if (dualBoundBnCB >= 0.0) {
            double ratioBnCB = dualBoundBnCB/bestDualBound;
            ratiosBnCB.push_back(ratioBnCB);
            ratios.insert(ratioBnCB);
        }
    }

    for (double ratio : ratios) {
        double percentageBnBA,
               percentageBnBB,
               percentageBnCA,
               percentageBnCB;

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

        std::cout << ratio << ", "
                  << percentageBnBA << ", "
                  << percentageBnBB << ", "
                  << percentageBnCA << ", "
                  << percentageBnCB << std::endl;
    }

    return 0;
}

