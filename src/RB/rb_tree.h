#ifndef RB_BIN_TREE_RB_TREE_H
#define RB_BIN_TREE_RB_TREE_H

#include <iostream>
#include <initializer_list>
#include <limits>
#include <type_traits>
/*Библиотека <type_traits> предоставляет набор шаблонов и типов, которые 
позволяют выполнять запросы о свойствах типов во время компиляции. 
Это особенно полезно для метапрограммирования и SFINAE (Substitution Failure 
Is Not An Error), что позволяет создавать более гибкие и универсальные шаблоны.
В вашем случае <type_traits> используется для реализации SFINAE, чтобы различать 
случаи, когда тип T является простым типом или структурой с ключом. 
Это позволяет вам определить, какой метод at или operator[] следует использовать 
в зависимости от типа T.
Вот как это работает:
SFINAE (Substitution Failure Is Not An Error): Это принцип, который позволяет 
компилятору игнорировать ошибки подстановки шаблонов, если есть другие варианты, 
которые могут быть использованы. Это позволяет вам создавать специализированные 
версии шаблонов для различных типов.
std::enable_if_t: Это утилита из <type_traits>, которая позволяет включать или 
исключать шаблоны в зависимости от условия. В вашем случае она используется для 
включения методов at и operator[] только для тех типов, которые удовлетворяют 
определенным условиям.
std::is_same_v: Это утилита из <type_traits>, которая проверяет, являются ли два 
типа одинаковыми. В вашем случае она используется для проверки, является ли тип T 
простым типом или структурой с ключом.*/

namespace rb_tree {

enum COLOR { RED, BLACK };

template <typename T1, typename T2>
struct dataMap {
  T1 key;
  T2 data;
  // Операторы сравнения для dataMap
  bool operator<(const dataMap<T1, T2> &other) const { return key < other.key; }
  bool operator>(const dataMap<T1, T2> &other) const { return key > other.key; }
  bool operator==(const dataMap<T1, T2> &other) const {
    return key == other.key;
  }
  bool operator!=(const dataMap<T1, T2> &other) const {
    return key != other.key;
  }
  // Перегрузка оператора вывода для dataMap
  friend std::ostream &operator<<(std::ostream &os, const dataMap<T1, T2> &dm) {
    os << "Key: " << dm.key << ", Data: " << dm.data;
    return os;
  }
};

template <typename T>
struct Node {
  T data;
  Node *left = nullptr, *right = nullptr, *parent = nullptr;
  COLOR nodeColor = RED;

  // Конструктор для простых типов данных
  Node(const T &data) : data(data) {}
};

template <typename T1, typename T2>
struct Node<dataMap<T1, T2>> {
  dataMap<T1, T2> data;
  Node *left = nullptr, *right = nullptr, *parent = nullptr;
  COLOR nodeColor = RED;
  // Конструктор для dataMap
  Node(const dataMap<T1, T2> &data) : data(data) {}
};

template <typename T>
class RB_Tree {
 private:
  Node<T> *root = nullptr;
  size_t tree_size = 0;
  
  Node<T> *grandfather(Node<T> *ptr);
  Node<T> *uncle(Node<T> *ptr);
  void rotateRight(Node<T> *ptr);
  void rotateLeft(Node<T> *ptr);
  void balanceTree(Node<T> *ptr);
  void balanceTree_1(Node<T> *ptr);
  void balanceTree_2(Node<T> *ptr);
  void push(Node<T> *startnode,  const T data);
  void push(const T data);
  void push(Node<T> *startnode, Node <T> *ptr);
  Node<T> *findNode(Node<T> *node, const T &volum);
  void printTree(Node<T> *node, int indent = 0) const;
  void clear(Node<T> *node);
  void colorChange(Node<T> *ptr);
  Node<T> *copyTree(Node<T>* node, Node<T>* parent = nullptr);
  void mergeRecursive(Node<T>* node);
  void removeRoot(Node<T> *node);
  int nodeCounting(Node<T>* node);

 public:

  using size_type = size_t;

  //Конструктор по умолчанию
  RB_Tree() = default;

