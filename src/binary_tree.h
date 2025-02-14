#ifndef BINATY_TREE_H
#define BINATY_TREE_H

#include <iostream>
#include <limits>

namespace binary_tree {

enum COLOR { RED, BLACK };

template <typename T1, typename T2>
struct Node {
  T1 key;
  T2 data;
  Node *left = nullptr, *right = nullptr, *parent = nullptr;
  COLOR nodeColor = RED;

  // Конструктор для Node
  Node(const T1 &key, const T2 &data) : key(key), data(data) {}

  // Операторы сравнения для Node
  bool operator<(const Node<T1, T2> &other) const { return key < other.key; }
  bool operator>(const Node<T1, T2> &other) const { return key > other.key; }
  bool operator==(const Node<T1, T2> &other) const { return key == other.key; }
  bool operator!=(const Node<T1, T2> &other) const { return key != other.key; }

  // Перегрузка оператора вывода для Node
  friend std::ostream &operator<<(std::ostream &os, const Node<T1, T2> &node) {
    os << "Key: " << node.key << ", Data: " << node.data;
    return os;
  }
};

template <typename T1, typename T2>
class BinaryTree {
 private:
  Node<T1, T2> *root = nullptr;
  Node<T1, T2> *endNode = nullptr;
  size_t tree_size = 0;

  Node<T1, T2> *grandfather(Node<T1, T2> *ptr);
  Node<T1, T2> *uncle(Node<T1, T2> *ptr);
  void rotateRight(Node<T1, T2> *ptr);
  void rotateLeft(Node<T1, T2> *ptr);
  void balanceTree(Node<T1, T2> *ptr);
  void balanceTree_1(Node<T1, T2> *ptr);
  void balanceTree_2(Node<T1, T2> *ptr);
  void push(Node<T1, T2> *startnode, const T1 &key, const T2 &data);
  Node<T1, T2> *findNode(Node<T1, T2> *node, const T1 &key) const;
  void printTree(Node<T1, T2> *node, int indent = 0) const;
  void clear(Node<T1, T2> *node);
  void colorChange(Node<T1, T2> *ptr);
  void copyRecursive(const Node<T1, T2>* node, const Node<T1, T2>* end);
  void pushRecursive(Node<T1, T2> *node);
  void removeRoot(Node<T1, T2> *node);
  int nodeCounting(Node<T1, T2> *node);
  Node<T1, T2> *lastNode();  // Метод для нахождения последнего узла
  void updateEndNode();
  void repainting(Node<T1, T2> *ptr);
  bool checkAlternation(Node<T1, T2> *ptr);
  Node<T1, T2>* findMultiNode(Node<T1, T2> *node, const T1 &key) const;

 public:
  using size_type = size_t;

  // Конструктор по умолчанию
  BinaryTree() = default;

  // Конструктор со списком инициализирования
  BinaryTree(std::initializer_list<std::pair<T1, T2>> const &items) {
    for (const auto &item : items) {
      push(item.first, item.second);
    }
  }

  // Конструктор копирования
  BinaryTree(const BinaryTree &other) {
    copyRecursive(other.root, other.endNode);
    tree_size = other.tree_size;
    updateEndNode();
  }

  // Конструктор перемещения
  BinaryTree(BinaryTree &&other) noexcept
      : root(other.root), endNode(other.endNode), tree_size(other.tree_size) {
    other.root = nullptr;
    other.endNode = nullptr;
    other.tree_size = 0;
  }

  // Перегрузка оператора присваивания для перемещения объекта
  BinaryTree &operator=(BinaryTree &&other) noexcept {
    if (this != &other) {
      clear();  // Очищаем текущее дерево
      std::swap(root, other.root);
      std::swap(endNode, other.endNode);
      std::swap(tree_size, other.tree_size);
    }
    return *this;
  }

  // Деструктор
  ~BinaryTree();

  Node<T1, T2> *find(const T1 &key) const;
  void remove(Node<T1, T2> *ptr);
  void print();
  void push(const T1 &key, const T2 &data);

  // Методы для доступа к информации о наполнении контейнера
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  class iterator {
   private:
    Node<T1, T2> *current;

   public:
    iterator(Node<T1, T2> *node);

    // Префиксный оператор++
    iterator &operator++();

    // Префиксный оператор--
    iterator &operator--();

    // Постфиксный оператор++
    iterator operator++(int);

    // Постфиксный оператор--
    iterator operator--(int);

    // Операторы сравнения
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    bool operator>(const iterator &other) const;
    bool operator<(const iterator &other) const;

    // Оператор разыменования
    std::pair<T1, T2> operator*() const;

    // Оператор доступа к члену
    Node<T1, T2> *operator->() const;
  };

