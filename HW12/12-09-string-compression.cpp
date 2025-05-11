#include <iostream>
#include <string>
#include <sstream>

std::string compress_string(const std::string& input)
{
    if (input.empty())
    {
        return "";
    }

    std::ostringstream compressed;
    char current_char = input[0];
    int count = 1;

    for (size_t i = 1; i < input.size(); ++i)
    {
        if (input[i] == current_char)
        {
            ++count;
        }
        else
        {
            compressed << current_char;
            if (count > 1)
            {
                compressed << count;
            }
            current_char = input[i];
            count = 1;
        }
    }

    compressed << current_char;
    if (count > 1)
    {
        compressed << count;
    }

    return compressed.str();
}

int main()
{
    std::string user_input;
    
    std::cout << "Алгоритм сжатия строк (aaabbbccc -> a3b3c3)" << std::endl;
    std::cout << "Введите строку (только латинские буквы): ";
    std::getline(std::cin, user_input);

    for (char c : user_input)
    {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        {
            std::cout << "Ошибка: строка должна содержать только латинские буквы." << std::endl;
            return 1;
        }
    }

    std::string compressed = compress_string(user_input);
    std::cout << "Исходная строка: " << user_input << std::endl;
    std::cout << "Сжатая строка: " << compressed << std::endl;

    return 0;
}
