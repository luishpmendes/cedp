#include "ArgumentParser.hpp"
#include <cassert>
#include <cfloat>
#include <climits>
#include <iomanip>
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
        std::vector<double> psi, p,
                            dualBoundsBnBA,
                            dualBoundsBnBB,
                            dualBoundsBnCA,
                            dualBoundsBnCB,
                            dualBoundsGRASPA,
                            dualBoundsGRASPB,
                            feasibleBnBA,
                            feasibleBnBB,
                            feasibleBnCA,
                            feasibleBnCB,
                            feasibleGRASPA,
                            feasibleGRASPB,
                            gapBnBA,
                            gapBnBB,
                            gapBnCA,
                            gapBnCB,
                            gapGRASPA,
                            gapGRASPB,
                            optBnBA,
                            optBnBB,
                            optBnCA,
                            optBnCB,
                            optGRASPA,
                            optGRASPB;
        std::string type, solver, T;
        unsigned int m, D, V, E, U, A, UPrime, APrime, timeLimit, seed,
                     solvingTime, solutionsFound, primalBound,
                     isSolutionFeasible, totalIterations,
                     firstSolutionIteration, firstSolutionTime,
                     bestSolutionIteration, bestSolutionTime, notPartition,
                     notConnected, dontRespectCapacity, notBalanced,
                     notFeasible, fixedSolutions, localSearchCounter, n,
                     psiSize, k,
                     totalIterationsGRASPA, totalIterationsGRASPB,
                     notFeasibleGRASPA, notFeasibleGRASPB,
                     notConnectedGRASPA, notConnectedGRASPB,
                     dontRespectCapacityGRASPA, dontRespectCapacityGRASPB,
                     notBalancedGRASPA, notBalancedGRASPB,
                     fixedSolutionsGRASPA, fixedSolutionsGRASPB;
        double Dratio, B, dualBound, maximumDemand, ratioMean, ratioStd,
               feasibleRatioBnBA,
               feasibleRatioBnBB,
               feasibleRatioBnCA,
               feasibleRatioBnCB,
               feasibleRatioGRASPA,
               feasibleRatioGRASPB,
               meanGapBnBA,
               meanGapBnBB,
               meanGapBnCA,
               meanGapBnCB,
               meanGapGRASPA,
               meanGapGRASPB,
               optRatioBnBA,
               optRatioBnBB,
               optRatioBnCA,
               optRatioBnCB,
               optRatioGRASPA,
               optRatioGRASPB,
               ratioMeanGRASPA, ratioMeanGRASPB;
        bool statisticalFilter;

        totalIterationsGRASPA = totalIterationsGRASPB =
        notFeasibleGRASPA = notFeasibleGRASPB =
        notConnectedGRASPA = notConnectedGRASPB =
        dontRespectCapacityGRASPA = dontRespectCapacityGRASPB =
        notBalancedGRASPA = notBalancedGRASPB =
        fixedSolutionsGRASPA = fixedSolutionsGRASPB = 0;
        ratioMeanGRASPA = ratioMeanGRASPB = 0.0;

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

            if (T.compare(type) == 0) {
                if (solver.compare("BnBSolverA") == 0) {
                    primalBoundsBnBA.push_back(primalBound);
                    dualBoundsBnBA.push_back(dualBound);

                    if (solutionsFound > 0) {
                        feasibleBnBA.push_back(1.0);
                    } else {
                        feasibleBnBA.push_back(0.0);
                    }
                } else if (solver.compare("BnBSolverB") == 0) {
                    primalBoundsBnBB.push_back(primalBound);
                    dualBoundsBnBB.push_back(dualBound);

                    if (solutionsFound > 0) {
                        feasibleBnBB.push_back(1.0);
                    } else {
                        feasibleBnBB.push_back(0.0);
                    }
                } else if (solver.compare("BnCSolverA") == 0) {
                    primalBoundsBnCA.push_back(primalBound);
                    dualBoundsBnCA.push_back(dualBound);

                    if (solutionsFound > 0) {
                        feasibleBnCA.push_back(1.0);
                    } else {
                        feasibleBnCA.push_back(0.0);
                    }
                } else if (solver.compare("BnCSolverB") == 0) {
                    primalBoundsBnCB.push_back(primalBound);
                    dualBoundsBnCB.push_back(dualBound);

                    if (solutionsFound > 0) {
                        feasibleBnCB.push_back(1.0);
                    } else {
                        feasibleBnCB.push_back(0.0);
                    }
                } else if (solver.compare("GRASPA") == 0) {
                    primalBoundsGRASPA.push_back(primalBound);
                    dualBoundsGRASPA.push_back(dualBound);

                    if (solutionsFound > 0) {
                        feasibleGRASPA.push_back(1.0);
                    } else {
                        feasibleGRASPA.push_back(0.0);
                    }

                    totalIterationsGRASPA += totalIterations;
                    notFeasibleGRASPA += notFeasible;
                    notConnectedGRASPA += notConnected;
                    dontRespectCapacityGRASPA += dontRespectCapacity;
                    notBalancedGRASPA += notBalanced;
                    fixedSolutionsGRASPA += fixedSolutions;
                    ratioMeanGRASPA += ratioMean;
                } else if (solver.compare("GRASPB") == 0) {
                    primalBoundsGRASPB.push_back(primalBound);
                    dualBoundsGRASPB.push_back(dualBound);

                    if (solutionsFound > 0) {
                        feasibleGRASPB.push_back(1.0);
                    } else {
                        feasibleGRASPB.push_back(0.0);
                    }

                    totalIterationsGRASPB += totalIterations;
                    notFeasibleGRASPB += notFeasible;
                    notConnectedGRASPB += notConnected;
                    dontRespectCapacityGRASPB += dontRespectCapacity;
                    notBalancedGRASPB += notBalanced;
                    fixedSolutionsGRASPB += fixedSolutions;
                    ratioMeanGRASPB += ratioMean;
                }
            }
        }

        n = 72;

        assert(primalBoundsBnBA.size() == n);
        assert(dualBoundsBnBA.size() == n);
        assert(feasibleBnBA.size() == n);
        assert(primalBoundsBnBB.size() == n);
        assert(dualBoundsBnBB.size() == n);
        assert(feasibleBnBB.size() == n);
        assert(primalBoundsBnCA.size() == n);
        assert(dualBoundsBnCA.size() == n);
        assert(feasibleBnCA.size() == n);
        assert(primalBoundsBnCB.size() == n);
        assert(dualBoundsBnCB.size() == n);
        assert(feasibleBnCB.size() == n);
        assert(primalBoundsGRASPA.size() == n);
        assert(dualBoundsGRASPA.size() == n);
        assert(feasibleGRASPA.size() == n);
        assert(primalBoundsGRASPB.size() == n);
        assert(dualBoundsGRASPB.size() == n);
        assert(feasibleGRASPB.size() == n);

        for (unsigned int i = 0; i < n; i++) {
            unsigned int primalBoundBnBA,
                         primalBoundBnBB,
                         primalBoundBnCA,
                         primalBoundBnCB,
                         primalBoundGRASPA,
                         primalBoundGRASPB;
            double dualBoundBnBA,
                   dualBoundBnBB,
                   dualBoundBnCA,
                   dualBoundBnCB,
                   dualBoundGRASPA,
                   dualBoundGRASPB,
                   bestDualBound;

            primalBoundBnBA = primalBoundsBnBA[i];
            primalBoundBnBB = primalBoundsBnBB[i];
            primalBoundBnCA = primalBoundsBnCA[i];
            primalBoundBnCB = primalBoundsBnCB[i];
            primalBoundGRASPA = primalBoundsGRASPA[i];
            primalBoundGRASPB = primalBoundsGRASPB[i];

            dualBoundBnBA = dualBoundsBnBA[i];
            dualBoundBnBB = dualBoundsBnBB[i];
            dualBoundBnCA = dualBoundsBnCA[i];
            dualBoundBnCB = dualBoundsBnCB[i];
            dualBoundGRASPA = dualBoundsGRASPA[i];
            dualBoundGRASPB = dualBoundsGRASPB[i];

            bestDualBound = DBL_MAX;

            if (bestDualBound > dualBoundBnBA) {
                bestDualBound = dualBoundBnBA;
            }

            if (bestDualBound > dualBoundBnBB) {
                bestDualBound = dualBoundBnBB;
            }

            if (bestDualBound > dualBoundBnCA) {
                bestDualBound = dualBoundBnCA;
            }

            if (bestDualBound > dualBoundBnCB) {
                bestDualBound = dualBoundBnCB;
            }

            if (bestDualBound > dualBoundGRASPA) {
                bestDualBound = dualBoundGRASPA;
            }

            if (bestDualBound > dualBoundGRASPB) {
                bestDualBound = dualBoundGRASPB;
            }

            if (primalBoundBnBA > 0 && bestDualBound < DBL_MAX) {
                double gap = (bestDualBound - ((double) primalBoundBnBA));
                gap /= ((double) primalBoundBnBA);
                gapBnBA.push_back(gap);
            }

            if (primalBoundBnBB > 0 && bestDualBound < DBL_MAX) {
                double gap = (bestDualBound - ((double) primalBoundBnBB));
                gap /= ((double) primalBoundBnBB);
                gapBnBB.push_back(gap);
            }

            if (primalBoundBnCA > 0 && bestDualBound < DBL_MAX) {
                double gap = (bestDualBound - ((double) primalBoundBnCA));
                gap /= ((double) primalBoundBnCA);
                gapBnCA.push_back(gap);
            }

            if (primalBoundBnCB > 0 && bestDualBound < DBL_MAX) {
                double gap = (bestDualBound - ((double) primalBoundBnCB));
                gap /= ((double) primalBoundBnCB);
                gapBnCB.push_back(gap);
            }

            if (primalBoundGRASPA > 0 && bestDualBound < DBL_MAX) {
                double gap = (bestDualBound - ((double) primalBoundGRASPA));
                gap /= ((double) primalBoundGRASPA);
                gapGRASPA.push_back(gap);
            }

            if (primalBoundGRASPB > 0 && bestDualBound < DBL_MAX) {
                double gap = (bestDualBound - ((double) primalBoundGRASPB));
                gap /= ((double) primalBoundGRASPB);
                gapGRASPB.push_back(gap);
            }

            if (primalBoundBnBA <= bestDualBound && 
                    bestDualBound < 1.0 + primalBoundBnBA) {
                optBnBA.push_back(1.0);
            } else {
                optBnBA.push_back(0.0);
            }

            if (primalBoundBnBB <= bestDualBound && 
                    bestDualBound < 1.0 + primalBoundBnBB) {
                optBnBB.push_back(1.0);
            } else {
                optBnBB.push_back(0.0);
            }

            if (primalBoundBnCA <= bestDualBound && 
                    bestDualBound < 1.0 + primalBoundBnCA) {
                optBnCA.push_back(1.0);
            } else {
                optBnCA.push_back(0.0);
            }

            if (primalBoundBnCB <= bestDualBound && 
                    bestDualBound < 1.0 + primalBoundBnCB) {
                optBnCB.push_back(1.0);
            } else {
                optBnCB.push_back(0.0);
            }

            if (primalBoundGRASPA <= bestDualBound && 
                    bestDualBound < 1.0 + primalBoundGRASPA) {
                optGRASPA.push_back(1.0);
            } else {
                optGRASPA.push_back(0.0);
            }

            if (primalBoundGRASPB <= bestDualBound && 
                    bestDualBound < 1.0 + primalBoundGRASPB) {
                optGRASPB.push_back(1.0);
            } else {
                optGRASPB.push_back(0.0);
            }
        }

        assert(gapBnBA.size() <= n);
        assert(gapBnBB.size() <= n);
        assert(gapBnCA.size() <= n);
        assert(gapBnCB.size() <= n);
        assert(gapGRASPA.size() <= n);
        assert(gapGRASPB.size() <= n);

        assert(optBnBA.size() == n);
        assert(optBnBB.size() == n);
        assert(optBnCA.size() == n);
        assert(optBnCB.size() == n);
        assert(optGRASPA.size() == n);
        assert(optGRASPB.size() == n);

        feasibleRatioBnBA = 0.0;
        for (const double & feasible : feasibleBnBA) {
            feasibleRatioBnBA += feasible;
        }
        feasibleRatioBnBA /= (double) feasibleBnBA.size();

        feasibleRatioBnBB = 0.0;
        for (const double & feasible : feasibleBnBB) {
            feasibleRatioBnBB += feasible;
        }
        feasibleRatioBnBB /= (double) feasibleBnBB.size();

        feasibleRatioBnCA = 0.0;
        for (const double & feasible : feasibleBnCA) {
            feasibleRatioBnCA += feasible;
        }
        feasibleRatioBnCA /= (double) feasibleBnCA.size();

        feasibleRatioBnCB = 0.0;
        for (const double & feasible : feasibleBnCB) {
            feasibleRatioBnCB += feasible;
        }
        feasibleRatioBnCB /= (double) feasibleBnCB.size();

        feasibleRatioGRASPA = 0.0;
        for (const double & feasible : feasibleGRASPA) {
            feasibleRatioGRASPA += feasible;
        }
        feasibleRatioGRASPA /= (double) feasibleGRASPA.size();

        feasibleRatioGRASPB = 0.0;
        for (const double & feasible : feasibleGRASPB) {
            feasibleRatioGRASPB += feasible;
        }
        feasibleRatioGRASPB /= (double) feasibleGRASPB.size();

        meanGapBnBA = 0.0;
        for (const double & gap : gapBnBA) {
            meanGapBnBA += gap;
        }
        meanGapBnBA /= (double) gapBnBA.size();

        meanGapBnBB = 0.0;
        for (const double & gap : gapBnBB) {
            meanGapBnBB += gap;
        }
        meanGapBnBB /= (double) gapBnBB.size();

        meanGapBnCA = 0.0;
        for (const double & gap : gapBnCA) {
            meanGapBnCA += gap;
        }
        meanGapBnCA /= (double) gapBnCA.size();

        meanGapBnCB = 0.0;
        for (const double & gap : gapBnCB) {
            meanGapBnCB += gap;
        }
        meanGapBnCB /= (double) gapBnCB.size();

        meanGapGRASPA = 0.0;
        for (const double & gap : gapGRASPA) {
            meanGapGRASPA += gap;
        }
        meanGapGRASPA /= (double) gapGRASPA.size();

        meanGapGRASPB = 0.0;
        for (const double & gap : gapGRASPB) {
            meanGapGRASPB += gap;
        }
        meanGapGRASPB /= (double) gapGRASPB.size();

        optRatioBnBA = 0.0;
        for (const double & opt : optBnBA) {
            optRatioBnBA += opt;
        }
        optRatioBnBA /= (double) optBnBA.size();

        optRatioBnBB = 0.0;
        for (const double & opt : optBnBB) {
            optRatioBnBB += opt;
        }
        optRatioBnBB /= (double) optBnBB.size();

        optRatioBnCA = 0.0;
        for (const double & opt : optBnCA) {
            optRatioBnCA += opt;
        }
        optRatioBnCA /= (double) optBnCA.size();

        optRatioBnCB = 0.0;
        for (const double & opt : optBnCB) {
            optRatioBnCB += opt;
        }
        optRatioBnCB /= (double) optBnCB.size();

        optRatioGRASPA = 0.0;
        for (const double & opt : optGRASPA) {
            optRatioGRASPA += opt;
        }
        optRatioGRASPA /= (double) optGRASPA.size();

        optRatioGRASPB = 0.0;
        for (const double & opt : optGRASPB) {
            optRatioGRASPB += opt;
        }
        optRatioGRASPB /= (double) optGRASPB.size();

        std::cout << "T, "
                  << T << ", " 
                  << std::setprecision(4) << std::fixed
                  << feasibleRatioBnBA << ", "
                  << meanGapBnBA << ", "
                  << optRatioBnBA << ", "
                  << feasibleRatioBnBB << ", "
                  << meanGapBnBB << ", "
                  << optRatioBnBB << ", "
                  << feasibleRatioBnCA << ", "
                  << meanGapBnCA << ", "
                  << optRatioBnCA << ", "
                  << feasibleRatioBnCB << ", "
                  << meanGapBnCB << ", "
                  << optRatioBnCB << ", "
                  << feasibleRatioGRASPA << ", "
                  << meanGapGRASPA << ", "
                  << optRatioGRASPA << ", "
                  << feasibleRatioGRASPB << ", "
                  << meanGapGRASPB << ", "
                  << optRatioGRASPB << ", "
                  << ((double) notFeasibleGRASPA) / ((double) totalIterationsGRASPA) << ", "
                  << ((double) notConnectedGRASPA) / ((double) notFeasibleGRASPA) << ", "
                  << ((double) dontRespectCapacityGRASPA) / ((double) notFeasibleGRASPA) << ", "
                  << ((double) notBalancedGRASPA) / ((double) notFeasibleGRASPA) << ", "
                  << ((double) fixedSolutionsGRASPA) / ((double) notFeasibleGRASPA) << ", "
                  << ratioMeanGRASPA / ((double) n) << ", "
                  << ((double) notFeasibleGRASPB) / ((double) totalIterationsGRASPB) << ", "
                  << ((double) notConnectedGRASPB) / ((double) notFeasibleGRASPB) << ", "
                  << ((double) dontRespectCapacityGRASPB) / ((double) notFeasibleGRASPB) << ", "
                  << ((double) notBalancedGRASPB) / ((double) notFeasibleGRASPB) << ", "
                  << ((double) fixedSolutionsGRASPB) / ((double) notFeasibleGRASPB) << ", "
                  << ratioMeanGRASPB / ((double) n) << std::endl;
    }

    return 0;
}

