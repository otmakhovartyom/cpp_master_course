#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

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
    // 1. std::count - подсчёт количества элементов с заданным значением
    std::cout << "=== std::count ===" << std::endl;
    std::vector<int> v1 = {1, 2, 3, 2, 4, 2, 5};
    print_vector(v1, "Исходный вектор");
    int count2 = std::count(v1.begin(), v1.end(), 2);
    std::cout << "Количество двоек в векторе: " << count2 << std::endl << std::endl;

    // 2. std::mismatch - нахождение первого расхождения между двумя последовательностями
    std::cout << "=== std::mismatch ===" << std::endl;
    std::vector<int> v2a = {1, 2, 3, 4, 5};
    std::vector<int> v2b = {1, 2, 4, 4, 5};
    print_vector(v2a, "Первая последовательность");
    print_vector(v2b, "Вторая последовательность");
    auto mismatch_pair = std::mismatch(v2a.begin(), v2a.end(), v2b.begin());
    if (mismatch_pair.first != v2a.end())
    {
        std::cout << "Первое несоответствие на позиции " 
                  << std::distance(v2a.begin(), mismatch_pair.first)
                  << ": " << *mismatch_pair.first << " != " << *mismatch_pair.second << std::endl;
    }
    else
    {
        std::cout << "Последовательности идентичны" << std::endl;
    }
    std::cout << std::endl;

    // 3. std::equal - проверка на равенство двух последовательностей
    std::cout << "=== std::equal ===" << std::endl;
    print_vector(v2a, "Первая последовательность");
    print_vector(v2b, "Вторая последовательность");
    bool is_equal = std::equal(v2a.begin(), v2a.end(), v2b.begin());
    std::cout << "Последовательности " << (is_equal ? "РАВНЫ" : "НЕ РАВНЫ") << std::endl << std::endl;

    // 4. std::search - поиск подпоследовательности
    std::cout << "=== std::search ===" << std::endl;
    std::vector<int> v4 = {1, 2, 3, 4, 5, 1, 2, 3};
    std::vector<int> sub = {1, 2, 3};
    print_vector(v4, "Основной вектор");
    print_vector(sub, "Искомая подпоследовательность");
    auto search_it = std::search(v4.begin(), v4.end(), sub.begin(), sub.end());
    if (search_it != v4.end())
    {
        std::cout << "Подпоследовательность найдена начиная с позиции " 
                  << std::distance(v4.begin(), search_it) << std::endl;
    }
    else
    {
        std::cout << "Подпоследовательность не найдена" << std::endl;
    }
    std::cout << std::endl;

    // 5. std::replace - замена всех вхождений одного значения на другое
    std::cout << "=== std::replace ===" << std::endl;
    std::vector<int> v5 = {1, 2, 3, 2, 4, 2, 5};
    print_vector(v5, "До замены");
    std::replace(v5.begin(), v5.end(), 2, 99);
    print_vector(v5, "После замены 2 на 99");
    std::cout << std::endl;

    // 6. std::remove - удаление элементов с заданным значением (без изменения размера)
    std::cout << "=== std::remove ===" << std::endl;
    std::vector<int> v6 = {1, 2, 3, 2, 4, 2, 5};
    print_vector(v6, "До удаления");
    auto new_end = std::remove(v6.begin(), v6.end(), 2);
    v6.erase(new_end, v6.end());
    print_vector(v6, "После remove(2) + erase");
    std::cout << std::endl;

    // 7. std::unique - удаление последовательных дубликатов
    std::cout << "=== std::unique ===" << std::endl;
    std::vector<int> v7 = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    print_vector(v7, "До удаления дубликатов");
    auto unique_end = std::unique(v7.begin(), v7.end());
    v7.erase(unique_end, v7.end());
    print_vector(v7, "После unique + erase");
    std::cout << std::endl;

    // 8. std::rotate - циклический сдвиг
    std::cout << "=== std::rotate ===" << std::endl;
    std::vector<int> v8 = {1, 2, 3, 4, 5};
    print_vector(v8, "До сдвига");
    std::rotate(v8.begin(), v8.begin() + 2, v8.end());
    print_vector(v8, "После сдвига влево на 2");
    std::cout << std::endl;

    // 9. std::partition - разделение элементов по условию
    std::cout << "=== std::partition ===" << std::endl;
    std::vector<int> v9 = {1, 5, 3, 8, 2, 7, 4};
    print_vector(v9, "До разделения");
    auto partition_it = std::partition(v9.begin(), v9.end(), [](int x) { return x < 5; });
    std::cout << "После разделения (x < 5):" << std::endl;
    std::cout << "Первая часть (<5): ";
    for (auto it = v9.begin(); it != partition_it; ++it) std::cout << *it << " ";
    std::cout << std::endl << "Вторая часть (>=5): ";
    for (auto it = partition_it; it != v9.end(); ++it) std::cout << *it << " ";
    std::cout << std::endl << std::endl;

    // 10. std::nth_element - частичная сортировка (n-й элемент на своём месте)
    std::cout << "=== std::nth_element ===" << std::endl;
    std::vector<int> v10 = {5, 3, 9, 1, 7, 2, 6, 8, 4};
    print_vector(v10, "До частичной сортировки");
    auto mid = v10.begin() + v10.size()/2;
    std::nth_element(v10.begin(), mid, v10.end());
    print_vector(v10, "После nth_element (nth - индекс посередине вектора)");
    std::cout << "Медиана: " << *mid << std::endl;

    return 0;
}
