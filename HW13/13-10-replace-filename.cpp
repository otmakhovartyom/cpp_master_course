#include <iostream>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <string>

// Функция для преобразования строки в snake_case
std::string to_snake_case(const std::string& str)
{
    std::string result;
    bool prev_upper = false;

    for (size_t i = 0; i < str.size(); ++i)
    {
        char c = str[i];
        
        // Замена пробелов и дефисов на нижние подчеркивания
        if (c == ' ' || c == '-')
        {
            result += '_';
            prev_upper = false;
            continue;
        }
        
        // Обработка верхнего регистра
        if (isupper(c))
        {
            if (!result.empty() && !prev_upper)
            {
                result += '_';
            }
            result += tolower(c);
            prev_upper = true;
        }
        else
        {
            result += c;
            prev_upper = false;
        }
    }
    
    // Удаление двойных подчеркиваний
    std::string final_result;
    for (size_t i = 0; i < result.size(); ++i)
    {
        if (i > 0 && result[i] == '_' && result[i-1] == '_') continue;
        final_result += result[i];
    }
    
    return final_result;
}

// Функция для переименования файлов в директории
void rename_files_in_directory(const std::filesystem::path& directory)
{
    try
    {
        if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
        {
            std::cerr << "Ошибка: " << directory << " не является допустимой директорией." << std::endl;
            return;
        }

        std::cout << std::endl << "Найденные файлы в директории '" << directory << "':" << std::endl;
        
        // Вывод список файлов для подтверждения операции
        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.is_regular_file())
            {
                std::cout << "  " << entry.path().filename() << std::endl;
            }
        }

        std::cout << std::endl << "Вы уверены, что хотите переименовать эти файлы в snake_case? (y/n): ";
        char answer;
        std::cin >> answer;
        std::cin.ignore();
        
        if (tolower(answer) != 'y')
        {
            std::cout << "Операция отменена." << std::endl;
            return;
        }

        // Переименование
        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.is_regular_file())
            {
                std::filesystem::path old_path = entry.path();
                std::string new_filename = to_snake_case(old_path.stem().string()) + old_path.extension().string();
                
                // Создание нового пути с заменой имени файла через replace_filename
                std::filesystem::path new_path = old_path;
                new_path.replace_filename(new_filename);

                if (new_path != old_path)
                {
                    try
                    {
                        std::filesystem::rename(old_path, new_path);
                        std::cout << "  " << old_path.filename() << " -> " << new_path.filename() << std::endl;
                    }
                    catch (const std::filesystem::filesystem_error& e)
                    {
                        std::cerr << "Ошибка при переименовании " << old_path << ": " << e.what() << std::endl;
                    }
                }
            }
        }
        
        std::cout << "Готово! Файлы переименованы в snake_case." << std::endl;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Ошибка файловой системы: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Программа для переименования файлов в директории (без рекурсии): приведение к виду snake_case" << std::endl;
    std::cout << "Пример преобразования: 'Test Document-v0.txt' -> 'test_document_v0.txt'" << std::endl << std::endl;
    std::cout << "Введите путь к директории (например, 13-10-test-dir/ из репозитория): ";
    
    std::string path_str;
    std::getline(std::cin, path_str);
    
    std::filesystem::path directory(path_str);
    rename_files_in_directory(directory);

    return 0;
}
