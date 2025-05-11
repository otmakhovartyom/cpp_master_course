#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Функция для объединения строк с разделителем
std::string join(const std::vector<std::string>& strings, const std::string& delimiter)
{
    if (strings.empty())
    {
        return "";
    }

    std::ostringstream oss;
    auto it = strings.begin();
    
    oss << *it;  // Первый элемент без разделителя
    ++it;

    for (; it != strings.end(); ++it)
    {
        oss << delimiter << *it;  // Остальные элементы с разделителем
    }

    return oss.str();
}

int main()
{
    std::vector<std::string> words;
    std::string input, delimiter;
    int count;

    std::cout << "Введите количество строк: ";
    std::cin >> count;
    std::cin.ignore();

    for (int i = 0; i < count; ++i)
    {
        std::cout << "Введите строку #" << i + 1 << ": ";
        std::getline(std::cin, input);
        words.push_back(input);
    }

    std::cout << "Введите разделитель: ";
    std::getline(std::cin, delimiter);

    std::string result = join(words, delimiter);
    std::cout << std::endl << "Результат конкатенации:" << std::endl << result << std::endl;

    return 0;
}
