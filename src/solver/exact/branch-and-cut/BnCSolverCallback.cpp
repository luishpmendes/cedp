#include "BnCSolverCallback.hpp"

/**
 * Constructs a new callback.
 *
 * @param instance the new callback's instance.
 * @param x        the new callback's variables.
 */
BnCSolverCallback::BnCSolverCallback(const Instance & instance, 
        const std::vector<std::vector<GRBVar> > & x) : 
    instance(instance), x(x) {}

/**
 * The callback function.
 */
void BnCSolverCallback::callback() {
    try {
        if (this->where == GRB_CB_MIPSOL) {
            for (unsigned int j = 0; j < this->instance.getM(); j++) {
                std::set<Edge> district;

                for (const Edge & e : this->instance.getG().getEdges()) {
                    unsigned int eId = this->instance.getG().getEdgeId(e);

                    if (this->getSolution(this->x[eId - 1][j]) >= 0.5) {
                        district.insert(e);
                    }
                }

                std::vector<Graph> connectedComponents = 
                    this->instance.getG().getInducedSubGraph(district).
                    getConnectedComponents();

                if (connectedComponents.size() > 1) {
                    std::vector<unsigned int> edgeComponent (this->instance.getG().getMaxEid(),
                            connectedComponents.size());
                    std::vector<GRBLinExpr> cutExpr (connectedComponents.size(), 0);

                    for (unsigned int i = 0; i < connectedComponents.size(); i++) {
                        std::set<Edge> componentEdges = connectedComponents[i].getEdges();

                        for (const Edge & e : componentEdges) {
                            unsigned int eId = connectedComponents[i].getEdgeId(e);

                            edgeComponent[eId - 1] = i;
                        }

                        std::set<Edge> cutEdges =
                            this->instance.getG().getAdjacentEdges(componentEdges);

                        for (const Edge & e : cutEdges) {
                            unsigned int eId = this->instance.getG().getEdgeId(e);

                            cutExpr[i] += this->x[eId - 1][j];
                        }
                    }

                    for (const Edge & e : district) {
                        unsigned int eId = this->instance.getG().getEdgeId(e);

                        for (const Edge & f : district) {
                            unsigned int fId = this->instance.getG().getEdgeId(f);

                            if (edgeComponent[eId - 1] != edgeComponent[fId - 1]) {
                                GRBLinExpr constr = this->x[eId - 1][j] + this->x[fId - 1][j] -
                                    cutExpr[edgeComponent[eId - 1]];

                                this->addLazy(constr <= 1);
                            }
                        }
                    }
                }
            }
        }
    } catch (GRBException e) {
        std::cerr << "Error number: " << e.getErrorCode() << std::endl;
        std::cerr << e.getMessage() << std::endl;
    } catch (...) {
        std::cerr << "Error during callback" << std::endl;
    }
}

