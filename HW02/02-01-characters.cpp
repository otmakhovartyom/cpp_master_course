#include <iostream>

int main()
{
    std::cout << "Welcome to the character classifier! The following types are supported: digits, arithmetic operators, round parentheses, other characters." << std::endl;
    std::cout << "Enter one character: "; unsigned char symb{}; std::cin >> symb;
    std::cout << "Character type: ";

    switch (symb)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        {
            std::cout << "arithmetic operators"; break;
        }

        case '(':
        case ')':
        {
            std::cout << "round parentheses"; break;
        }

        default:
        {
            if (std::isdigit (symb))
            {
                std::cout << "digits" << ' '; break;
            }

            std::cout << "other characters"; break;
        }
    }

    std::cout << std::endl;

    return 0;
}
