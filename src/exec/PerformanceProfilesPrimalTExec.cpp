#include "ArgumentParser.hpp"
#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <vector>

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("-T")) {
        std::vector<unsigned int> primalBoundsBnBA,
                                  primalBoundsBnBB,
                                  primalBoundsBnCA,
                                  primalBoundsBnCB,
                                  primalBoundsGRASPA,
                                  primalBoundsGRASPB;
        std::vector<double> ratiosBnBA,
                            ratiosBnBB,
                            ratiosBnCA,
                            ratiosBnCB,
                            ratiosGRASPA,
                            ratiosGRASPB,
                            psi,
                            p;
        std::set<double> ratios;
        std::string type, solver, T;
        unsigned int m, D, V, E, U, A, UPrime, APrime, timeLimit, seed,
                     solvingTime, solutionsFound, primalBound,
                     isSolutionFeasible, totalIterations,
                     firstSolutionIteration, firstSolutionTime,
                     bestSolutionIteration, bestSolutionTime, notPartition,
                     notConnected, dontRespectCapacity, notBalanced,
                     notFeasible, fixedSolutions, localSearchCounter, n,
                     psiSize, k;
        double Dratio, B, dualBound, maximumDemand, ratioMean, ratioStd;
        bool statisticalFilter;

        T = argParser.getCmdOption("-T");

        while (std::cin >> type >> Dratio >> solver >> m >> D >> B >> V >> E
                >> U >> A >> UPrime >> APrime >> maximumDemand >> timeLimit >>
                seed >> solvingTime >> solutionsFound >> primalBound >>
                dualBound >> isSolutionFeasible) {
            if (solver.compare("GRASPA") == 0 ||
                    solver.compare("GRASPB") == 0) {
                std::cin >> totalIterations >> firstSolutionIteration >>
                    firstSolutionTime >> bestSolutionIteration >>
                    bestSolutionTime >> notPartition >> notConnected >>
                    dontRespectCapacity >> notBalanced >> notFeasible >>
                    fixedSolutions >> localSearchCounter >> ratioMean >>
                    ratioStd >> psiSize >> k >> statisticalFilter;

                psi.resize(psiSize);

                for (double & alpha : psi) {
                    std::cin >> alpha;
                }

                p.resize(psiSize);

                for (double & prob : p) {
                    std::cin >> prob;
                }
            }

            if (solutionsFound == 0) {
                primalBound = UINT_MAX;
            }

            if (T.compare(type) == 0) {
                if (solver.compare("BnBSolverA") == 0) {
                    primalBoundsBnBA.push_back(primalBound);
                } else if (solver.compare("BnBSolverB") == 0) {
                    primalBoundsBnBB.push_back(primalBound);
                } else if (solver.compare("BnCSolverA") == 0) {
                    primalBoundsBnCA.push_back(primalBound);
                } else if (solver.compare("BnCSolverB") == 0) {
                    primalBoundsBnCB.push_back(primalBound);
                } else if (solver.compare("GRASPA") == 0) {
                    primalBoundsGRASPA.push_back(primalBound);
                } else if (solver.compare("GRASPB") == 0) {
                    primalBoundsGRASPB.push_back(primalBound);
                }
            }
        }

        n = 72;

        assert(primalBoundsBnBA.size() == n);
        assert(primalBoundsBnBB.size() == n);
        assert(primalBoundsBnCA.size() == n);
        assert(primalBoundsBnCB.size() == n);
        assert(primalBoundsGRASPA.size() == n);
        assert(primalBoundsGRASPB.size() == n);

        for (unsigned int i = 0; i < n; i++) {
            unsigned int primalBoundBnBA,
                         primalBoundBnBB,
                         primalBoundBnCA,
                         primalBoundBnCB,
                         primalBoundGRASPA,
                         primalBoundGRASPB,
                         bestPrimalBound;

            primalBoundBnBA = primalBoundsBnBA[i];
            primalBoundBnBB = primalBoundsBnBB[i];
            primalBoundBnCA = primalBoundsBnCA[i];
            primalBoundBnCB = primalBoundsBnCB[i];
            primalBoundGRASPA = primalBoundsGRASPA[i];
            primalBoundGRASPB = primalBoundsGRASPB[i];

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

            if (bestPrimalBound < primalBoundGRASPA && primalBoundGRASPA < UINT_MAX) {
                bestPrimalBound = primalBoundGRASPA;
            }

            if (bestPrimalBound < primalBoundGRASPB && primalBoundGRASPB < UINT_MAX) {
                bestPrimalBound = primalBoundGRASPB;
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

            if (primalBoundGRASPA < UINT_MAX) {
                double ratioGRASPA = ((double) bestPrimalBound)/((double) primalBoundGRASPA);
                ratiosGRASPA.push_back(ratioGRASPA);
                ratios.insert(ratioGRASPA);
            }

            if (primalBoundGRASPB < UINT_MAX) {
                double ratioGRASPB = ((double) bestPrimalBound)/((double) primalBoundGRASPB);
                ratiosGRASPB.push_back(ratioGRASPB);
                ratios.insert(ratioGRASPB);
            }
        }

        for (const double & ratio : ratios) {
            double percentageBnBA,
                   percentageBnBB,
                   percentageBnCA,
                   percentageBnCB,
                   percentageGRASPA,
                   percentageGRASPB;

            percentageBnBA = 0.0;
            for (const double & ratioBnBA : ratiosBnBA) {
                if (ratioBnBA <= ratio) {
                    percentageBnBA += 1.0;
                }
            }
            percentageBnBA *= 100.0/((double) n);

            percentageBnBB = 0.0;
            for (const double & ratioBnBB : ratiosBnBB) {
                if (ratioBnBB <= ratio) {
                    percentageBnBB += 1.0;
                }
            }
            percentageBnBB *= 100.0/((double) n);

            percentageBnCA = 0.0;
            for (const double & ratioBnCA : ratiosBnCA) {
                if (ratioBnCA <= ratio) {
                    percentageBnCA += 1.0;
                }
            }
            percentageBnCA *= 100.0/((double) n);

            percentageBnCB = 0.0;
            for (const double & ratioBnCB : ratiosBnCB) {
                if (ratioBnCB <= ratio) {
                    percentageBnCB += 1.0;
                }
            }
            percentageBnCB *= 100.0/((double) n);

            percentageGRASPA = 0.0;
            for (const double & ratioGRASPA : ratiosGRASPA) {
                if (ratioGRASPA <= ratio) {
                    percentageGRASPA += 1.0;
                }
            }
            percentageGRASPA *= 100.0/((double) n);

            percentageGRASPB = 0.0;
            for (const double & ratioGRASPB : ratiosGRASPB) {
                if (ratioGRASPB <= ratio) {
                    percentageGRASPB += 1.0;
                }
            }
            percentageGRASPB *= 100.0/((double) n);

            std::cout << ratio << ", "
                      << percentageBnBA << ", "
                      << percentageBnBB << ", "
                      << percentageBnCA << ", "
                      << percentageBnCB << ", "
                      << percentageGRASPA << ", "
                      << percentageGRASPB << std::endl;
        }
    }

    return 0;
}

