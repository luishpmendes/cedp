#include "../solver/metaheuristic/grasp/GRASPSolver.hpp"
#include "ArgumentParser.hpp"

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("--instance") && 
            argParser.cmdOptionExists("--time-limit") && 
            argParser.cmdOptionExists("--m") && 
            argParser.cmdOptionExists("--k")) {
        std::string instanceFilename = argParser.getCmdOption("--instance");
        unsigned int timeLimit = std::stoul(argParser.getCmdOption("--time-limit"));
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        unsigned int m = std::stoul(argParser.getCmdOption("--m"));
        unsigned int k = std::stoul(argParser.getCmdOption("--k"));

        if (argParser.cmdOptionExists("--seed")) {
            seed = std::stoul(argParser.getCmdOption("--seed"));
        }

        Instance instance (instanceFilename);
        GRASPSolver solver = GRASPSolver(instance, timeLimit, seed, m, k);

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

        std::cout << -((int) solver.getBestPrimalBound()) << " " << 
            solver.getSolvingTime() << std::endl; 
    } else {
        std::cerr << "./GRASPSolverExec --instance <instanceFilename> " << 
            "--time-limit <timeLimit> --seed <seed> --alpha <alpha> " << 
            "--statistics <solverStatisticsFilename> " << 
            "--solution <solutionFilename>" << std::endl;
    }

    return 0;
}

