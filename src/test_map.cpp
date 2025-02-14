#include <iostream>

#include "map.h"
#include <map>

int main() {
  // Создаем объект Map
  binary_tree::map<int, std::string> myMap;

  // Вставляем элементы и проверяем возвращаемое значение
  auto result1 = myMap.insert(1, "one");
  std::cout << "Insert (1, \"one\"): "
            << (result1.second ? "Inserted" : "Not inserted") << std::endl;
  std::cout << "Iterator key: " << result1.first->key
            << ", value: " << result1.first->data << std::endl;
  std::cout << std::endl;

  auto result2 = myMap.insert(2, "two");
  std::cout << "Insert (2, \"two\"): "
            << (result2.second ? "Inserted" : "Not inserted") << std::endl;
  std::cout << "Iterator key: " << result2.first->key
            << ", value: " << result2.first->data << std::endl;
  std::cout << std::endl;

  auto result3 = myMap.insert(3, "three");
  std::cout << "Insert (3, \"three\"): "
            << (result3.second ? "Inserted" : "Not inserted") << std::endl;
  std::cout << "Iterator key: " << result3.first->key
            << ", value: " << result3.first->data << std::endl;
  std::cout << std::endl;

  // Проверяем наличие элементов
  std::cout << "Contains key 1: " << (myMap.contains(1) ? "Yes" : "No")
            << std::endl;
  std::cout << "Contains key 4: " << (myMap.contains(4) ? "Yes" : "No")
            << std::endl;

  // Проверяем наличие элементов
  std::cout << "Contains key 1: " << (myMap.contains(1) ? "Yes" : "No")
            << std::endl;
  std::cout << "Contains key 4: " << (myMap.contains(4) ? "Yes" : "No")
            << std::endl;
  std::cout << std::endl;

  // Доступ к элементам через at и operator[]
  try {
    std::cout << "Value at key 2: " << myMap.at(2) << std::endl;
    std::cout << "Value at key 3: " << myMap[3] << std::endl;
  } catch (const std::out_of_range &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  std::cout << std::endl;

  // Вставка или замена элемента
  myMap.insert_or_assign(2, "new_two");
  std::cout << "Value at key 2 after insert_or_assign: " << myMap.at(2)
            << std::endl;
  std::cout << std::endl;

  // Проверка оператора [] для несуществующего ключа
  std::cout << "Value at key 4 before assignment: " << myMap[4]
            << std::endl;  // Должно вывести пустую строку
  myMap[4] = "four";
  std::cout << "Value at key 4 after assignment: " << myMap[4] << std::endl;
  std::cout << std::endl;

  // Итерация по элементам
  std::cout << "Map contents:" << std::endl;
  for (auto it = myMap.begin(); it != myMap.end(); ++it) {
    std::cout << (*it).first << (*it).second << std::endl;
  }
  std::cout << std::endl;

  // Проверка операторов итераторов
  auto it1 = myMap.begin();
  auto it2 = myMap.begin();

  // Оператор ++ (префиксный)
  ++it1;
  std::cout << "After ++it1: " << (*it1).first << ": " << (*it1).second << std::endl;
  std::cout << std::endl;

  // Оператор ++ (постфиксный)
  it2++;
  std::cout << "After it2++: " << (*it2).first << ": " << (*it2).second << std::endl;
  std::cout << std::endl;

  // Оператор -- (префиксный)
  --it1;
  std::cout << "After --it1: " << (*it1).first << ": " << (*it1).second  << std::endl;
  std::cout << std::endl;

  // Оператор -- (постфиксный)
  it2--;
  std::cout << "After it2--: " << (*it2).first << ": " << (*it2).second << std::endl;
  std::cout << std::endl;

  // Оператор ==
  std::cout << "it1 == it2: " << (it1 == it2 ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Оператор !=
  ++it1;
  std::cout << "After ++it1: " << (*it1).first << ": " << (*it1).second  << std::endl;
  std::cout << "it1 != it2: " << (it1 != it2 ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Оператор >
  std::cout << "it1 > it2: " << (it1 > it2 ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Оператор <
  std::cout << "it1 < it2: " << (it1 < it2 ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Оператор *
  std::cout << "Dereference it1: " << (*it1).first << ": " << std::endl;
  std::cout << std::endl;

  // Оператор ->
  std::cout << "Arrow operator it1: " << it1->key << ": " << it1->data
            << std::endl;
  std::cout << std::endl;

  // Проверка размера и пустоты
  std::cout << "Map size: " << myMap.size() << std::endl;
  std::cout << "Is map empty? " << (myMap.empty() ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Проверка максимального размера
  std::cout << "Map max size: " << myMap.max_size() << std::endl;
  std::cout << std::endl;

  // распечатать дерево
  std::cout << "Map contents:" << std::endl;
  myMap.print_tree();
  myMap.insert(11, "eleven");
    std::cout << "Map contents:" << std::endl;
  myMap.print_tree();
  std::cout << std::endl;

  // Удаление элемента
  myMap.erase(myMap.begin());
  std::cout << "Map contents after erasing first element:" << std::endl;
  myMap.print_tree();
  std::cout << std::endl;

  // Создаем объект Map
  binary_tree::map<int, std::string> newMap = myMap;
  std::cout << "newMap contents:" << std::endl;
  newMap.print_tree();
  std::cout << std::endl;

  // изменим новое дерево
  newMap[1] = "ten";
  newMap[5] = "five";
  std::cout << "newMap contents:" << std::endl;
  newMap.print_tree();
  std::cout << std::endl;

  // проверка swap
  std::cout << "myMap and newMap after swap:" << std::endl;
  myMap.swap(newMap);
  std::cout << "newMap contents:" << std::endl;
  newMap.print_tree();
  std::cout << std::endl;
  std::cout << "myMap contents:" << std::endl;
  myMap.print_tree();
  std::cout << std::endl;

  // добавим элементы в новое дерево
  std::cout << "newMap after adding new elements:" << std::endl;
  newMap[-10] = "minus-ten";
  newMap[-5] = "minus_five";
  newMap[-3] = "minus_three";
  newMap.print_tree();
  std::cout << std::endl;

  // проверка merge
  std::cout << "myMap after merge thith newMap:" << std::endl;
  myMap.merge(newMap);
  myMap.print_tree();
  std::cout << std::endl;
  std::cout << "myMap contents:" << std::endl;
  for (auto it = myMap.begin(); it != myMap.end(); ++it) {
    std::cout << it->key << ": " << it->data << std::endl;
  }
  std::cout << std::endl;
  std::cout << "newMap after merge:" << std::endl;
  newMap.print_tree();
  std::cout << "newMap size: " << newMap.size() << std::endl;
  std::cout << "Is newMap empty after clear? "
            << (newMap.empty() ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  
    binary_tree::map<int, int> our_map = {{1, 2}, {3, 4}, {5, 6}};
    our_map.print_tree();
    std::cout << std::endl;
    std::map<int, int> std_map = {{1, 2}, {3, 4}, {5, 6}};
    binary_tree::map<int, int> our_map_copy = std::move(our_map);
    our_map_copy.print_tree();
    std::cout << std::endl;
    our_map.print_tree();
    std::cout << std::endl;
    std::map<int, int> std_map_copy = std::move(std_map);
    auto our_it = our_map_copy.begin();
    auto std_it = std_map_copy.begin();
    /*for (; our_it != our_map_copy.end(); ++our_it, ++std_it) {

      ((*our_it).first == (*std_it).first);
      ((*our_it).second == (*std_it).second);
    }*/
  

  // Очистка контейнера
  myMap.clear();
  std::cout << "myMap size after clear: " << myMap.size() << std::endl;
  std::cout << "Is meMap empty after clear? " << (myMap.empty() ? "Yes" : "No")
            << std::endl;

  return 0;
}