  //Конструктор со списком инициализирования
  RB_Tree(std::initializer_list<T> const &items) {
    for (const auto &item : items) {
      push(item);
    }
  }

  //Конструктор копирования
  RB_Tree(const RB_Tree& other) {
    root = copyTree(other.root);
  }

  //Конструктор перемещения
  RB_Tree(RB_Tree&& other) noexcept : root(other.root) {
    other.root = nullptr;
  }

  //Перегрузка оператора присваивания для перемещения объекта
  RB_Tree& operator=(RB_Tree&& other) noexcept {
    if (this != &other) {
      clear(root);
      root = other.root;
      other.root = nullptr;
    }
    return *this;
  }

  //Деструктор
  ~RB_Tree();

  Node<T> *find(const T &volum);
  void remove(const T &volum);
  void print();

  // Метод at для доступа к элементу с проверкой границ
  template <typename K = T, typename std::enable_if_t<std::is_same_v<K, T>, int> = 0>
  T& at(const T& key);

  template <typename K = T, typename std::enable_if_t<!std::is_same_v<K, T>, int> = 0>
  T& at(const typename K::key_type& key);

  // Оператор [] для доступа или вставки элемента
  template <typename K = T, typename std::enable_if_t<std::is_same_v<K, T>, int> = 0>
  T& operator[](const T& key);

  template <typename K = T, typename std::enable_if_t<!std::is_same_v<K, T>, int> = 0>
  T& operator[](const typename K::key_type& key);

  // Методы для доступа к информации о наполнении контейнера
  bool empty();
  size_type size();
  size_type max_size();

  class iterator {
    private:
      Node<T>* current;
    public:
      iterator(Node<T> *node);

      //Префиксный оператор++
      iterator& operator++();

      //Префиксный оператор--
      iterator& operator--();

      //Постфиксный оператор++
      iterator operator++(int);

      //Постфиксный оператор--
      iterator operator--(int);

      //Операторы сравнения
      bool operator==(const iterator &other) const;
      bool operator!=(const iterator &other) const;
      bool operator>(const iterator &other) const;
      bool operator<(const iterator &other) const;

      //Оператор разыменования
      T& operator*() const;

      //Оператор доступа к члену
      T* operator->() const;

  };

  class const_iterator {
    private:
      const Node<T>* current;
    public:
      const_iterator(const Node<T> *node);

      // Префиксный оператор++
      const_iterator& operator++();

      // Префиксный оператор--
      const_iterator& operator--();

      // Постфиксный оператор++
      const_iterator operator++(int);

      // Постфиксный оператор--
      const_iterator operator--(int);

      // Операторы сравнения
      bool operator==(const const_iterator &other) const;
      bool operator!=(const const_iterator &other) const;
      bool operator>(const const_iterator &other) const;
      bool operator<(const const_iterator &other) const;

      // Оператор разыменования
      const T& operator*() const;

      // Оператор доступа к члену
      const T* operator->() const;
  };

  // Методы для получения итераторов
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Метод для удаления элемента по итератору
  void erase(iterator pos);

  // Метод для обмена содержимым с другим деревом
  void swap(RB_Tree<T>& other);

