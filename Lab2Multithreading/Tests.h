#pragma once
#include <optional>
#include <string>
#include <vector>

class Tests
{
public:
    Tests(int init);
    void TestDefaultBehaviour();
    
    void TestExecutionPolicyBehaviour();

    void TestCustomAlgorithm();

private:
    template <class ExPolicy>
    std::vector<float> TestPolicy(ExPolicy policy = nullptr);

    void PrintResult(const std::vector<float> &testResults, const std::optional<std::string> &msg = {});

private:
    std::vector<int> testData1k;
    std::vector<int> testData1m;
    std::vector<int> testData10m;
};
