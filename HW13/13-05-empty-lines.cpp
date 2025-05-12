#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

// Проверяем, является ли строка пустой или пробельной
bool is_blank(const std::string& line)
{
    for (char c : line)
    {
        if (!std::isspace(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::string file_name;
    
    std::cout << "Введите имя файла (например, 13-05-test.txt из репозитория): ";
    std::getline(std::cin, file_name);
    
    // Открываем файл для чтения
    std::ifstream input_file(file_name);
    if (!input_file.is_open())
    {
        std::cerr << "Ошибка: не удалось открыть для чтения файл " << file_name << std::endl;
        return 1;
    }
    
    // Сохраняем !is_blank строки
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input_file, line))
    {
        if (!is_blank(line))
        {
            lines.push_back(line);
        }
    }
    input_file.close();
    
    // Перезаписываем файл без пустых/пробельных строк
    std::ofstream output_file(file_name, std::ios::trunc);
    if (!output_file.is_open())
    {
        std::cerr << "Ошибка: не удалось открыть для записи файл " << file_name << std::endl;
        return 1;
    }
    
    for (const auto& filtered_line : lines)
    {
        output_file << filtered_line << std::endl;
    }
    output_file.close();
    
    std::cout << "Пустые строки успешно удалены из файла " << file_name << std::endl;
    
    return 0;
}
