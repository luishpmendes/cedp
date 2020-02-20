#pragma once

/*
 * The Statistics class represents a data structure for keeping track of
 * statistics of a sequence of values.
 */
class Statistics {
    private:
        /*
         * This statistics' sequence size.
         */
        unsigned int size;

        /*
         * This statistics' sequence mean.
         */
        double mean;

        /*
         * This statistics' sequence variance.
         */
        double variance;

        /*
         * This statistics' sequence standard deviation.
         */
        double standardDeviation;

    public:
        /*
         * Creates a new data structure for statistics of a sequence of values.
         */
        Statistics();

        /* 
         * Returns this statistics' sequence size.
         *
         * @return this statistics' sequence size.
         */
        unsigned int getSize() const;

        /*
         * Returns this statistics' sequence mean.
         *
         * @return this statistics' sequence mean.
         */
        double getMean() const;

        /*
         * Returns this statistics' sequence variance.
         *
         * @return this statistics' sequence variance.
         */
        double getVariance() const;

        /*
         * Returns this statistics' sequence standard deviation.
         *
         * @return this statistics' sequence standard deviation.
         */
        double getStandardDeviation() const;

        /*
         * Adds a new value into this statistics' sequence.
         *
         * @param value the new value to be added into this statistics' 
         *              sequence.
         */
        void addValue(double value);
};

