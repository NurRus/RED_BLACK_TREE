#ifndef MULTISET_H
#define MULTISET_H

#include <initializer_list>
#include <utility>

#include "../tree/binary_tree.h"

namespace binary_tree {

template <typename Key>
class multiset {
 private:
  BinaryTree<Key, Key> tree;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  class MultisetIterator {
   private:
    typename BinaryTree<Key, Key>::iterator it;

   public:
    MultisetIterator(typename BinaryTree<Key, Key>::iterator iter) : it(iter) {}

    // Оператор разыменования
    key_type operator*() const {
      return it->key;  // Возвращаем только ключ
    }

    // Операторы сравнения
    bool operator==(const MultisetIterator &other) const {
      return it == other.it;
    }
    bool operator!=(const MultisetIterator &other) const {
      return it != other.it;
    }
    bool operator>(const MultisetIterator &other) const {
      return it > other.it;
    }
    bool operator<(const MultisetIterator &other) const {
      return it < other.it;
    }

    // Префиксный оператор++
    MultisetIterator &operator++() {
      ++it;
      return *this;
    }

    // Постфиксный оператор++
    MultisetIterator operator++(int) {
      MultisetIterator temp = *this;
      ++it;
      return temp;
    }

    // Префиксный оператор--
    MultisetIterator &operator--() {
      --it;
      return *this;
    }

    // Постфиксный оператор--
    MultisetIterator operator--(int) {
      MultisetIterator temp = *this;
      --it;
      return temp;
    }

    // Метод для получения итератора
    typename BinaryTree<Key, Key>::iterator getIterator() const { return it; }
  };

  class MultisetConstIterator {
   private:
    typename BinaryTree<Key, Key>::const_iterator it;

   public:
    MultisetConstIterator(typename BinaryTree<Key, Key>::const_iterator iter)
        : it(iter) {}

    // Оператор разыменования
    const key_type operator*() const {
      return it->key;  // Возвращаем только ключ
    }

    // Операторы сравнения
    bool operator==(const MultisetConstIterator &other) const {
      return it == other.it;
    }
    bool operator!=(const MultisetConstIterator &other) const {
      return it != other.it;
    }
    bool operator>(const MultisetConstIterator &other) const {
      return it > other.it;
    }
    bool operator<(const MultisetConstIterator &other) const {
      return it < other.it;
    }

    // Префиксный оператор++
    MultisetConstIterator &operator++() {
      ++it;
      return *this;
    }

    // Постфиксный оператор++
    MultisetConstIterator operator++(int) {
      MultisetConstIterator temp = *this;
      ++it;
      return temp;
    }

    // Префиксный оператор--
    MultisetConstIterator &operator--() {
      --it;
      return *this;
    }

    // Постфиксный оператор--
    MultisetConstIterator operator--(int) {
      MultisetConstIterator temp = *this;
      --it;
      return temp;
    }
  };

  using iterator = MultisetIterator;
  using const_iterator = MultisetConstIterator;

  // Конструктор по умолчанию
  multiset() = default;

  // Конструктор со списком инициализации
  multiset(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      tree.push(item, item);
    }
  }

  // Конструктор копирования
  multiset(const multiset &ms) : tree(ms.tree) {}

  // Конструктор перемещения
  multiset(multiset &&ms) noexcept : tree(std::move(ms.tree)) {}

  // Деструктор
  ~multiset() = default;

  // Оператор присваивания перемещением
  multiset &operator=(multiset &&ms) noexcept {
    if (this != &ms) {
      tree = std::move(ms.tree);
    }
    return *this;
  }

  // Методы для итерации
  iterator begin() { return iterator(tree.begin()); }
  iterator end() { return iterator(tree.end()); }
  const_iterator begin() const { return const_iterator(tree.begin()); }
  const_iterator end() const { return const_iterator(tree.end()); }

  // Методы для проверки состояния контейнера
  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  // Методы для изменения контейнера
  void clear() { tree.clear(); }

  iterator insert(const value_type &value) {
    tree.push(value, value);
    return iterator(tree.find(value));
  }

  void erase(iterator pos) { tree.erase(pos.getIterator()); }

  void swap(multiset &other) { tree.swap(other.tree); }

  void merge(multiset &other) { tree.merge(other.tree); }

  // Методы для просмотра контейнера
  size_type count(const Key &key) const {
    size_type count = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
      if (it->key == key) {
        ++count;
      }
    }
    return count;
  }

  iterator find(const Key &key) {
    Node<Key, Key> *result = tree.find(key);
    if (result) {
      return iterator(result);
    }
    return end();
  }

  bool contains(const Key &key) const { return tree.contains(key); }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    iterator start = lower_bound(key);
    iterator end = upper_bound(key);
    return std::make_pair(start, end);
  }

  iterator lower_bound(const Key &key) {
    iterator it = begin();
    if (it == end() || *it >= key) return it;
    while (it != end() && *it < key) {
      ++it;
    }
    return it;
  }

  iterator upper_bound(const Key &key) {
    iterator it = begin();
    while (it != end() && *it <= key) {
      ++it;
    }
    return it;
  }

  void print_tree() { tree.print(); }
};

}  // namespace binary_tree

#endif  // MULTISET_H
