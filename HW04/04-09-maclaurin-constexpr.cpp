#include <iostream>
#include <iomanip>
#include <cstdint>
#define MAX_ITER 1000000000

constexpr double exp(double x, double epsilon)
{
    double nextElement = 1.0;
    double result = nextElement; 
    
    for (uint64_t i = 1; ((i < MAX_ITER) && (nextElement > epsilon)); i++)
    {
        nextElement *= x / i;
        result += nextElement;
    }

    return result;
}


int main()
{
    constexpr double exponent = exp(1.0, 1e-14);
    std::cout << std::setprecision(15) << "e = " << exponent << std::endl;
    return 0;
}