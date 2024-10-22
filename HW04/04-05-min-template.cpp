#include <iostream>

// base template
template <typename T> [[nodiscard]] T inline min(T const a, T const b)
{
    return a < b ? a : b;
}
// variadic template
template <typename T1, typename... T> [[nodiscard]] inline T1 min(T1 a, T... args)
{
    return min(a, min(args...));
}


int main()
{
    int a1 = 3230, a2 = 879, a3 = 43456;
    std::cout << "integer test: min (" << a1 << ", " << a2 << ", " << a3 << ") = " << min(a1, a2, a3) << std::endl;

    double b1 = 3.2456, b2 = -87.293, b3 = -43.45, b4 = 0.1;
    std::cout << "double test: min (" << b1 << ", " << b2 << ", " << b3 << ", " << b4 << ") = " << min(b1, b2, b3, b4) << std::endl;
}