  class const_iterator {
   private:
    const Node<T1, T2> *current;

   public:
    const_iterator(const Node<T1, T2> *node);

    // Префиксный оператор++
    const_iterator &operator++();

    // Префиксный оператор--
    const_iterator &operator--();

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
    std::pair<const T1, const T2> operator*() const;

    // Оператор доступа к члену
    const Node<T1, T2> *operator->() const;
  };

  // Методы для получения итераторов
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Метод для удаления элемента по итератору
  void erase(iterator pos);

  // Метод для обмена содержимым с другим деревом
  void swap(BinaryTree<T1, T2> &other);

  // Сливает два контейнера
  void merge(BinaryTree<T1, T2> &other);

  // Метод для проверки наличия элемента
  bool contains(const T1 &key) const;

  // очистка дерева
  void clear();
};

template <typename T1, typename T2>
BinaryTree<T1, T2>::~BinaryTree() {
  clear();
  if (root) delete root;
  if (endNode) delete endNode;
}

template <typename T1, typename T2>
Node<T1, T2> *BinaryTree<T1, T2>::grandfather(Node<T1, T2> *ptr) {
  if (ptr == nullptr || ptr->parent == nullptr) return nullptr;
  return ptr->parent->parent;
}

template <typename T1, typename T2>
Node<T1, T2> *BinaryTree<T1, T2>::uncle(Node<T1, T2> *ptr) {
  Node<T1, T2> *gf = grandfather(ptr);
  if (ptr == nullptr || gf == nullptr) return nullptr;
  Node<T1, T2> *result = (gf->left == ptr->parent ? gf->right : gf->left);
  return result;
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::rotateRight(Node<T1, T2> *ptr) {
  std::swap(ptr->nodeColor, ptr->parent->nodeColor);
  Node<T1, T2> *father = ptr->parent;
  father->left = ptr->right;
  ptr->parent = father->parent;
  ptr->right = father;
  father->parent = ptr;
  if (father->left) father->left->parent = father;
  if (ptr->parent) {
    if (ptr->parent->left == father)
      ptr->parent->left = ptr;
    else
      ptr->parent->right = ptr;
  } else  root = ptr;
  repainting(ptr);
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::rotateLeft(Node<T1, T2> *ptr) {
  std::swap(ptr->nodeColor, ptr->parent->nodeColor);
  Node<T1, T2> *father = ptr->parent;
  father->right = ptr->left;
  ptr->parent = father->parent;
  ptr->left = father;
  father->parent = ptr;
  if (father->right) father->right->parent = father;
  if (ptr->parent) {
    if (ptr->parent->left == father)
      ptr->parent->left = ptr;
    else
      ptr->parent->right = ptr;
  } else root = ptr;
  repainting(ptr);
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::checkAlternation(Node<T1, T2> *ptr) {
  bool result = false;
  if(ptr->left && ptr->left->nodeColor == BLACK && ptr->left != endNode) result = true;
  if(ptr->right && ptr->right->nodeColor == BLACK && ptr->right != endNode) result = true;
  return result;
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::repainting(Node<T1, T2> *ptr) {
  if(ptr->left && ptr->right){
    if(ptr->left->nodeColor == RED && ptr->right->nodeColor == RED){
      if(checkAlternation(ptr->left) || checkAlternation(ptr->right)) return;
      ptr->left->nodeColor = BLACK;
      ptr->right->nodeColor = BLACK;
      if(ptr != root) {
        ptr->nodeColor = RED;
        if(ptr->parent->nodeColor == RED) balanceTree(ptr);
      }
    }
  }
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::balanceTree(Node<T1, T2> *ptr) {
  Node<T1, T2> *un = uncle(ptr);
  Node<T1, T2> *gf = grandfather(ptr);
  if (un && un->nodeColor == RED) {
    // перекраска
    repainting(gf);
  } else if (gf) {
    if (gf->right == ptr->parent)
      balanceTree_1(ptr);
    else
      balanceTree_2(ptr);
  }
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::balanceTree_1(Node<T1, T2> *ptr) {
  Node<T1, T2> *father = ptr->parent;
  if (father->left == ptr) {
    father->left = ptr->right;
    if (ptr->right) ptr->right->parent = father;
    ptr->right = father;
    ptr->parent = father->parent;
    father->parent->right = ptr;
    father->parent = ptr;
    rotateLeft(ptr);
  } else
    rotateLeft(father);
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::balanceTree_2(Node<T1, T2> *ptr) {
  Node<T1, T2> *father = ptr->parent;
  if (father->right == ptr) {
    father->right = ptr->left;
    if (ptr->left) ptr->left->parent = father;
    ptr->left = father;
    ptr->parent = father->parent;
    father->parent->left = ptr;
    father->parent = ptr;
    rotateRight(ptr);
  } else
    rotateRight(father);
}

template <typename T1, typename T2>
Node<T1, T2> *BinaryTree<T1, T2>::findMultiNode(Node<T1, T2> *node,
                                           const T1 &key) const {
  Node<T1, T2> * result = node;
  if(node->left){
    if(findNode(node->left, key)) return findNode(node->left, key);
  }
  return result;
}

template <typename T1, typename T2>
Node<T1, T2> *BinaryTree<T1, T2>::findNode(Node<T1, T2> *node,
                                           const T1 &key) const {                                          
  if (node == nullptr) return node;
  if (key == node->key) return findMultiNode(node, key);
  if (key < node->key) {
    return findNode(node->left, key);
  } else {
    return findNode(node->right, key);
  }
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::printTree(Node<T1, T2> *node, int indent) const {
  if (!node) return;
  if (node != endNode) {
    printTree(node->right, indent + 1);
    for (int i = 0; i < indent; ++i) std::cout << ".";
    std::cout << node->key << ":"
              << (node->nodeColor == BLACK ? "BLACK" : "RED") << std::endl;
    printTree(node->left, indent + 1);
  }
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::clear(Node<T1, T2> *node) {
  if (node) {
    // Сохраняем потомков текущего узла
    Node<T1, T2> *leftChild = node->left;
    Node<T1, T2> *rightChild = node->right;

    // Удаляем текущий узел
    delete node;

    // Рекурсивно вызываем clear для левого поддерева
    clear(leftChild);

    // Рекурсивно вызываем clear для правого поддерева
    clear(rightChild);
  }
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::clear() {
  clear(root);
  if (root) root = nullptr;
  if (endNode) endNode = nullptr;
  tree_size = 0;
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::push(Node<T1, T2> *startnode, const T1 &key,
                              const T2 &data) {
  Node<T1, T2> *newnode = startnode;
  Node<T1, T2> *father = nullptr;
  int right = 0;
  while (newnode != nullptr && newnode != endNode) {
    father = newnode;
    if (key > newnode->key) {
      newnode = newnode->right;
      right = 1;
    } else if (key < newnode->key) {
      newnode = newnode->left;
      right = 0;
    } else {
      if (nodeCounting(newnode->left) >= nodeCounting(newnode->right)) {
        newnode = newnode->right;
        right = 1;
      } else {
        newnode = newnode->left;
        right = 0;
      }
    }
  }
  // if(newnode == endNode) endNode = nullptr;
  newnode = new Node<T1, T2>(key, data);
  if (father) {
    newnode->parent = father;
    newnode->nodeColor = RED;
    if (right == 1)
      father->right = newnode;
    else
      father->left = newnode;
    if (father->nodeColor == RED) balanceTree(newnode);
    else repainting(father);
  } else {
    newnode->nodeColor = BLACK;
    root = newnode;
  }
  updateEndNode();
  ++tree_size;
  //print();
  //std::cout<<std::endl;
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::push(const T1 &key, const T2 &data) {
  push(root, key, data);
}

template <typename T1, typename T2>
Node<T1, T2> *BinaryTree<T1, T2>::find(const T1 &key) const {
  Node<T1, T2> *result = findNode(root, key);
  return result;
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::colorChange(Node<T1, T2> *ptr) {
  if (ptr) {
    ptr->nodeColor = (ptr->nodeColor == RED ? BLACK : RED);
    colorChange(ptr->left);
    colorChange(ptr->right);
  }
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::print() {
  printTree(root);
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::copyRecursive(const Node<T1, T2>* node, 
                          const Node<T1, T2>* end){
  if (node && node != end) {
    // Сохраняем потомков текущего узла
    Node<T1, T2> *leftChild = node->left;
    Node<T1, T2> *rightChild = node->right;

    // Вставляем текущий узел в новое дерево
    push(node->key, node->data);

    // Рекурсивно вызываем copyRecursive для левого поддерева
    if (leftChild) copyRecursive(leftChild, end);
    leftChild = nullptr;
    
    // Рекурсивно вызываем copyRecursive для правого поддерева
    if (rightChild) copyRecursive(rightChild, end);
    rightChild = nullptr;

  }
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::empty() const {
  return tree_size == 0;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::size_type BinaryTree<T1, T2>::size() const {
  return tree_size;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::size_type BinaryTree<T1, T2>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Node<T1, T2>) / 2;
}

template <typename T1, typename T2>
BinaryTree<T1, T2>::iterator::iterator(Node<T1, T2> *node) : current(node) {}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::iterator &
BinaryTree<T1, T2>::iterator::operator++() {
  if (current == nullptr) return *this;
  if (current->right){
    current = current->right;
    while (current->left) {current = current->left;}
    return *this;
  }
  if(current == current->parent->left){
    current = current->parent;
    return *this;
  }
  if(current == current->parent->right){
    while (current->parent && current == current->parent->right)
    {
      current = current->parent;
    }
    if(current->parent) current = current->parent;
    else{
      while (current->right) {current = current->right;}
    }    
  }
  return *this;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::iterator &
BinaryTree<T1, T2>::iterator::operator--() {
  if (current == nullptr) return *this;
  if (current->left) {
    current = current->left;  
    while (current->right) current = current->right;
  } else {
    Node<T1, T2> *father = current->parent;
    if (father == nullptr || current == father->left) return *this;
    while (father && current == father->left) {
      current = father;
      father = father->parent;
    }
    current = father;
  }
  return *this;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::iterator BinaryTree<T1, T2>::iterator::operator++(
    int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::iterator BinaryTree<T1, T2>::iterator::operator--(
    int) {
  iterator temp = *this;
  --(*this);
  return temp;
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::iterator::operator==(const iterator &other) const {
  return current == other.current;
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::iterator::operator!=(const iterator &other) const {
  return current != other.current;
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::iterator::operator>(const iterator &other) const {
  return current->key > other.current->key;
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::iterator::operator<(const iterator &other) const {
  return current->key < other.current->key;
}

template <typename T1, typename T2>
std::pair<T1, T2> BinaryTree<T1, T2>::iterator::operator*() const {
  return std::make_pair(current->key, current->data);
}

template <typename T1, typename T2>
Node<T1, T2> *BinaryTree<T1, T2>::iterator::operator->() const {
  return current;
}

template <typename T1, typename T2>
BinaryTree<T1, T2>::const_iterator::const_iterator(const Node<T1, T2> *node)
    : current(node) {}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::const_iterator &
BinaryTree<T1, T2>::const_iterator::operator++() {
  if (current == nullptr) return *this;
  if (current->right){
    current = current->right;
    while (current->left) {current = current->left;}
    return *this;
  }
  if(current == current->parent->left){
    current = current->parent;
    return *this;
  }
  if(current == current->parent->right){
    while (current->parent && current == current->parent->right)
    {
      current = current->parent;
    }
    if(current->parent) current = current->parent;
    else{
      while (current->right) {current = current->right;}
    }  
  }
  return *this;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::const_iterator &
BinaryTree<T1, T2>::const_iterator::operator--() {
  if (current == nullptr) return *this;
  if (current->left) {
    current = current->left;  
    while (current->right) current = current->right;
  } else {
    Node<T1, T2> *father = current->parent;
    if (father == nullptr || current == father->left) return *this;
    while (father && current == father->left) {
      current = father;
      father = father->parent;
    }
    current = father;
  }
  return *this;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::const_iterator
BinaryTree<T1, T2>::const_iterator::operator++(int) {
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::const_iterator
BinaryTree<T1, T2>::const_iterator::operator--(int) {
  const_iterator temp = *this;
  --(*this);
  return temp;
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::const_iterator::operator==(
    const const_iterator &other) const {
  return current == other.current;
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::const_iterator::operator!=(
    const const_iterator &other) const {
  return current != other.current;
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::const_iterator::operator>(
    const const_iterator &other) const {
  return current->key > other.current->key;
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::const_iterator::operator<(
    const const_iterator &other) const {
  return current->key < other.current->key;
}

template <typename T1, typename T2>
std::pair<const T1, const T2> BinaryTree<T1, T2>::const_iterator::operator*()
    const {
  return std::make_pair(current->key, current->data);
}

template <typename T1, typename T2>
const Node<T1, T2> *BinaryTree<T1, T2>::const_iterator::operator->() const {
  return current;
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::iterator BinaryTree<T1, T2>::begin() {
  Node<T1, T2> *node = root;
  if (!node) return iterator(nullptr);
  while (node && node->left) {
    node = node->left;
  }
  return iterator(node);
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::iterator BinaryTree<T1, T2>::end() {
  return iterator(endNode);
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::const_iterator BinaryTree<T1, T2>::begin() const {
  const Node<T1, T2> *node = root;
  if (!node) return const_iterator(nullptr);
  while (node && node->left) {
    node = node->left;
  }
  return const_iterator(node);
}

template <typename T1, typename T2>
typename BinaryTree<T1, T2>::const_iterator BinaryTree<T1, T2>::end() const {
  return const_iterator(endNode);
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::erase(iterator pos) {
  if (pos == end()) return;
  Node<T1, T2> *ptr = find(pos->key);
  remove(ptr);
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::swap(BinaryTree<T1, T2> &other) {
  // Меняем местами корни деревьев
  std::swap(root, other.root);
  // Меняем местами размеры деревьев
  std::swap(tree_size, other.tree_size);
  // меняем endNode
  std::swap(endNode, other.endNode);
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::merge(BinaryTree<T1, T2> &other) {
  // Если текущее дерево меньше, меняем деревья местами
  if (this->size() < other.size()) {
    swap(other);
  }

  auto it = other.begin();

  for (; it != other.end(); ++it) {
    push(it->key, it->data);
  }

  other.clear();
  other.tree_size = 0;  // Обнуляем размер второго дерева
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::pushRecursive(Node<T1, T2> *node) {
  if (node && node != endNode) {
    // Сохраняем потомков текущего узла
    Node<T1, T2> *leftChild = node->left;
    Node<T1, T2> *rightChild = node->right;

    // Вставляем текущий узел в текущее дерево
    push(node->key, node->data);
    
    // Удаляем текущий узел
    delete node;
    --tree_size;

    // Рекурсивно вызываем pushRecursive для левого поддерева
    if (leftChild) pushRecursive(leftChild);
    leftChild = nullptr;
    
    // Рекурсивно вызываем pushRecursive для правого поддерева
    if (rightChild) pushRecursive(rightChild);
    rightChild = nullptr;

  }
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::remove(Node<T1, T2> *ptr) {
  if (!ptr) return;
  if (ptr != root) {
    if (ptr->parent->left == ptr)
      ptr->parent->left = nullptr;
    else
      ptr->parent->right = nullptr;

    Node<T1, T2> *leftChild = ptr->left;
    Node<T1, T2> *rightChild = ptr->right;

    delete ptr;
    --tree_size;

    if (leftChild) {
      pushRecursive(leftChild);
    }
    if (rightChild) {
      pushRecursive(rightChild);
    }
  } else removeRoot(ptr);
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::removeRoot(Node<T1, T2> *node) {
  Node<T1, T2> *left_root = root->left;
  Node<T1, T2> *right_root = root->right;
  if (left_root) left_root->parent = nullptr;
  if (right_root) right_root->parent = nullptr;
  
  if(left_root || right_root){
    if (nodeCounting(left_root) >= nodeCounting(right_root)) {
      left_root->nodeColor = BLACK;
      root = left_root;
      delete node;
      --tree_size;
      pushRecursive(right_root);
    } else {
      right_root->nodeColor = BLACK;
      root = right_root;
      delete node;
      --tree_size;
      pushRecursive(left_root);
    }
  } else {
    delete node;
    --tree_size;
    root = nullptr;
  }
}

template <typename T1, typename T2>
int BinaryTree<T1, T2>::nodeCounting(Node<T1, T2> *node) {
  // Если узел равен nullptr, возвращаем 0
  if (node == nullptr) {
    return 0;
  }
  // Возвращаем количество узлов в текущем поддереве
  return 1 + nodeCounting(node->left) + nodeCounting(node->right);
}

template <typename T1, typename T2>
Node<T1, T2> *BinaryTree<T1, T2>::lastNode() {
  Node<T1, T2> *current = root;
  if (!current) return nullptr;
  while (current->right && current->right != endNode) {
    current = current->right;
  }
  return current;
}

template <typename T1, typename T2>
void BinaryTree<T1, T2>::updateEndNode() {
  if (root) {
    Node<T1, T2> *last = lastNode();
    if (!endNode) endNode = new Node<T1, T2>{T1(), T2()};
    last->right = endNode;
    endNode->parent = last;
    endNode->nodeColor = BLACK;
  } else {
    endNode = nullptr;
  }
}

template <typename T1, typename T2>
bool BinaryTree<T1, T2>::contains(const T1 &key) const {
  bool result = false;
  if (find(key)) return true;
  return result;
}

}  // namespace binary_tree

#endif