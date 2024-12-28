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

 public:
  RB_Tree() = default;
  ~RB_Tree();
  // вставка
  void push(const T data);
  Node<T> *find(const T &volum);
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
  Node<T> *temp = ptr->right;
  Node<T> *father = ptr->parent;
  ptr->parent = father->parent;
  father->parent = ptr;
  father->left = temp;
  ptr->right = father;
  if (temp) temp->parent = father;
  if (ptr->parent)
    ptr->parent->left = ptr;
  else
    root = ptr;
}

template <typename T>
void RB_Tree<T>::rotateLeft(Node<T> *ptr) {
  std::swap(ptr->nodeColor, ptr->parent->nodeColor);
  Node<T> *temp = ptr->left;
  Node<T> *father = ptr->parent;
  ptr->parent = grandfather(ptr);
  father->right = temp;
  ptr->left = father;
  father->parent = ptr;
  ptr->left = father;
  if (temp) temp->parent = father;
  if (ptr->parent)
    ptr->parent->right = ptr;
  else
    root = ptr;
}

template <typename T>
void RB_Tree<T>::balanceTree(Node<T> *ptr) {
  Node<T> *un = uncle(ptr);
  if (un && un->nodeColor == RED) {
    Node<T> *gf = grandfather(ptr);
    // перекраска
    un->nodeColor = BLACK;
    ptr->parent->nodeColor = BLACK;
    if (gf != root) {
      gf->nodeColor = RED;
      if (gf->parent && gf->parent->nodeColor == RED) balanceTree(gf);
    }
  } else
    balanceTree_1(ptr);
}

template <typename T>
void RB_Tree<T>::balanceTree_1(Node<T> *ptr) {
  Node<T> *gf = grandfather(ptr);
  if (gf && gf->right == ptr->parent) {
    Node<T> *father = ptr->parent;
    if (father->left == ptr) {
      Node<T> *temp = ptr->right;
      ptr->parent = gf;
      gf->right = ptr;
      father->parent = ptr;
      father->left = temp;
      ptr->right = father;
      rotateLeft(ptr);
    } else
      rotateLeft(father);
  } else
    balanceTree_2(ptr);
}

template <typename T>
void RB_Tree<T>::balanceTree_2(Node<T> *ptr) {
  Node<T> *gf = grandfather(ptr);
  if (gf && gf->left == ptr->parent) {
    Node<T> *father = ptr->parent;
    if (father->right == ptr) {
      Node<T> *temp = ptr->left;
      ptr->parent = gf;
      gf->left = ptr;
      father->parent = ptr;
      father->right = temp;
      ptr->right = father;
      rotateRight(ptr);
    } else
      rotateRight(father);
  }
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
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

// вставка
template <typename T>
void RB_Tree<T>::push(const T data) {
  Node<T> *newnode = root;
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
  if (father != nullptr) {
    if (right == 1)
      father->right = newnode;
    else
      father->left = newnode;
    if (newnode->parent->nodeColor == RED) balanceTree(newnode);
  } else {
    newnode->nodeColor = BLACK;
    root = newnode;
  }
}

template <typename T>
Node<T> *RB_Tree<T>::find(const T &volum) {
  Node<T> *result = findNode(root, volum);
  return result;
}

template <typename T>
void RB_Tree<T>::print() {
  printTree(root);
}

} // namespace rb_tree
#endif
