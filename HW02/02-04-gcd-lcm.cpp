#include <iostream>
#include <cstdint>
#include <numeric>

uint64_t gcdRecursive (uint64_t a, uint64_t b)
{
    return b ? gcdRecursive (b, a % b) : a;
}

uint64_t gcdNonRecursive (uint64_t a, uint64_t b)
{
    while (b)
    {
        a %= b;
        std::swap(a, b);
    }

    return a;
}

uint64_t lcm (uint64_t a, uint64_t b)
{
    return a / gcdNonRecursive (a, b) * b;
}


int main()
{
    std::cout << "This program finds the greatest common divisor (GCD) and the least common multiple (LCM) for two numbers" << std::endl;
    std::cout << "Enter two positive integers: "; uint64_t a{}, b{}; std::cin >> a >> b;
    std::cout << std::endl;

    std::cout << "The GCD found using Euclid's recursive algorithm: " << gcdRecursive (a, b) << std::endl;
    std::cout << "The GCD found using Euclid's non-recursive algorithm: " << gcdNonRecursive (a, b) << std::endl;
    std::cout << "The GCD found using std::gcd: " << std::gcd(a, b) << std::endl;

    std::cout << "The LCM found using Euclid's non-recursive algorithm and the mathematical relationship between GCD and LCM: " << lcm (a, b) << std::endl;
    std::cout << "The LCM found using std::lcm: " << std::lcm(a, b) << std::endl;

    return 0;
}
