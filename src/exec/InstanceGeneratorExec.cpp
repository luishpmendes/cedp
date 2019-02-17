#include "../instance/Instance.hpp"
#include "ArgumentParser.hpp"
#include <chrono>

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if (argParser.cmdOptionExists("-m")) {
        unsigned int m = std::stoul(argParser.getCmdOption("-m"));
        double B = 0.2;
        double D = 0.5;

        if (argParser.cmdOptionExists("-B")) {
            B = std::stod(argParser.getCmdOption("-B"));
        }

        if (argParser.cmdOptionExists("-D")) {
            D = std::stod(argParser.getCmdOption("-D"));
        }

        Graph G (std::cin);

        double dE = G.getEdgesWeight();
        unsigned int maxD = round(((2.0 * (1.0 + (D * B))) / ((double) m)) * ((double) dE));

        Instance instance (m, maxD, B, G);

        instance.write();
    } else {
        std::cerr << "./ArtificialInstanceGenerator -m <m> -B <B> -D <D>" << std::endl;
    }

    return 0;
}

