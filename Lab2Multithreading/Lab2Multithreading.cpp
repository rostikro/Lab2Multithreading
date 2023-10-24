#include "Tests.h"

int main(int argc, char* argv[])
{
    Tests tests(1);
    
    tests.TestDefaultBehaviour();
    tests.TestExecutionPolicyBehaviour();
    tests.TestCustomAlgorithm();
    
    return 0;
}
