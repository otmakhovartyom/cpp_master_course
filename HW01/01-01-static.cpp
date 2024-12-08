#include <iostream>

int print()
{
    std::cout << "specific print 2" << std::endl;
    return 0;
}

int specific = print();

int main()
{
    return 0;
}
