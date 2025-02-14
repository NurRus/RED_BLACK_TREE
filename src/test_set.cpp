#include <iostream>

#include "set.h"
#include <set>

int main() {
  
  // Создаем объект Set
  binary_tree::set<int> mySet;
  
  mySet.insert(1);
  mySet.print_tree();

  // Вставляем элементы и проверяем возвращаемое значение
  auto result1 = mySet.insert(1);
  std::cout << "Insert 1: " << (result1.second ? "Inserted" : "Not inserted") << std::endl;
  std::cout << "Iterator value: " << *result1.first << std::endl;
  std::cout << std::endl;

  auto result2 = mySet.insert(2);
  std::cout << "Insert 2: " << (result2.second ? "Inserted" : "Not inserted") << std::endl;
  std::cout << "Iterator value: " << *result2.first << std::endl;
  std::cout << std::endl;

  auto result3 = mySet.insert(3);
  std::cout << "Insert 3: " << (result3.second ? "Inserted" : "Not inserted") << std::endl;
  std::cout << "Iterator value: " << *result3.first << std::endl;
  std::cout << std::endl;

  // Проверяем наличие элементов
  std::cout << "Contains 1: " << (mySet.contains(1) ? "Yes" : "No") << std::endl;
  std::cout << "Contains 4: " << (!mySet.contains(4)  ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Итерация по элементам
  std::cout << "Set contents:" << std::endl;
  for (auto it = mySet.begin(); it != mySet.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;

  // Проверка операторов итераторов
  auto it1 = mySet.begin();
  auto it2 = mySet.begin();

  // Оператор ++ (префиксный)
  ++it1;
  std::cout << "After ++it1: " << *it1 << std::endl;
  std::cout << std::endl;

  // Оператор ++ (постфиксный)
  it2++;
  std::cout << "After it2++: " << *it2 << std::endl;
  std::cout << std::endl;

  // Оператор -- (префиксный)
  --it1;
  std::cout << "After --it1: " << *it1 << std::endl;
  std::cout << std::endl;

  // Оператор -- (постфиксный)
  it2--;
  std::cout << "After it2--: " << *it2 << std::endl;
  std::cout << std::endl;

  // Оператор ==
  std::cout << "it1 == it2: " << (it1 == it2 ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Оператор !=
  ++it1;
  std::cout << "After ++it1: " << *it1 << std::endl;
  std::cout << "it1 != it2: " << (it1 != it2 ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Оператор *
  std::cout << "Dereference it1: " << *it1 << std::endl;
  std::cout << std::endl;

  // Проверка размера и пустоты
  std::cout << "Set size: " << mySet.size() << std::endl;
  std::cout << "Is set empty? " << (mySet.empty() ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Проверка максимального размера
  std::cout << "Set max size: " << mySet.max_size() << std::endl;
  std::cout << std::endl;

  // распечатать дерево
  std::cout << "Set contents:" << std::endl;
  mySet.print_tree();
  std::cout << std::endl;

  // Удаление элемента
  mySet.erase(mySet.begin());
  std::cout << "Set contents after erasing first element:" << std::endl;
  mySet.print_tree();
  std::cout << std::endl;

  // Создаем объект Set
  binary_tree::set<int> newSet = mySet;
  std::cout << "newSet contents:" << std::endl;
  newSet.print_tree();
  std::cout << std::endl;

  // изменим новое дерево
  newSet.insert(1);
  newSet.insert(5);
  std::cout << "newSet contents:" << std::endl;
  newSet.print_tree();
  std::cout << std::endl;

  // проверка swap
  std::cout << "mySet and newSet after swap:" << std::endl;
  mySet.swap(newSet);
  std::cout << "newSet contents:" << std::endl;
  newSet.print_tree();
  std::cout << std::endl;
  std::cout << "mySet contents:" << std::endl;
  mySet.print_tree();
  std::cout << std::endl;

  // добавим элементы в новое дерево
  std::cout << "newSet after adding new elements:" << std::endl;
  newSet.insert(-10);
  newSet.insert(-5);
  newSet.insert(-3);
  newSet.print_tree();
  std::cout << std::endl;

  // проверка merge
  std::cout << "mySet after merge with newSet:" << std::endl;
  mySet.merge(newSet);
  mySet.print_tree();
  std::cout << std::endl;
  std::cout << "mySet contents:" << std::endl;
  for (auto it = mySet.begin(); it != mySet.end(); ++it) {
    std::cout << *it << std::endl;
  }
  std::cout << std::endl;
  std::cout << "newSet after merge:" << std::endl;
  newSet.print_tree();
  std::cout << "newSet size: " << newSet.size() << std::endl;
  std::cout << "Is newSet empty after clear? " << (newSet.empty() ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  // Очистка контейнера
  mySet.clear();
  std::cout << "mySet size after clear: " << mySet.size() << std::endl;
  std::cout << "Is mySet empty after clear? " << (mySet.empty() ? "Yes" : "No") << std::endl;
  std::cout << std::endl;

  { 
  binary_tree::set<std::string> our_set = {"This", "our", "is", "set"};
   std::set<std::string> std_set = {"This", "our", "is", "set"};
   our_set.print_tree();
   std:: cout << std::endl;
   auto our_it = our_set.begin();
   auto std_it = std_set.begin();
   std:: cout << *our_it << " : " << *std_it << std::endl;
   our_it = our_set.end();
   std_it = std_set.end();
   --our_it;
   --std_it;
   std:: cout << *our_it << " : " << *std_it << std::endl;
   std:: cout << std::endl;
  }
 {
   binary_tree::set<int> our_set = {1, 2, 3, 4, 5};
   std::set<int> std_set = {1, 2, 3, 4, 5};
   binary_tree::set<int> our_set_copy = our_set;
   std::set<int> std_set_copy = std_set;
   auto our_it = our_set_copy.begin();
   auto std_it = std_set_copy.begin();
   for (; our_it != our_set_copy.end(); ++our_it, ++std_it) {
    std::cout << *our_it << " == " << *std_it << std::endl;
   }
   std:: cout << std::endl;
 }

 {
   binary_tree::set<int> our_set = {1};
   binary_tree::set<int> our_merge_set = {3, 4, 5};
   our_set.print_tree();
   std:: cout << std::endl;
   our_merge_set.print_tree();
   std:: cout << std::endl;
   our_set.merge(our_merge_set);
   our_set.print_tree();
   std:: cout << std::endl;
  
   std:: cout << our_set.size()<< std::endl;
   
   
   std:: cout << std::endl;

 }

  //mySet.clear();
  return 0;
}