  // Сливает два контейнера
  void merge(RB_Tree<T>&  other);
 
};

template <typename T>
RB_Tree<T>::~RB_Tree() {
  clear(root);
}

template <typename T>
Node<T> *RB_Tree<T>::grandfather(Node<T> *ptr) {
  if (ptr == nullptr || ptr->parent == nullptr) return nullptr;
  return ptr->parent->parent;
}

template <typename T>
Node<T> *RB_Tree<T>::uncle(Node<T> *ptr) {
  Node<T> *gf = grandfather(ptr);
  if (ptr == nullptr || gf == nullptr) return nullptr;
  Node<T> *result = (gf->left == ptr->parent ? gf->right : gf->left);
  return result;
}

template <typename T>
void RB_Tree<T>::rotateRight(Node<T> *ptr) {
  std::swap(ptr->nodeColor, ptr->parent->nodeColor);
  Node<T> *father = ptr->parent;
  father->left = ptr->right;
  ptr->parent = father->parent;
  ptr->right = father;
  father->parent = ptr;
  if (father->left) father->left->parent = father;
  if (ptr->parent){
    if(ptr->parent->left == father) ptr->parent->left = ptr;
    else ptr->parent->right = ptr;
  } else root = ptr;
}

template <typename T>
void RB_Tree<T>::rotateLeft(Node<T> *ptr) {
  std::swap(ptr->nodeColor, ptr->parent->nodeColor);
  Node<T> *father = ptr->parent;
  father->right = ptr->left;
  ptr->parent = father->parent;
  ptr->left = father;
  father->parent = ptr;
  if (father->right) father->right->parent = father;
  if (ptr->parent){
    if(ptr->parent->left == father) ptr->parent->left = ptr;
    else ptr->parent->right = ptr;
  } else root = ptr;
}

template <typename T>
void RB_Tree<T>::balanceTree(Node<T> *ptr) {
  Node<T> *un = uncle(ptr);
  Node<T> *gf = grandfather(ptr);
  if (un && un->nodeColor == RED) {
    // перекраска
    un->nodeColor = BLACK;
    ptr->parent->nodeColor = BLACK;
    if (gf != root) {
      gf->nodeColor = RED;
      if (gf->parent->nodeColor == RED) balanceTree(gf);
    }
  } else if(gf){
    if(gf->right == ptr->parent) balanceTree_1(ptr);
    else balanceTree_2(ptr);
  }
}

template <typename T>
void RB_Tree<T>::balanceTree_1(Node<T> *ptr) {
  Node<T> *father = ptr->parent;
  if (father->left == ptr) {
    father->left = ptr->right;
    if(ptr->right) ptr->right->parent = father;
    ptr->right = father;
    ptr->parent = father->parent;
    father->parent->right = ptr;
    father->parent = ptr;
    rotateLeft(ptr);
  } else rotateLeft(father);
}

template <typename T>
void RB_Tree<T>::balanceTree_2(Node<T> *ptr) {
  Node<T> *father = ptr->parent;
  if (father->right == ptr) {
    father->right = ptr->left;
    if(ptr->left) ptr->left->parent = father;
    ptr->left = father;
    ptr->parent = father->parent;
    father->parent->left = ptr;
    father->parent = ptr;
    rotateRight(ptr);
  } else rotateRight(father);
}

template <typename T>
Node<T> *RB_Tree<T>::findNode(Node<T> *node, const T &volum) {
  if (node == nullptr || node->data == volum) {
    return node;
  }

  if (volum < node->data) {
    return findNode(node->left, volum);
  } else {
    return findNode(node->right, volum);
  }
}

template <typename T>
void RB_Tree<T>::printTree(Node<T> *node, int indent) const {
  if (node) {
    printTree(node->right, indent + 1);
    for (int i = 0; i < indent; ++i) std::cout << ".";
    std::cout << node->data << ":"
              << (node->nodeColor == BLACK ? "BLACK" : "RED") << std::endl;
    printTree(node->left, indent + 1);
  }
}

// Этот подход к удалению узла и его потомков
// рабочий, но требует больших затрат памяти
/*template <typename T> 
void RB_Tree<T>::clear(Node<T> *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}*/

// Более эффективный подход к удалению, требует меньше
// памяти, т.к. сразу подтирает узел.
template <typename T>
void RB_Tree<T>::clear(Node<T> *node) {
  if (node) {
    // Сохраняем потомков текущего узла
    Node<T> *leftChild = node->left;
    Node<T> *rightChild = node->right;

    // Удаляем текущий узел
    delete node;

    // Рекурсивно вызываем clear для левого поддерева
    clear(leftChild);
    leftChild = nullptr; // Обнуляем указатель на левого потомка

    // Рекурсивно вызываем clear для правого поддерева
    clear(rightChild);
    rightChild = nullptr; // Обнуляем указатель на правого потомка
  }
}

// вставка
template <typename T>
void RB_Tree<T>::push(Node<T> *startnode,  const T data) {
  Node<T> *newnode = startnode;
  Node<T> *father = nullptr;
  int right = 0;
  while (newnode != nullptr) {
    father = newnode;
    std:: cout << data << std::endl;
    std:: cout << newnode->data << std::endl;
    if (data > newnode->data) {
      newnode = newnode->right;
      right = 1;
    } else if(data < newnode->data){
      newnode = newnode->left;
      right = 0;
    } else return;
  }

  newnode = new Node<T>(data);
  newnode->parent = father;
  if (father) {
    if (right == 1) father->right = newnode;
    else father->left = newnode;
    if (newnode->parent->nodeColor == RED) balanceTree(newnode);
  } else {
    newnode->nodeColor = BLACK;
    root = newnode;
  }
  ++tree_size;
}

template <typename T>
void RB_Tree<T>::push(const T data) {
  push(root, data);
}

template <typename T>
void RB_Tree<T>::push(Node<T> *startnode, Node <T> *ptr){
  T data = ptr->data;
  COLOR curren_color = ptr->nodeColor;
  push(startnode, data);
  Node<T> *newnode = find(data);
  if(newnode->nodeColor != curren_color) colorChange(ptr);
  if(ptr->right){
    newnode->right = ptr->right;
    ptr->right->parent = newnode;
  }
  if(ptr->left){
    newnode->left = ptr->left;
    ptr->left->parent = newnode;
  }
  delete ptr;
}

template <typename T>
Node<T> *RB_Tree<T>::find(const T &volum) {
  Node<T> *result = findNode(root, volum);
  return result;
}

template <typename T>
void RB_Tree<T>::colorChange(Node<T> *ptr){
  if(ptr) {
    ptr->nodeColor = (ptr->nodeColor == RED ? BLACK: RED);
    colorChange(ptr->left);
    colorChange(ptr->right);
  }
}

template <typename T>
void RB_Tree<T>::print() {
  printTree(root);
}

template <typename T>
Node<T>* RB_Tree<T>::copyTree(Node<T>* node, Node<T>* parent) {
    if (!node) return nullptr;
    Node<T>* newNode = new Node<T>(node->data);
    newNode->nodeColor = node->nodeColor;
    newNode->parent = parent;
    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);
    return newNode;
}

