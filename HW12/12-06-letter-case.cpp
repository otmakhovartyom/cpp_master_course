#include <cctype>
#include <string>
#include <iostream>

std::string capitalize_words(const std::string& text)
{
    if (text.empty())
    {
        return text;
    }

    std::string result;
    bool capitalize_next = true; // Флаг, отвечающий за начало слова

    for (char c : text)
    {
        if (isalpha(c))
        {
            if (capitalize_next)
            {
                result += toupper(c);
                capitalize_next = false;
            }
            else
            {
                result += tolower(c);
            }
        }
        else
        {
            result += c;
            capitalize_next = !isalnum(c);
        }
    }

    return result;
}

int main()
{
    std::string input_text;

    // Ввод пользователем
    std::cout << "Enter text: ";
    std::getline(std::cin, input_text);

    // Вывод результата
    std::cout << "Result: " << capitalize_words(input_text) << std::endl;

    return 0;
}
