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
                    this->instance.getG().getInducedSubGraph(district).getConnectedComponents();

                if (connectedComponents.size() > 1) {
                    for (unsigned int i = 0; i < connectedComponents.size(); i++) {
                        std::set<Edge> cut =
                            this->instance.getG().getAdjacentEdges(connectedComponents[i].
                                    getEdges());

                        for (const Edge & e : connectedComponents[i].getEdges()) {
                            unsigned int eId = this->instance.getG().getEdgeId(e);

                            for (unsigned int k = 0; k < connectedComponents.size(); k++) {
                                if (k != i) {
                                    for (const Edge & f : connectedComponents[k].getEdges()) {
                                        unsigned int fId = this->instance.getG().getEdgeId(f);

                                        GRBLinExpr constr = 0.0;
                                        constr += this->x[eId - 1][j];
                                        constr += this->x[fId - 1][j];

                                        for (const Edge & g : cut) {
                                            unsigned int gId = this->instance.getG().getEdgeId(g);

                                            constr -= this->x[gId - 1][j];
                                        }

                                        this->addLazy(constr <= 1);
                                    }
                                }
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

