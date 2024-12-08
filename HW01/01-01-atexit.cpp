#include <iostream>

void print()
{
    std::cout << "specific print 4" << std::endl;
    return;
}

int specific = std::atexit(print);

int main()
{
    return 0;
}