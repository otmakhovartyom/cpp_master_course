#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <sstream>
#include <iomanip>

// Функция проверки корректности даты
bool is_valid_date(int day, int month, int year)
{
    if (year < 1 || month < 1 || month > 12 || day < 1)
    {
        return false;
    }

    static const std::map<int, int> days_in_month =
    {
        {1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31}, {6, 30},
        {7, 31}, {8, 31}, {9, 30}, {10, 31}, {11, 30}, {12, 31}
    };

    auto it = days_in_month.find(month);
    if (it == days_in_month.end())
    {
        return false;
    }

    return day <= it->second;
}

// Функция для преобразования даты в новый формат
std::string format_date(const std::string& day, const std::string& month, const std::string& year)
{
    int d, m, y;

    // попытка преобразования в числа
    try
    {
        d = std::stoi(day);
        m = std::stoi(month);
        y = std::stoi(year);
    }
    catch (...)
    {
        return "";
    }

    if (!is_valid_date(d, m, y))
    {
        return "";
    }

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << y << "-"
        << std::setw(2) << std::setfill('0') << m << "-"
        << std::setw(2) << std::setfill('0') << d;
    return oss.str();
}

// Функция замены дат в тексте
std::string replace_dates(const std::string& text)
{
    std::regex date_regex(R"((\b\d{1,2})(\/)(\d{1,2})(\/)(\d{4}\b))");
    std::smatch match;
    std::string result;
    std::string::const_iterator search_start(text.cbegin());

    while (std::regex_search(search_start, text.cend(), match, date_regex))
    {
        result += std::string(search_start, match[0].first);

        std::string day = match[1].str();
        std::string month = match[3].str();
        std::string year = match[5].str();

        std::string formatted_date = format_date(day, month, year);
        if (!formatted_date.empty())
        {
            result += formatted_date;
        }
        else
        {
            result += match[0].str();
        }

        search_start = match[0].second;
    }

    result += std::string(search_start, text.cend());
    return result;
}

// Функция для демонстрации примера работы
void show_demo()
{
    std::cout << "=== Демонстрация работы программы ===" << std::endl;
    std::string demo_text = "Даты: 05/12/2023, 31/12/2023 (корректные), 30/02/2023, 00/13/2025 (некорректные).";
    std::cout << "Исходный текст:" << std::endl << demo_text << std::endl;
    
    std::string converted_text = replace_dates(demo_text);
    std::cout << std::endl << "После преобразования:" << std::endl << converted_text << std::endl;
    std::cout << "=====================================" << std::endl << std::endl;
}

int main()
{
    show_demo();

    std::cout << "Теперь введите свой текст с датами в формате дд/мм/гггг:" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::string output = replace_dates(input);
    std::cout << std::endl << "Результат преобразования:" << std::endl << output << std::endl;

    return 0;
}
