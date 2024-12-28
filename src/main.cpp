#include "rb_tree.h"

using namespace rb_tree;

int main() {
  // Пример использования с простым типом данных
  RB_Tree<int> intTree;
  intTree.push(25);
  intTree.push(30);
  intTree.push(8);
  intTree.push(12);
  intTree.push(10);
  intTree.push(13);
  intTree.push(15);
  intTree.push(9);
  intTree.push(11);
  intTree.push(6);
  intTree.push(7);
  intTree.push(5);

  intTree.print();
  std::cout << std::endl;

  intTree.remove(8);

  intTree.print();
  std::cout << std::endl;

  intTree.remove(25);

  intTree.print();

  Node<int> *N = intTree.find(-2);
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