template <typename T>
template <typename K, typename std::enable_if_t<std::is_same_v<K, T>, int>>
T& RB_Tree<T>::at(const T& key) {
  Node<T>* node = findNode(root, key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->data;
}

template <typename T>
template <typename K, typename std::enable_if_t<!std::is_same_v<K, T>, int>>
T& RB_Tree<T>::at(const typename K::key_type& key) {
  Node<T>* node = findNode(root, T(key, T()));
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->data;
}

template <typename T>
template <typename K, typename std::enable_if_t<std::is_same_v<K, T>, int>>
T& RB_Tree<T>::operator[](const T& key) {
  Node<T>* node = findNode(root, key);
  if (node == nullptr) {
    push(key);
    node = findNode(root, key);
  }
  return node->data;
}

template <typename T>
template <typename K, typename std::enable_if_t<!std::is_same_v<K, T>, int>>
T& RB_Tree<T>::operator[](const typename K::key_type& key) {
  Node<T>* node = findNode(root, T(key, T()));
  if (node == nullptr) {
    push(T(key, T()));
    node = findNode(root, T(key, T()));
  }
  return node->data;
}

// Определение метода empty
template <typename T>
bool RB_Tree<T>::empty() {
  return tree_size == 0;
}

// Определение метода size
template <typename T>
typename RB_Tree<T>::size_type RB_Tree<T>::size() {
  return tree_size;
}

// Определение метода max_size
template <typename T>
typename RB_Tree<T>::size_type RB_Tree<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node<T>) / 2;
}

// Определения методов и операторов класса iterator
template <typename T>
RB_Tree<T>::iterator::iterator(Node<T> *node) : current(node) {}

template <typename T>
typename RB_Tree<T>::iterator& RB_Tree<T>::iterator::operator++() {
  if(current->right){
    current = current->right;
    while(current->left) current = current->left;
  } else {
    Node<T> *father = current->parent;
    while(father && current == father->right){
      current = father;
      father = father->parent;
    }
    current = father;
  }
  return *this;
}

