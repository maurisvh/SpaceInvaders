#include "random.h"

namespace si {
    RandomGenerator::RandomGenerator()
        : device(), engine(device()),
          standardUniformDistribution(0, 1) {}

    RandomGenerator RandomGenerator::rg;

    float RandomGenerator::random() {
        return standardUniformDistribution(engine);
    }
}
