#pragma once

#include "gurobi_c++.h"
#include "../../../instance/Instance.hpp"

/**
 * The BnCSolverCallback class represents a BnCSolver's callback class that 
 * cuts-off solution with disconnected districts.
 */
class BnCSolverCallback : public GRBCallback {
    private:
        /**
         * This callback's instance.
         */
        Instance instance;

        /**
         * This callback's variables.
         */
        std::vector<std::vector<GRBVar> > x;
    protected:
        /**
         * The callback function.
         */
        void callback();
    public:
        /**
         * Constructs a new callback.
         *
         * @param instance the new callback's instance.
         * @param x        the new callback's variables.
         */
        BnCSolverCallback(const Instance & instance, 
                const std::vector<std::vector<GRBVar> > & x);
};

