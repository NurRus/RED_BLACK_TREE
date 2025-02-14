#ifndef SET_H
#define SET_H

#include <initializer_list>
#include <utility>

#include "../tree/binary_tree.h"

namespace binary_tree {

template <typename Key>
class set {
 private:
  BinaryTree<Key, Key> tree;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  class iterator {
   private:
    typename BinaryTree<Key, Key>::iterator it;

   public:
    iterator(typename BinaryTree<Key, Key>::iterator iter) : it(iter) {}

    // Оператор разыменования
    key_type operator*() const {
      return it->key;  // Возвращаем только ключ
    }

    // Операторы сравнения
    bool operator==(const iterator &other) const { return it == other.it; }
    bool operator!=(const iterator &other) const { return it != other.it; }
    bool operator>(const iterator &other) const { return it > other.it; }
    bool operator<(const iterator &other) const { return it < other.it; }

    // Префиксный оператор++
    iterator &operator++() {
      ++it;
      return *this;
    }

    // Постфиксный оператор++
    iterator operator++(int) {
      iterator temp = *this;
      ++it;
      return temp;
    }

    // Префиксный оператор--
    iterator &operator--() {
      --it;
      return *this;
    }

    // Постфиксный оператор--
    iterator operator--(int) {
      iterator temp = *this;
      --it;
      return temp;
    }

    // Оператор доступа к члену
    Node<Key, Key> *operator->() const { return it.operator->(); }

    // Метод для получения  итератора
    typename BinaryTree<Key, Key>::iterator getIterator() const { return it; }
  };

  class const_iterator {
   private:
    typename BinaryTree<Key, Key>::const_iterator it;

   public:
    const_iterator(typename BinaryTree<Key, Key>::const_iterator iter)
        : it(iter) {}

    // Оператор разыменования
    const key_type operator*() const {
      return it->first;  // Возвращаем только ключ
    }

    // Операторы сравнения
    bool operator==(const const_iterator &other) const {
      return it == other.it;
    }
    bool operator!=(const const_iterator &other) const {
      return it != other.it;
    }
    bool operator>(const const_iterator &other) const { return it > other.it; }
    bool operator<(const const_iterator &other) const { return it < other.it; }

    // Префиксный оператор++
    const_iterator &operator++() {
      ++it;
      return *this;
    }

    // Постфиксный оператор++
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++it;
      return temp;
    }

    // Префиксный оператор--
    const_iterator &operator--() {
      --it;
      return *this;
    }

    // Постфиксный оператор--
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --it;
      return temp;
    }
    // Оператор доступа к члену
    const Node<Key, Key> *operator->() const { return it.operator->(); }
  };

  set() = default;

  set(std::initializer_list<key_type> const &items) {
    for (const auto &item : items) {
      tree.push(item, item);
    }
  }

  set(const set &s) : tree(s.tree) {}

  set(set &&s) noexcept : tree(std::move(s.tree)) {}

  // Оператор присваивания перемещением
  set &operator=(set &&other) noexcept {
    if (this != &other) {
      tree = std::move(other.tree);
    }
    return *this;
  }

  // Оператор присваивания копированием
  set &operator=(const set &s) {
    if (this != &s) {
      tree = s.tree;
    }
    return *this;
  }

  ~set() = default;

  iterator begin() { return iterator(tree.begin()); }
  iterator end() { return iterator(tree.end()); }
  const_iterator begin() const { return const_iterator(tree.begin()); }
  const_iterator end() const { return const_iterator(tree.end()); }

  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  void clear() { tree.clear(); }

  std::pair<iterator, bool> insert(const key_type &value) {
    Node<Key, Key> *result = tree.find(value);
    if (result) {
      return std::make_pair(iterator(result), false);
    }
    tree.push(value, value);
    result = tree.find(value);
    return std::make_pair(iterator(result), true);
  }

  void erase(iterator pos) { tree.erase(pos.getIterator()); }

  void swap(set &other) { tree.swap(other.tree); }

  void merge(set &other) { tree.merge(other.tree); }

  void print_tree() { tree.print(); }

  bool contains(const Key &key) { return tree.contains(key); }

  iterator find(const Key &key) {
    Node<Key, Key> *result = tree.find(key);
    if (result) {
      return iterator(result);
    }
    return end();
  }
};

}  // namespace binary_tree

#endif  // SET_H

  
  