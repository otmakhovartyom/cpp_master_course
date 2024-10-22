#include <iostream>
#include <cstdint>

template <uint64_t N> struct Fibonacci
{
  static constexpr uint64_t value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};
 
template <> struct Fibonacci<0>
{
  static constexpr uint64_t value = 0;
};
 
template <> struct Fibonacci<1>
{
  static constexpr uint64_t value = 1;
};

template <uint64_t N> constexpr uint64_t fibonacci_v = Fibonacci<N>::value;


int main()
{
  std::cout << "32nd Fibonacci number: " << fibonacci_v<32> << std::endl;
}