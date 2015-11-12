#pragma once
#include <random>

namespace si {
    class RandomGenerator {
    public:
        /// Return the singleton RandomGenerator instance.
        static RandomGenerator &instance();

        /// Generate a random double in the interval [0, 1).
        double random();
    
    private:
        RandomGenerator();

        std::random_device device;
        std::default_random_engine engine;
        std::uniform_real_distribution<double> standardUniformDistribution;

        // This is a singleton class. Don't allow copies.
        RandomGenerator(RandomGenerator const &) = delete;
        void operator=(RandomGenerator const &) = delete;
    };
}
