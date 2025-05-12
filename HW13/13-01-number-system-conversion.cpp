#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <limits>

// Функция преобразования вектора байт в HEX-строку
std::string bytes_to_hex_string(const std::vector<uint8_t>& bytes)
{
    std::ostringstream oss; // строковый поток вывода
    oss << std::hex << std::uppercase << std::setfill('0');  // настройка манипуляторов потоков
    
    for (uint8_t byte : bytes)
    {
        oss << std::setw(2) << static_cast<int>(byte);
    }
    
    return oss.str();
}

int main()
{
    std::vector<uint8_t> predefined_data = {0xBA, 0xAD, 0xF0, 0x0D};
    std::string predefined_hex = bytes_to_hex_string(predefined_data);
    std::cout << "Пример работы:" << std::endl;
    std::cout << "Входные данные: {0xBA, 0xAD, 0xF0, 0x0D}" << std::endl;
    std::cout << "HEX-строка: " << predefined_hex << std::endl;


    std::cout << std::endl << "Введите количество 8-битных чисел в коллекции: ";
    size_t count;
    std::cin >> count;

    std::vector<uint8_t> user_data;
    std::cout << "Введите " << count << " чисел в HEX-формате (например, 0xBA):" << std::endl;;
    
    for (size_t i = 0; i < count;)
    {
        unsigned int num;
        std::cin >> std::hex >> num;
        
        // Проверка на ошибку ввода
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: некорректный HEX-формат. Повторите ввод: ";
            continue;
        }
        
        // Проверка на 8-битность
        if (num > 0xFF)
        {
            std::cout << "Ошибка: число должно быть 8-битным (0x00..0xFF). Повторите ввод: ";
            continue;
        }
        
        user_data.push_back(static_cast<uint8_t>(num));
        i++;
    }

    if (!user_data.empty())
    {
        std::string user_hex = bytes_to_hex_string(user_data);
        std::cout << "Результат: " << user_hex << std::endl;
    }
    else
    {
        std::cout << "Не было введено корректных данных." << std::endl;
    }

    return 0;
}
