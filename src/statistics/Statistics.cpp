#include "Statistics.hpp"
#include <cmath>

/* Creates a new data structure for statistics of a sequence of values. */
Statistics::Statistics() : size(0.0), mean(0.0), variance(0.0), 
    standardDeviation(0.0) {}


/* 
 * Returns this statistics' sequence size.
 *
 * @return this statistics' sequence size.
 */
unsigned int Statistics::getSize() const {
    return this->size;
}

/*
 * Returns this statistics' sequence mean.
 *
 * @return this statistics' sequence mean.
 */
double Statistics::getMean() const {
    return this->mean;
}

/*
 * Returns this statistics' sequence variance.
 *
 * @return this statistics' sequence variance.
 */
double Statistics::getVariance() const {
    return this->variance;
}

/*
 * Returns this statistics' sequence standard deviation.
 *
 * @return this statistics' sequence standard deviation.
 */
double Statistics::getStandardDeviation() const {
    return this->standardDeviation;
}

/*
 * Adds a new value into this statistics' sequence.
 *
 * @param value the new value to be added into this statistics' sequence.
 */
void Statistics::addValue(double value) {
    double oldMean = this->mean;
    this->size++;
    this->mean += (value - oldMean) / this->size;
    this->variance += ((value - oldMean) * (value - this->mean) - this->variance) / this->size;
    this->standardDeviation = std::sqrt(this->variance);
}

