#include "../solver/metaheuristic/lagrangian-heuristic/LagrangianHeuristicSolver1.hpp"
#include "ArgumentParser.hpp"

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("--instance") && 
            argParser.cmdOptionExists("--time-limit") && 
            argParser.cmdOptionExists("-N")) {
        std::string instanceFilename = argParser.getCmdOption("--instance");
        unsigned int timeLimit = std::stoul(argParser.getCmdOption("--time-limit"));
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        unsigned int N = std::stoul(argParser.getCmdOption("-N"));

        if (argParser.cmdOptionExists("--seed")) {
            seed = std::stoul(argParser.getCmdOption("--seed"));
        }

        Instance instance (instanceFilename);
        LagrangianHeuristicSolver1 solver (instance, timeLimit, seed, N);

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
        std::cerr << "./LagrangianHeuristicSolver1Exec " << 
            "--instance <instanceFilename> --time-limit <timeLimit> " << 
            "--seed <seed> -N <N> --statistics <solverStatisticsFilename> " << 
            "--solution <solutionFilename>" << std::endl;
    }

    return 0;
}

