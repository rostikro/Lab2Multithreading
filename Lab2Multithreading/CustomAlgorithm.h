#pragma once
#include <thread>

namespace custom_algorithm
{    
    template <class It, class Pr>
    bool all_of(int threadsCount, It itBegin, It itEnd, Pr pred)
    {        
        std::vector<bool> results(threadsCount);
        std::vector<std::thread> threads;
    
        int distance = std::distance(itBegin, itEnd);
        const int step = distance / threadsCount;

        int off = distance % threadsCount;

        // first thread operates with bigger data
        threads.push_back(std::thread([&results, &itBegin, off, &step, &pred](){ results[0] = std::all_of(std::execution::unseq, itBegin, itBegin + off + step, pred); }));
        
        for (int i=1; i<threadsCount; i++)
        {
            off += step;
            threads.push_back(std::thread([i, &results, &itBegin, off, &step, &pred](){ results[i] = std::all_of(std::execution::unseq, itBegin + off, itBegin + off + step, pred); }));
        }

        for (int i=0; i<threadsCount; i++)
        {
            threads[i].join();
        }

        auto isTrue = [](const bool &v) { return v; };
        return std::all_of(results.begin(), results.end(), isTrue);
    }
}
