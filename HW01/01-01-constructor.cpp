#include <iostream>

class Print
{
public:
    Print()
    {
        std::cout << "specific print 1" << std::endl;
    }
};

Print specific;

int main()
{
    return 0;
}