template <typename T>
typename RB_Tree<T>::iterator& RB_Tree<T>::iterator::operator--() {
  if(current->left) {
    current = current->left;
    while(current->right) current = current->right;
  } else {
    Node<T> *father = current->parent;
    while(father && current == father->left){
      current = father;
      father = father->parent;
    }
    current = father;
  }
  return *this;
}

template <typename T>
typename RB_Tree<T>::iterator RB_Tree<T>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename RB_Tree<T>::iterator RB_Tree<T>::iterator::operator--(int) {
  iterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
bool RB_Tree<T>::iterator::operator==(const iterator &other) const {
  return current == other.current;
}

template <typename T>
bool RB_Tree<T>::iterator::operator!=(const iterator &other) const {
  return current != other.current;
}

template <typename T>
bool RB_Tree<T>::iterator::operator>(const iterator &other) const {
  return current->data > other.current->data;
}

template <typename T>
bool RB_Tree<T>::iterator::operator<(const iterator &other) const {
  return current->data < other.current->data;
}

template <typename T>
T& RB_Tree<T>::iterator::operator*() const {
  return current->data;
}

template <typename T>
T* RB_Tree<T>::iterator::operator->() const {
  return &current->data;
}

// Определения методов и операторов класса const_iterator
template <typename T>
RB_Tree<T>::const_iterator::const_iterator(const Node<T> *node) : current(node) {}

template <typename T>
typename RB_Tree<T>::const_iterator& RB_Tree<T>::const_iterator::operator++() {
  if(current->right){
    current = current->right;
    while(current->left) current = current->left;
  } else {
    const Node<T> *father = current->parent;
    while(father && current == father->right){
      current = father;
      father = father->parent;
    }
    current = father;
  }
  return *this;
}

template <typename T>
typename RB_Tree<T>::const_iterator& RB_Tree<T>::const_iterator::operator--() {
  if(current->left) {
    current = current->left;
    while(current->right) current = current->right;
  } else {
    const Node<T> *father = current->parent;
    while(father && current == father->left){
      current = father;
      father = father->parent;
    }
    current = father;
  }
  return *this;
}

template <typename T>
typename RB_Tree<T>::const_iterator RB_Tree<T>::const_iterator::operator++(int) {
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename RB_Tree<T>::const_iterator RB_Tree<T>::const_iterator::operator--(int) {
  const_iterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
bool RB_Tree<T>::const_iterator::operator==(const const_iterator &other) const {
  return current == other.current;
}

template <typename T>
bool RB_Tree<T>::const_iterator::operator!=(const const_iterator &other) const {
  return current != other.current;
}

template <typename T>
bool RB_Tree<T>::const_iterator::operator>(const const_iterator &other) const {
  return current->data > other.current->data;
}

template <typename T>
bool RB_Tree<T>::const_iterator::operator<(const const_iterator &other) const {
  return current->data < other.current->data;
}

template <typename T>
const T& RB_Tree<T>::const_iterator::operator*() const {
  return current->data;
}

template <typename T>
const T* RB_Tree<T>::const_iterator::operator->() const {
  return &current->data;
}

// Определения методов begin и end
template <typename T>
typename RB_Tree<T>::iterator RB_Tree<T>::begin() {
  Node<T> *node = root;
  while (node && node->left) {
    node = node->left;
  }
  return iterator(node);
}

template <typename T>
typename RB_Tree<T>::iterator RB_Tree<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename RB_Tree<T>::const_iterator RB_Tree<T>::begin() const {
  const Node<T> *node = root;
  while (node && node->left) {
    node = node->left;
  }
  return const_iterator(node);
}

template <typename T>
typename RB_Tree<T>::const_iterator RB_Tree<T>::end() const {
  return const_iterator(nullptr);
}

// Определение метода erase
template <typename T>
void RB_Tree<T>::erase(iterator pos) {
  if (pos == end()) return;
  remove(pos->data);
}

template <typename T>
void RB_Tree<T>::swap(RB_Tree<T>& other) {
  // Меняем местами корни деревьев
  std::swap(root, other.root);
  // Меняем местами размеры деревьев
  std::swap(tree_size, other.tree_size);
}

/*Слияние двух сбалансированных бинарных деревьев:
определяем дерево с максимальным размером. Берём его за основу,
т.к. при этом будет меньше операций вставок элементов с другого 
дерева. Чтобы не было проблем с именем первого дерева, необходимо
оставить наше дерево основным, а если его размер меньше, просто 
поменять деревья местами, путём замены их корней.
Начинаем вставлять элементы, начиная с корня, и вниз по веткам,
как в функции clear, запоминая указатели на потомков и удаляя
сразу узел, который вставили. Затем рекурсивно вызвать эту функцию
для потомков. Таким образом мы реализуем слияние двух деревьев и 
автоматическое удаления второго дерева.
*/
template <typename T>
void RB_Tree<T>::merge(RB_Tree<T>& other) {
    // Если текущее дерево меньше, меняем деревья местами
    if (this->size() < other.size()) {
        std::swap(this->root, other.root);
        std::swap(this->tree_size, other.tree_size);
    }

    // Вставляем элементы из другого дерева в текущее дерево
    mergeRecursive(other.root);
    other.root = nullptr; // Обнуляем корень второго дерева
    other.tree_size = 0;  // Обнуляем размер второго дерева
}

template <typename T>
void RB_Tree<T>::mergeRecursive(Node<T>* node) {
    if (node) {
        // Сохраняем потомков текущего узла
        Node<T>* leftChild = node->left;
        Node<T>* rightChild = node->right;

        // Вставляем текущий узел в текущее дерево
        push(node->data);

        // Удаляем текущий узел
        delete node;

        // Рекурсивно вызываем mergeRecursive для левого поддерева
        if(leftChild) mergeRecursive(leftChild);
        leftChild = nullptr;

        // Рекурсивно вызываем mergeRecursive для правого поддерева
        if(rightChild) mergeRecursive(rightChild);
        rightChild = nullptr;
    }
}
/*Таким образом, функция merge реализует слияние двух красно-черных деревьев 
с автоматическим удалением второго дерева, всегда используя текущее дерево в 
качестве основного.*/

template <typename T>
void RB_Tree<T>::remove(const T &volume){
  Node<T> *ptr = find(volume);
  if(!ptr) return;
  if(ptr != root){

    if(ptr->parent->left == ptr) ptr->parent->left = nullptr;
    else ptr->parent->right = nullptr;
    
    Node<T>* leftChild = ptr->left;
    Node<T>* rightChild = ptr->right;

    delete ptr;
    --tree_size;

    if(leftChild){
      mergeRecursive(leftChild);
      //leftChild = nullptr;
    }
    if(rightChild){
      mergeRecursive(rightChild);
      //rightChild = nullptr;
    }
  } else removeRoot(ptr);
}

/*Второй случай, когда удаляем узел, который является корнем особый:
при этом образуются два поддерева, левое и правое. Логика должна быть
такая же, как в случае слияния двух деревьев. Только для ускорения
процесса слияния необходимо определить поддерево с максимальным размером,
чтобы в него вставлять узлы поддерева с минимаальным размером.
Для этого нужен метод подсчета узлов в дереве. И достаточно посчитать
колличество тольк в одном дереве, т.к. во втором его можно вычислить*/

template <typename T>
void RB_Tree<T>::removeRoot(Node<T> *node){
  Node<T> *left_root = root->left;
  Node<T> *right_root = root->right;
  if(left_root) left_root->parent = nullptr;
  if(right_root) right_root->parent = nullptr;
  if(nodeCounting(left_root) >= tree_size / 2){
    left_root->nodeColor = BLACK;  
    root = left_root;
    delete node;
    --tree_size;
    mergeRecursive(right_root);
  } else {
    right_root->nodeColor = BLACK;  
    root = right_root;
    delete node;
    --tree_size;
    mergeRecursive(left_root);
  }
}

template <typename T>
int RB_Tree<T>::nodeCounting(Node<T>* node){
    // Если узел равен nullptr, возвращаем 0
    if (node == nullptr) {
        return 0;
    }
    // Возвращаем количество узлов в текущем поддереве
    return 1 + nodeCounting(node->left) + nodeCounting(node->right);
}

} // namespace rb_tree
#endif
