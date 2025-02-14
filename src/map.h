#ifndef MAP_H
#define MAP_H

#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "../tree/binary_tree.h"

namespace binary_tree {

template <typename Key, typename T>
class map {
 private:
  BinaryTree<Key, T> tree;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename BinaryTree<Key, T>::iterator;
  using const_iterator = typename BinaryTree<Key, T>::const_iterator;

  map() = default;

  map(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      tree.push(item.first, item.second);
    }
  }

  map(const map &other) : tree(other.tree) {}

  map(map &&other) noexcept : tree(std::move(other.tree)) {}

  ~map() = default;

  map &operator=(const map &other) {
    if (this != &other) {
      tree = other.tree;
    }
    return *this;
  }

  map &operator=(map &&other) noexcept {
    tree = std::move(other.tree);
    return *this;
  }

  T &at(const Key &key) {
    Node<Key, T> *result = tree.find(key);
    if (!result) throw std::out_of_range("Key not found");
    return result->data;
  }

  const T &at(const Key &key) const {
    Node<Key, T> *result = tree.find(key);
    if (!result) throw std::out_of_range("Key not found");
    return result->data;
  }

  T &operator[](const Key &key) {
    Node<Key, T> *result = tree.find(key);
    if (!result) {
      tree.push(key, T());
      result = tree.find(key);
    }
    return result->data;
  }

  const T &operator[](const Key &key) const {
    Node<Key, T> *result = tree.find(key);
    if (!result) throw std::out_of_range("Key not found");
    return result->data;
  }

  iterator begin() { return tree.begin(); }
  iterator end() { return tree.end(); }
  const_iterator begin() const { return tree.begin(); }
  const_iterator end() const { return tree.end(); }

  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  void clear() { tree.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    Node<Key, T> *result = tree.find(value.first);
    if (result) {
      return std::make_pair(iterator(result), false);
    }
    tree.push(value.first, value.second);
    result = tree.find(value.first);
    return std::make_pair(iterator(result), true);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    Node<Key, T> *result = tree.find(key);
    if (result) {
      result->data = obj;
      return std::make_pair(iterator(result), false);
    }
    tree.push(key, obj);
    result = tree.find(key);
    return std::make_pair(iterator(result), true);
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    tree.erase(pos);
  }

  void swap(map &other) { tree.swap(other.tree); }

  void merge(map &other) { tree.merge(other.tree); }

  bool contains(const Key &key) { return tree.contains(key); }

  void print_tree() { tree.print(); }

  iterator find(const Key &key) {
    Node<Key, Key> *result = tree.find(key);
    if (result) {
      return iterator(result);
    }
    return end();
  }
};

}  // namespace binary_tree

#endif  // MAP_H
