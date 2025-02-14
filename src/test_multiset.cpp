#include <iostream>
#include "s21_multiset.h"

int main() {
  // Создаем объект multiset
  binary_tree::multiset<int> ms;
  // Тестируем метод insert
  ms.insert(10);

  ms.insert(20);

  ms.insert(30);

  ms.insert(20);


  // Выводим содержимое multiset
  std::cout << "Multiset contents: ";
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  ms.print_tree();
  std::cout << std::endl;

  // Тестируем метод size
  std::cout << "Size: " << ms.size() << std::endl;

  // Тестируем метод empty
  std::cout << "Is empty: " << (ms.empty() ? "Yes" : "No") << std::endl;

  // Тестируем метод count
  std::cout << "Count of 20: " << ms.count(20) << std::endl;

  // Тестируем метод find
  auto it = ms.find(20);
  if (it != ms.end()) {
    std::cout << "Found: " << *it << std::endl;
  } else {
    std::cout << "Not found" << std::endl;
  }

  // Тестируем метод contains
  std::cout << "Contains 30: " << (ms.contains(30) ? "Yes" : "No") << std::endl;

  // Тестируем метод equal_range
  auto range = ms.equal_range(20);
  std::cout << "Equal range of 20: ";
  for (auto rit = range.first; rit != range.second; ++rit) {
    std::cout << *rit << " ";
  }
  std::cout << std::endl;

  // Тестируем метод lower_bound
  it = ms.lower_bound(20);
  std::cout << "Lower bound of 20: " << *it << std::endl;

  // Тестируем метод upper_bound
  it = ms.upper_bound(20);
  std::cout << "Upper bound of 20: " << *it << std::endl;

  // Тестируем метод erase
  ms.erase(ms.find(20));
  std::cout << "After erasing 20: ";
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // Тестируем метод clear
  ms.clear();
  std::cout << "After clear, size: " << ms.size() << std::endl;

  // Тестируем метод swap
  ms.print_tree();
  binary_tree::multiset<int> ms2 = {40, 50, 60};
  ms.swap(ms2);
  std::cout << "After swap, ms contents: ";
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // Тестируем метод merge
  binary_tree::multiset<int> ms3 = {70, 80, 90};
  std::cout << "initialize a new tree, ms3 contents: ";
  for (auto it = ms3.begin(); it != ms3.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  ms.merge(ms3);
  std::cout << "After merge ms и ms3, ms contents: ";
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "in the form of a balanced tree, ms contents: ";
  std::cout << std::endl;
  std::cout << std::endl;
  ms.print_tree();
  std::cout << std::endl;
  std::cout << "insert a new value 100";
  ms.insert(100);
  std::cout << std::endl;
  std::cout << "in the form of a balanced tree, ms contents: ";
  std::cout << std::endl;
  std::cout << std::endl;
  ms.print_tree();
  std::cout << std::endl;


  return 0;
}
