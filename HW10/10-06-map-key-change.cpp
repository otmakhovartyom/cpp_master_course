#include <map>
#include <string>
#include <iostream>
#include <type_traits>

struct MutableKey
{
    mutable int id;  // mutable позволяет изменять поле даже в константном объекте
    std::string name;
    
    bool operator<(const MutableKey& other) const
    {
        return id < other.id;
    }
};

// Печать мапы
template<typename Map>
void printMap(const Map& map, const std::string& title)
{
    std::cout << "=== " << title << " ===" << std::endl;
    for (const auto& pair : map)
    {
        if constexpr (std::is_same_v<typename Map::key_type, int>)
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
        else
        {
            std::cout << "{" << pair.first.id << ", " << pair.first.name << "}: " << pair.second << std::endl;
        }
    }
}

int main()
{
    std::cout << "1. Опасный способ с const_cast" << std::endl;
    std::map<int, std::string> map1 = {{1, "one"}, {4, "four"}, {2, "two"}};
    printMap(map1, "map1 перед изменением");
    
    auto it1 = map1.find(2);
    if (it1 != map1.end())
    {
        int& key = const_cast<int&>(it1->first);
        key = 5;
        
        std::cout << "Изменили ключ 2 -> 5 через const_cast" << std::endl;
    }
    printMap(map1, "map1 после опасного изменения (порядок нарушен)");
    

    std::cout << std::endl << "2. Опасный способ с mutable в структуре ключа" << std::endl;
    std::map<MutableKey, int> map2 =
    {
        {{1, "first"}, 1},
        {{2, "second"}, 2},
        {{4, "fourth"}, 4}
    };
    printMap(map2, "map2 перед изменением mutable ключа");
    
    auto it2 = map2.begin();
    it2->first.id = 3;  // Изменяем mutable поле ключа
    std::cout << "Изменили mutable поле ключа {1,first} -> {3,first}" << std::endl;
    printMap(map2, "map2 после изменения mutable ключа (порядок нарушен)");
    

    std::cout << std::endl << "3. Безопасный способ - удаление и вставка с новым ключом" << std::endl;
    std::map<int, std::string> map3 = {{1, "one"}, {4, "four"}, {2, "two"}};
    printMap(map3, "Исходная map3 перед безопасным изменением ключа");
    
    auto it3 = map3.find(2);
    if (it3 != map3.end())
    {
        auto value = std::move(it3->second);
        map3.erase(it3);
        auto [new_it, inserted] = map3.emplace(5, std::move(value));
        
        std::cout << "Заменили ключ 2 -> 5 (erase+emplace)" << std::endl;
        if (inserted)
        {
            std::cout << "Новый элемент: " << new_it->first << ": " << new_it->second << std::endl;
        }
    }
    printMap(map3, "map3 после безопасного изменения (порядок правильный)");
    
    return 0;
}
