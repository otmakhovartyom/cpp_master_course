#include <iostream>
#include <string>
#include <regex>
#include <vector>

int main()
{
    // Сырая строка с примерами email
    std::string text = R"(
        Вот несколько email-адресов для теста:
        - valid.email@example.com
        - another.valid-email@sub.domain.com
        - invalid.email@.com
        - no@tld
        - @missingusername.com
        - spaces in@email.com
        - user@server-with-hyphen.com
        - user.name+tag@domain.org
        - 123456@numbers.com
        - "quoted"@email.com
        - invalid@.missing-tld
        - missing-at-sign.com
        - just@a..double..dot
        - a..double..dot@example.com
        - localhost@
        - @
        Это текст, который не должен быть распознан как email.
        Проверяем на отсутствие email в конце текста.
    )";

    // Регулярное выражение для валидации email (немного доработал взятое с форума, но не стал сильно упарываться):
    // 1. Локальная часть: [A-Za-z0-9._%+-]+
    // 2. Обязательный символ @
    // 3. Доменная часть:
    //    - Не начинается с точки (?!\.)
    //    - Поддомены: [A-Za-z0-9-]+\. (минимум один поддомен с точкой)
    //    - Домен верхнего уровня: [A-Za-z]{2,} (минимум 2 буквы)
    std::regex email_regex(
        R"(\b[A-Za-z0-9._%+-]+@(?!\.)(?:[A-Za-z0-9-]+\.)+[A-Za-z]{2,}\b)"
    );

    // Поиск всех соответствий в тексте
    std::vector<std::string> emails;
    std::smatch matches;
    std::string::const_iterator search_start(text.cbegin());

    while (std::regex_search(search_start, text.cend(), matches, email_regex))
    {
        emails.push_back(matches[0]);
        search_start = matches[0].second;
    }

    // Вывод результатов
    std::cout << "Найдены корректные email-адреса:" << std::endl;
    for (const auto& email : emails)
    {
        std::cout << "- " << email << std::endl;
    }

    return 0;
}
