#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>

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
  
  Node<T> *grandfather(Node<T> *ptr);
  Node<T> *uncle(Node<T> *ptr);
  void rotateRight(Node<T> *ptr);
  void rotateLeft(Node<T> *ptr);
  void balanceTree(Node<T> *ptr);
  void balanceTree_1(Node<T> *ptr);
  void balanceTree_2(Node<T> *ptr);
  Node<T> *findNode(Node<T> *node, const T &volum);
  void printTree(Node<T> *node, int indent = 0) const;
  void clear(Node<T> *node);
  void colorChange(Node<T> *ptr);
  void removeLeft(Node<T> *ptr);
  void removeRight(Node<T> *ptr);

 public:
  RB_Tree() = default;
  ~RB_Tree();
  // вставка
  void push(Node<T> *startnode,  const T data);
  void push(const T data);
  void push(Node<T> *startnode, Node <T> *ptr);
  Node<T> *find(const T &volum);
  void remove(const T &volum);
  void print();
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

template <typename T>
void RB_Tree<T>::clear(Node<T> *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
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
    if (data > newnode->data) {
      newnode = newnode->right;
      right = 1;
    } else {
      newnode = newnode->left;
      right = 0;
    }
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
void RB_Tree<T>::removeLeft(Node<T> *ptr){
  COLOR ptrcolor = ptr->nodeColor;
  if(ptr->right){
    ptr->right->parent = ptr->parent;
    Node<T> *cutptr = ptr->right->left;
    if(!ptr->parent) {
      ptr->right->nodeColor = BLACK;
      root = ptr->right;
    } else {
      ptr->parent->left = ptr->right;
      if(ptr->right->nodeColor != ptrcolor) colorChange(ptr->right);
    }
    if(ptr->left){
      ptr->left->parent = ptr->right;
      ptr->right->left = ptr->left;
      if(cutptr) push(ptr->left, cutptr);
    }
  } else if(ptr->left){
    ptr->left->parent = ptr->parent;
    if(!ptr->parent){
      ptr->left->nodeColor = BLACK;
      root = ptr->left;
    } else {
      ptr->parent->left = ptr->left;
      if(ptr->left->nodeColor != ptrcolor) colorChange(ptr->left);
    } 
  }  
  delete ptr;
}

template <typename T>
void RB_Tree<T>::removeRight(Node<T> *ptr){
  COLOR ptrcolor = ptr->nodeColor;
  if(ptr->left){
    ptr->left->parent = ptr->parent;
    Node<T> *cutptr = ptr->left->right;
    if(!ptr->parent) {
      ptr->left->nodeColor = BLACK;
      root = ptr->left;
    } else {
      ptr->parent->right = ptr->left;
      if(ptr->left->nodeColor != ptrcolor) colorChange(ptr->left);
    }
    if(ptr->right){
      ptr->right->parent = ptr->left;
      ptr->left->right = ptr->right;
      if(cutptr) push(ptr->right, cutptr);
    }
  } else if(ptr->right){
    ptr->right->parent = ptr->parent;
    if(!ptr->parent){
      ptr->right->nodeColor = BLACK;
      root = ptr->right;
    } else {
      ptr->parent->right = ptr->right;
      if(ptr->right->nodeColor != ptrcolor) colorChange(ptr->right);
    } 
  }  
  delete ptr;
}

template <typename T>
void RB_Tree<T>::remove(const T &volume){
  Node<T> *ptr = find(volume);
  if(ptr){
    if(ptr->parent->left == ptr) removeLeft(ptr);
    else removeRight(ptr);
  }
}

template <typename T>
void RB_Tree<T>::print() {
  printTree(root);
}

} // namespace rb_tree
#endif
