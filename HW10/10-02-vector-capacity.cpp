#include <iostream>
#include <vector>
#include <stdexcept>

/*
Наблюдения:
1. Рост емкости без reserve:
   - Вектор начинает с емкости 0.
   - При добавлении первого элемента емкость становится 1.
   - Каждое перевыделение увеличивает емкость в 2 раза (теоретически может зависеть от компилятора, у меня используется g++).
   - В итоге наблюдается следующий рост емкости: 1 -> 2 -> 4 -> 8 -> 16 -> ...

2. Рост емкости с reserve(100):
   - После reserve(100) емкость сразу становится 100.
   - При добавлении 101-го элемента емкость увеличивается в 2 раза (до 200).
   - Дальнейший рост также происходит с коэффициентом x2.
   - В итоге наблюдается следующий рост емкости: 100 -> 200 -> 400 -> 800 -> ...

3. Попытка резервирования огромного объема памяти (1 триллион int ~ 4 ТБ):
   - Операционная система не может выделить столько памяти, и вектор бросает исключение std::bad_alloc.
   - Это показывает, что вектор корректно обрабатывает ошибки выделения памяти через механизм исключений.
*/

int main()
{
    std::cout << "Исследование роста емкости без reserve:" << std::endl;
    std::vector<int> vec;
    size_t prev_capacity = vec.capacity();
    std::cout << "Начальная емкость: " << prev_capacity << std::endl;
    for (int i = 0; i < 500; ++i)
    {
        vec.push_back(i);
        if (vec.capacity() != prev_capacity)
        {
            std::cout << "Элементов: " << i + 1 << ", емкость: " << vec.capacity() << std::endl;
            prev_capacity = vec.capacity();
        }
    }
    std::cout << std::endl;


    std::cout << "Исследование роста емкости с reserve(100):" << std::endl;
    std::vector<int> vec_reserved;
    vec_reserved.reserve(100);
    std::cout << "Емкость после reserve(100): " << vec_reserved.capacity() << std::endl;
    prev_capacity = vec_reserved.capacity();
    for (int i = 0; i < 500; ++i)
    {
        vec_reserved.push_back(i);
        if (vec_reserved.capacity() != prev_capacity)
        {
            std::cout << "Элементов: " << i + 1 << ", емкость: " << vec_reserved.capacity() << std::endl;
            prev_capacity = vec_reserved.capacity();
        }
    }
    std::cout << std::endl;


    std::cout << "Попытка резервирования огромного объема памяти (1 триллион элементов):" << std::endl;
    try
    {
        std::vector<int> vec_large;
        vec_large.reserve(1e12);
        std::cout << "Резервирование успешно" << std::endl;
    }
    catch (const std::bad_alloc& e)
    {
        std::cout << "Ошибка выделения памяти: " << e.what() << std::endl;
    }

    return 0;
}
