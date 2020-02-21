#include "../statistics/Statistics.hpp"
#include <cassert>
#include <cmath>

int main () {
    Statistics statistics;

    assert(statistics.getSize() == 0);
    assert(fabs(statistics.getMean()) < 0.001);
    assert(fabs(statistics.getVariance()) < 0.001);
    assert(fabs(statistics.getStandardDeviation()) < 0.001);

    statistics.addValue(89.0);

    assert(statistics.getSize() == 1);
    assert(fabs(statistics.getMean() - 89.0) < 0.001);
    assert(fabs(statistics.getVariance()) < 0.001);
    assert(fabs(statistics.getStandardDeviation()) < 0.001);

    statistics.addValue(13.0);

    assert(statistics.getSize() == 2);
    assert(fabs(statistics.getMean() - 51.0) < 0.001);
    assert(fabs(statistics.getVariance() - 1444.0) < 0.001);
    assert(fabs(statistics.getStandardDeviation() - 38.0) < 0.001);

    statistics.addValue(5.0);

    assert(statistics.getSize() == 3);
    assert(fabs(statistics.getMean() - 35.66667) < 0.001);
    assert(fabs(statistics.getVariance() - 1432.88889) < 0.001);
    assert(fabs(statistics.getStandardDeviation() - 37.85352) < 0.001);

    statistics.addValue(3.0);

    assert(statistics.getSize() == 4);
    assert(fabs(statistics.getMean() - 27.5) < 0.001);
    assert(fabs(statistics.getVariance() - 1274.75) < 0.001);
    assert(fabs(statistics.getStandardDeviation() - 35.70364) < 0.001);

    statistics.addValue(2.0);

    assert(statistics.getSize() == 5);
    assert(fabs(statistics.getMean() - 22.4) < 0.001);
    assert(fabs(statistics.getVariance() - 1123.84) < 0.001);
    assert(fabs(statistics.getStandardDeviation() - 33.52372) < 0.001);

    return 0;
}

