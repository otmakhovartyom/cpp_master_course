#include <iostream>

typedef void* (*SelfReturningFunc)();

// Посредник
static void* self_reference()
{
    return (void*)self_reference;
}

// Основная функция, которая возвращает указатель на посредника
SelfReturningFunc get_self_pointer()
{
    return (SelfReturningFunc)self_reference;
}

int main()
{
    SelfReturningFunc func = get_self_pointer();
    
    if ((void*)func == func())
    {
        std::cout << "Функция вернула указатель на саму себя" << std::endl;
    }
    else
    {
        std::cout << "Ошибка" << std::endl;
    }
    
    return 0;
}
