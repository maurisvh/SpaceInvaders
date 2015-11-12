#include "random.h"

namespace si {
    RandomGenerator::RandomGenerator()
        : device(), engine(device()),
          standardUniformDistribution(0, 1) {}

    RandomGenerator &RandomGenerator::instance() {
        static RandomGenerator randomGenerator;
        return randomGenerator;
    }

    double RandomGenerator::random() {
        return standardUniformDistribution(engine);
    }
}
