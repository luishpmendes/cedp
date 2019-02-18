#include "../solver/exact/branch-and-bound/BnBSolver.hpp"
#include "ArgumentParser.hpp"

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("--instance") && argParser.cmdOptionExists("--time-limit")) {
        std::string instanceFilename = argParser.getCmdOption("--instance");
        unsigned int timeLimit = std::stoul(argParser.getCmdOption("--time-limit"));
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

        if (argParser.cmdOptionExists("--seed")) {
            seed = std::stoul(argParser.getCmdOption("--seed"));
        }

        Instance instance (instanceFilename);
        BnBSolver solver = BnBSolver(instance, timeLimit, seed);

        solver.solve();

        if (argParser.cmdOptionExists("--statistics")) {
            std::string solverStatisticsFilename = argParser.getCmdOption("--statistics");

            solver.write(solverStatisticsFilename);
        }

        if (argParser.cmdOptionExists("--solution")) {
            std::string solutionFilename = argParser.getCmdOption("--solution");

            if (solver.getSolutionsCounter() > 0) {
                solver.getBestPrimalSolution().write(solutionFilename);
            }
        }
    } else {
        std::cerr << "./BnBSolverExec --instance <instanceFilename> " << 
            "--time-limit <timeLimit> --seed <seed> " << 
            "--statistics <solverStatisticsFilename> " << 
            "--solution <solutionFilename>" << std::endl;
    }

    return 0;
}

