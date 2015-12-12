#pragma once
#include <random>

namespace si {
    class RandomGenerator {
    public:
        /// The singleton RandomGenerator instance.
        static RandomGenerator rg;

        /// Generate a random float in the interval [0, 1).
        float random();

        /// Generate a random float in the interval [a, b).
        float random(float a, float b);
    
    private:
        RandomGenerator();

        std::random_device device;
        std::default_random_engine engine;
        std::uniform_real_distribution<float> standardUniformDistribution;

        // This is a singleton class. Don't allow copies.
        RandomGenerator(RandomGenerator const &) = delete;
        void operator=(RandomGenerator const &) = delete;
    };
}
