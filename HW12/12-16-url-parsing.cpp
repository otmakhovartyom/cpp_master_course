#include <iostream>
#include <string>
#include <regex>

void parse_url(const std::string& url)
{
    // Регулярное выражение для разбора URL
    std::regex url_regex(
        R"REGEX(^([a-zA-Z]+)://)REGEX"  // Протокол (группа 1)
        R"REGEX(([^:/?#]+))REGEX"       // Домен (группа 2)
        R"REGEX(:?([0-9]*))REGEX"       // Порт (группа 3, необязательный)
        R"REGEX((/?[^?#]*))REGEX"       // Путь (группа 4)
        R"REGEX(\??([^#]*))REGEX"       // Запрос (группа 5, необязательный)
        R"REGEX(#?(.*))REGEX"           // Фрагмент (группа 6, необязательный)
    );
    
    std::smatch url_match;
    
    if (std::regex_match(url, url_match, url_regex))
    {
        std::cout << "Полный URL: " << url_match[0] << std::endl;

        std::cout << "Протокол: " << url_match[1] << std::endl;
        
        std::cout << "Домен: " << url_match[2] << std::endl;
        
        if (!url_match[3].str().empty())
        {
            std::cout << "Порт: " << url_match[3] << std::endl;
        }
        else
        {
            std::cout << "Порт: (по умолчанию)" << std::endl;
        }
        
        std::cout << "Путь: " << (url_match[4].str().empty() ? "/" : url_match[4].str()) << std::endl;
        
        if (!url_match[5].str().empty())
        {
            std::cout << "Запрос: " << url_match[5] << std::endl;
        }
        
        if (!url_match[6].str().empty())
        {
            std::cout << "Фрагмент: " << url_match[6] << std::endl;
        }
    }

    else
    {
        std::cerr << "Неверный формат URL" << std::endl;
    }
}

int main()
{
    std::string url;
    std::cout << "Введите URL для разбора: ";
    std::getline(std::cin, url);
    
    parse_url(url);
    
    return 0;
}
