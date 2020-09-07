#pragma once

#include <chrono>
#include <functional>
#include <random>
#include <vector>

class Benchmark
{
private:
    std::minstd_rand lcg;
    std::mt19937 mt;
    std::ranlux24_base ranlux;

public:
    Benchmark ();

    using duration = std::chrono::high_resolution_clock::duration;

    duration TimeOnce (std::function<void ()> function);
    duration TimeOnce (std::function<void (uint64_t)> function, uint64_t iterations);
    duration TimeOnLCG (std::function<void (std::minstd_rand&, uint64_t)> function, uint64_t iterations);
    duration TimeOnMersenneTwister (std::function<void (std::mt19937&, uint64_t)> function, uint64_t iterations);
    duration TimeOnRANLUX (std::function<void (std::ranlux24_base&, uint64_t)> function, uint64_t iterations);
    duration TimeOnRandomData (std::function<void (std::vector<uint32_t>&)>, uint64_t iterations);
};
