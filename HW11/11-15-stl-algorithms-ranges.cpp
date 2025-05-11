#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>

void print_vector(const std::vector<int>& v, const std::string& message = "")
{
    if (!message.empty())
    {
        std::cout << message << ": ";
    }
    for (int x : v)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // 1. std::ranges::count - подсчёт количества элементов с заданным значением
    std::cout << "=== std::ranges::count ===" << std::endl;
    std::vector<int> v1 = {1, 2, 3, 2, 4, 2, 5};
    print_vector(v1, "Исходный вектор");
    int count2 = std::ranges::count(v1, 2);
    std::cout << "Количество двоек в векторе: " << count2 << std::endl << std::endl;

    // 2. std::ranges::mismatch - нахождение первого расхождения между двумя последовательностями
    std::cout << "=== std::ranges::mismatch ===" << std::endl;
    std::vector<int> v2a = {1, 2, 3, 4, 5};
    std::vector<int> v2b = {1, 2, 4, 4, 5};
    print_vector(v2a, "Первая последовательность");
    print_vector(v2b, "Вторая последовательность");
    auto mismatch_pair = std::ranges::mismatch(v2a, v2b);
    if (mismatch_pair.in1 != v2a.end())
    {
        std::cout << "Первое несоответствие на позиции " 
                  << std::distance(v2a.begin(), mismatch_pair.in1)
                  << ": " << *mismatch_pair.in1 << " != " << *mismatch_pair.in2 << std::endl;
    }
    else
    {
        std::cout << "Последовательности идентичны" << std::endl;
    }
    std::cout << std::endl;

    // 3. std::ranges::equal - проверка на равенство двух последовательностей
    std::cout << "=== std::ranges::equal ===" << std::endl;
    print_vector(v2a, "Первая последовательность");
    print_vector(v2b, "Вторая последовательность");
    bool is_equal = std::ranges::equal(v2a, v2b);
    std::cout << "Последовательности " << (is_equal ? "РАВНЫ" : "НЕ РАВНЫ") << std::endl << std::endl;

    // 4. std::ranges::search - поиск подпоследовательности
    std::cout << "=== std::ranges::search ===" << std::endl;
    std::vector<int> v4 = {1, 2, 3, 4, 5, 1, 2, 3};
    std::vector<int> sub = {1, 2, 3};
    print_vector(v4, "Основной вектор");
    print_vector(sub, "Искомая подпоследовательность");
    auto search_result = std::ranges::search(v4, sub);
    if (!search_result.empty())
    {
        std::cout << "Подпоследовательность найдена начиная с позиции " 
                  << std::distance(v4.begin(), search_result.begin()) << std::endl;
    }
    else
    {
        std::cout << "Подпоследовательность не найдена" << std::endl;
    }
    std::cout << std::endl;

    // 5. std::ranges::replace - замена всех вхождений одного значения на другое
    std::cout << "=== std::ranges::replace ===" << std::endl;
    std::vector<int> v5 = {1, 2, 3, 2, 4, 2, 5};
    print_vector(v5, "До замены");
    std::ranges::replace(v5, 2, 99);
    print_vector(v5, "После замены 2 на 99");
    std::cout << std::endl;

    // 6. std::ranges::remove - удаление элементов с заданным значением
    std::cout << "=== std::ranges::remove ===" << std::endl;
    std::vector<int> v6 = {1, 2, 3, 2, 4, 2, 5};
    print_vector(v6, "До удаления");
    auto [new_begin, new_end] = std::ranges::remove(v6, 2);
    v6.erase(new_begin, new_end);
    print_vector(v6, "После remove(2) + erase");
    std::cout << std::endl;

    // 7. std::ranges::unique - удаление последовательных дубликатов
    std::cout << "=== std::ranges::unique ===" << std::endl;
    std::vector<int> v7 = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    print_vector(v7, "До удаления дубликатов");
    auto [unique_begin, unique_end] = std::ranges::unique(v7);
    v7.erase(unique_begin, unique_end);
    print_vector(v7, "После unique + erase");
    std::cout << std::endl;

    // 8. std::ranges::rotate - циклический сдвиг
    std::cout << "=== std::ranges::rotate ===" << std::endl;
    std::vector<int> v8 = {1, 2, 3, 4, 5};
    print_vector(v8, "До сдвига");
    std::ranges::rotate(v8, v8.begin() + 2);
    print_vector(v8, "После сдвига влево на 2");
    std::cout << std::endl;

    // 9. std::ranges::partition - разделение элементов по условию
    std::cout << "=== std::ranges::partition ===" << std::endl;
    std::vector<int> v9 = {1, 5, 3, 8, 2, 7, 4};
    print_vector(v9, "До разделения");
    std::ranges::partition(v9, [](int x) { return x < 5; });
    auto partition_point = std::ranges::partition_point(v9, [](int x) { return x < 5; });
    std::cout << "После разделения (x < 5):" << std::endl;
    std::cout << "Первая часть (<5): ";
    for (auto it = v9.begin(); it != partition_point; ++it) std::cout << *it << " ";
    std::cout << std::endl << "Вторая часть (>=5): ";
    for (auto it = partition_point; it != v9.end(); ++it) std::cout << *it << " ";
    std::cout << std::endl << std::endl;

    // 10. std::ranges::nth_element - частичная сортировка
    std::cout << "=== std::ranges::nth_element ===" << std::endl;
    std::vector<int> v10 = {5, 3, 9, 1, 7, 2, 6, 8, 4};
    print_vector(v10, "До частичной сортировки");
    auto mid = v10.begin() + v10.size()/2;
    std::ranges::nth_element(v10, mid);
    print_vector(v10, "После nth_element (nth - индекс посередине вектора)");
    std::cout << "Медиана: " << *mid << std::endl;

    return 0;
}
