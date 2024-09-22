#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>

int main()
{
    std::cout << "Welcome to the factorizer for prime factors!" << std::endl;
    std::cout << "Enter one positive integer: "; uint64_t number{}; std::cin >> number;
    uint64_t iniNumber = number;

    std::vector<uint64_t> factors;

    uint64_t upperBound = std::sqrt(number);
    for (uint64_t i = 2; i <= upperBound; ++i)
    {
        while (number % i == 0)
        {
            factors.push_back(i);
            number /= i;
        }
    }

    if (number != 1)
    {
        factors.push_back(number);
    }

    std::cout << iniNumber << " = ";

    for (uint16_t factorIt = 0; factorIt < factors.size() - 1; ++factorIt)
    {
        std::cout << factors[factorIt] << " * ";
    }
    std::cout << factors[factors.size() - 1] << std::endl;

    return 0;
}
