#include "../solution/Solution.hpp"
#include <cassert>

int main () {
    Instance instance;
    std::vector<std::set<Edge> > E;
    Solution solution;

    instance = Instance("instances/exampleA.in");

    E = std::vector<std::set<Edge> > (instance.getM());

    E[0].insert(Edge(0, 1, 1));

    E[1].insert(Edge(1, 2, 1));

    solution = Solution(instance, E);

    assert(solution.getValue() == 2);

    assert(solution.isFeasible());

    instance = Instance("instances/exampleB.in");

    E = std::vector<std::set<Edge> > (instance.getM());

    E[0].insert(Edge(0, 1, 1));

    E[1].insert(Edge(1, 2, 1));
    
    E[2].insert(Edge(0, 2, 1));

    solution = Solution(instance, E);

    assert(solution.getValue() == 3);

    assert(solution.isFeasible());

    instance = Instance("instances/exampleC.in");

    E = std::vector<std::set<Edge> > (instance.getM());

    E[0].insert(Edge(0, 1, 1));
    E[0].insert(Edge(0, 3, 1));
    E[0].insert(Edge(1, 2, 1));
    E[0].insert(Edge(2, 5, 1));

    E[1].insert(Edge(1, 4, 1));
    E[1].insert(Edge(3, 4, 1));
    E[1].insert(Edge(4, 5, 1));
    E[1].insert(Edge(4, 7, 1));

    E[2].insert(Edge(3, 6, 1));
    E[2].insert(Edge(5, 8, 1));
    E[2].insert(Edge(6, 7, 1));
    E[2].insert(Edge(7, 8, 1));

    solution = Solution(instance, E);

    assert(solution.getValue() == 12);

    assert(solution.isFeasible());

    instance = Instance("instances/exampleD.in");

    E = std::vector<std::set<Edge> > (instance.getM());

    E[0].insert(Edge(0, 1, 1));
    E[0].insert(Edge(0, 6, 1));
    E[0].insert(Edge(1, 2, 1));
    E[0].insert(Edge(2, 6, 1));

    E[1].insert(Edge(2, 3, 1));
    E[1].insert(Edge(2, 5, 1));
    E[1].insert(Edge(3, 4, 1));
    E[1].insert(Edge(4, 5, 1));

    solution = Solution(instance, E);

    assert(solution.getValue() == 12);

    assert(solution.isFeasible());

    instance = Instance("instances/exampleF.in");

    E = std::vector<std::set<Edge> > (instance.getM());

    E[0].insert(Edge(0, 1, 1));
    E[0].insert(Edge(0, 4, 3));
    E[0].insert(Edge(0, 5, 3));
    E[0].insert(Edge(1, 2, 2));
    E[0].insert(Edge(1, 6, 4));
    E[0].insert(Edge(5, 7, 7));
    E[0].insert(Edge(6, 8, 8));

    E[1].insert(Edge(2, 3, 3));
    E[1].insert(Edge(2, 7, 5));
    E[1].insert(Edge(3, 4, 4));
    E[1].insert(Edge(3, 8, 6));
    E[1].insert(Edge(5, 8, 7));

    E[2].insert(Edge(4, 9, 7));
    E[2].insert(Edge(6, 9, 8));
    E[2].insert(Edge(7, 9, 9));

    solution = Solution(instance, E);

    assert(solution.getValue() == 84);

    assert(solution.isFeasible());

    return 0;
}

