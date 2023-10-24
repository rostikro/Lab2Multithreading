#include "Tests.h"

#include <algorithm>
#include <execution>
#include <iostream>

#include "CustomAlgorithm.h"
#include "Timer.h"


Tests::Tests(int init)
    : testData1k(1000, init), testData1m(1000000, init), testData10m(10000000, init)
{
}

void Tests::TestDefaultBehaviour()
{
    auto isPositive = [](const auto &v) { return v > 0; };

    // Default exec policy
    Timer timer;
    std::vector<float> testResults;
    
    // an empty test in order to overclock the CPU, otherwise the first test will always be slower
    std::all_of(testData1k.begin(), testData1k.end(), isPositive);

    timer.Reset();
    std::all_of(testData1k.begin(), testData1k.end(), isPositive);
    testResults.push_back(timer.Elapsed());
    
    timer.Reset();
    std::all_of(testData1m.begin(), testData1m.end(), isPositive);
    testResults.push_back(timer.Elapsed());
    
    timer.Reset();
    std::all_of(testData10m.begin(), testData10m.end(), isPositive);
    testResults.push_back(timer.Elapsed());

    // Output tests result
    PrintResult(testResults, "Block 1. Algorithm execution speed without execution policy:");
}

void Tests::TestExecutionPolicyBehaviour()
{
    std::cout << "Block 2. Algorithm execution speed with execution policy:" << std::endl;
    // Sequnced exec policy
    auto result = TestPolicy(std::execution::seq);
    PrintResult(result, "Sequenced policy (same as no policy):");

    // Unsequenced exec policy
    result = TestPolicy(std::execution::unseq);
    PrintResult(result, "Unsequenced policy:");

    // Parallel sequenced exec policy
    result = TestPolicy(std::execution::par);
    PrintResult(result, "Parallel sequenced policy:");

    // Parallel unsequenced exec policy
    result = TestPolicy(std::execution::par_unseq);
    PrintResult(result, "Parallel unsequenced policy:");
}

void Tests::TestCustomAlgorithm()
{
    auto isPositive = [](const auto &v) { return v > 0; };
    
    Timer timer;

    std::cout << "Block 3. Custom algorithm execution time: " << std::endl;
    
    for (int k=1; k<=256; k *= 2)
    {
        std::vector<float> testResults;

        // an empty test in order to overclock the CPU, otherwise the first test will always be slower
        std::all_of(testData1k.begin(), testData1k.end(), isPositive);
    
        timer.Reset();
        custom_algorithm::all_of(k, testData1k.begin(), testData1k.end(), isPositive);
        testResults.push_back(timer.Elapsed());

        timer.Reset();
        custom_algorithm::all_of(k, testData1m.begin(), testData1m.end(), isPositive);
        testResults.push_back(timer.Elapsed());

        timer.Reset();
        custom_algorithm::all_of(k, testData10m.begin(), testData10m.end(), isPositive);
        testResults.push_back(timer.Elapsed());

        PrintResult(testResults, "K = " + std::to_string(k));
    }
}

template <class ExPolicy>
std::vector<float> Tests::TestPolicy(ExPolicy policy)
{
    auto isPositive = [](const auto &v) { return v > 0; };
    
    Timer timer;
    std::vector<float> testResults;

    // an empty test in order to overclock the CPU, otherwise the first test will always be slower
    std::all_of(testData1k.begin(), testData1k.end(), isPositive);

    timer.Reset();
    std::all_of(policy, testData1k.begin(), testData1k.end(), isPositive);
    testResults.push_back(timer.Elapsed());
    
    timer.Reset();
    std::all_of(policy, testData1m.begin(), testData1m.end(), isPositive);
    testResults.push_back(timer.Elapsed());
    
    timer.Reset();
    std::all_of(policy, testData10m.begin(), testData10m.end(), isPositive);
    testResults.push_back(timer.Elapsed());

    return testResults;
}

void Tests::PrintResult(const std::vector<float>& testResults, const std::optional<std::string>& msg)
{
    if (msg)  std::cout << msg.value() << std::endl;
    std::cout << std::format("1k:\t{:.3f}ms", testResults[0]) << std::endl;
    std::cout << std::format("1m:\t{:.3f}ms", testResults[1])  << std::endl;
    std::cout << std::format("10m:\t{:.3f}ms", testResults[2])  << std::endl << std::endl;
}
