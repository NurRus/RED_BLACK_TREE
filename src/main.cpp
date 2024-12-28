#include "rb_tree.h"

using namespace rb_tree;

int main() {
  // Пример использования с простым типом данных
  RB_Tree<int> intTree;
  intTree.push(5);
  intTree.push(3);
  intTree.push(4);
  intTree.push(7);
  intTree.push(6);
  intTree.push(15);
  intTree.push(23);
  intTree.push(-2);
  // std::cout << "OK\n";

  intTree.print();

  Node<int> *N = intTree.find(20);
  if (N)
    std::cout << "\nfound: " << N->data << std::endl;
  else
    std::cout << "узла не существует" << std::endl;

  // Пример использования с dataMap
  RB_Tree<dataMap<int, std::string>> dataMapTree;
  dataMapTree.push({1, "one"});
  dataMapTree.push({3, "three"});
  dataMapTree.push({2, "two"});
  dataMapTree.push({5, "five"});
  dataMapTree.push({4, "four"});

  dataMapTree.print();

  Node<dataMap<int, std::string>> *M = dataMapTree.find({5});
  if (M)
    std::cout << "\nfound: " << M->data << std::endl;
  else
    std::cout << "узла не существует" << std::endl;

  return 0;
}
