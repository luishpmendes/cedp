#include "ArgumentParser.hpp"
#include "../graph/Graph.hpp"
#include <chrono>

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("-V") && argParser.cmdOptionExists("-E")) {
        unsigned int V = std::stoul(argParser.getCmdOption("-V"));
        unsigned int E = std::stoul(argParser.getCmdOption("-E"));
        unsigned int maxDemand = 100;
        bool isGrid = argParser.cmdOptionExists("--grid");
        bool isEuclidean = argParser.cmdOptionExists("--euclidean");
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

        if (argParser.cmdOptionExists("--max-demand")) {
            maxDemand = std::stoul(argParser.getCmdOption("--max-demand"));
        }

        if (argParser.cmdOptionExists("--seed")) {
            seed = std::stoul(argParser.getCmdOption("--seed"));
        }

        Graph G;

        if (!isGrid) {
            G = Graph::generateRandomConnectedGraph(V, E, maxDemand, isEuclidean, seed);
        } else {
            unsigned int r, c;
            r = c = round(sqrt(V));
            G = Graph::generateRandomConnectedGridGraph(r, c, E, maxDemand, isEuclidean, seed);
        }

        G.write();
    } else {
        std::cerr << "./GraphGeneratorExec -V <V> -E <E> --grid --euclidean " 
            << " --max-demand <maxDemand> --seed <seed>" << std::endl;
    }
}

