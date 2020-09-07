#include "Benchmark.h"

Benchmark::Benchmark ()
{
    std::random_device rd;

    lcg.seed (rd ());

    using result_type = std::random_device::result_type;

    result_type ranluxSeed[std::ranlux24_base::word_size];
    std::generate (std::begin (ranluxSeed), std::end (ranluxSeed), std::ref (rd));
    std::seed_seq ranluxSeedSequence (std::begin (ranluxSeed), std::end (ranluxSeed));
    ranlux.seed (ranluxSeedSequence);

    result_type mtSeed[std::mt19937::state_size];
    std::generate (std::begin (mtSeed), std::end (mtSeed), std::ref (rd));
    std::seed_seq mtSeedSequence (std::begin (mtSeed), std::end (mtSeed));
    mt.seed (mtSeedSequence);
}

using std::chrono::high_resolution_clock;
using duration = high_resolution_clock::duration;

duration Benchmark::TimeOnce (std::function<void ()> function)
{
    auto start = high_resolution_clock::now ();
    function ();
    auto end = high_resolution_clock::now ();
    return end - start;
}

duration Benchmark::TimeOnce (std::function<void (uint64_t)> function, uint64_t iterations)
{
    auto start = high_resolution_clock::now ();
    function (iterations);
    auto end = high_resolution_clock::now ();
    return end - start;
}

duration Benchmark::TimeOnLCG (std::function<void (std::minstd_rand&, uint64_t)> function, uint64_t iterations)
{
    auto start = high_resolution_clock::now ();
    function (lcg, iterations);
    auto end = high_resolution_clock::now ();
    return end - start;
}

duration Benchmark::TimeOnMersenneTwister (std::function<void (std::mt19937&, uint64_t)> function, uint64_t iterations)
{
    auto start = high_resolution_clock::now ();
    function (mt, iterations);
    auto end = high_resolution_clock::now ();
    return end - start;
}

duration Benchmark::TimeOnRANLUX (std::function<void (std::ranlux24_base&, uint64_t)> function, uint64_t iterations)
{
    auto start = high_resolution_clock::now ();
    function (ranlux, iterations);
    auto end = high_resolution_clock::now ();
    return end - start;
}

duration Benchmark::TimeOnRandomData (std::function<void (std::vector<uint32_t>&)> function, uint64_t iterations)
{
    std::vector<uint32_t> data (iterations);
    std::generate (data.begin (), data.end (), std::ref (mt));
    auto start = high_resolution_clock::now ();
    function (data);
    auto end = high_resolution_clock::now ();
    return end - start;
}
