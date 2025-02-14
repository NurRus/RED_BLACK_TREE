#include <iostream>
#include "rb_tree.h"

using std::cout;
using std::endl;
using std::string;
using std::out_of_range;

int main() {
    // Тестирование с простыми типами данных
    rb_tree::RB_Tree<int> intTree = {10, 5, 15, 3, 7, 12, 17};

    cout << "Int Tree:" << endl;
    intTree.print();

    cout << "Finding 7: " << (intTree.find(7) ? "Found" : "Not Found") << endl;
    cout << "Finding 20: " << (intTree.find(20) ? "Found" : "Not Found") << endl;

    intTree.remove(5);
    cout << "Int Tree after removing 5:" << endl;
    intTree.print();

    // Тестирование с dataMap
    rb_tree::RB_Tree<rb_tree::dataMap<string, int>> dataMapTree = {{"apple", 10}, {"banana", 20}, {"cherry", 30}, {"date", 40}};

    cout << "DataMap Tree:" << endl;
    dataMapTree.print();

    cout << "Finding 'banana': " << (dataMapTree.find({"banana", 0}) ? "Found" : "Not Found") << endl;
    cout << "Finding 'grape': " << (dataMapTree.find({"grape", 0}) ? "Found" : "Not Found") << endl;

    dataMapTree.remove({"banana", 0});
    cout << "DataMap Tree after removing 'banana':" << endl;
    dataMapTree.print();

    // Тестирование слияния деревьев
    rb_tree::RB_Tree<int> otherIntTree = {20, 25, 30};

    cout << "Other Int Tree:" << endl;
    otherIntTree.print();

    intTree.merge(otherIntTree);
    cout << "Int Tree after merging with Other Int Tree:" << endl;
    intTree.print();

    // Тестирование итераторов
    cout << "Iterating through Int Tree:" << endl;
    for (auto it = intTree.begin(); it != intTree.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Тестирование константных итераторов
    const rb_tree::RB_Tree<int>& constIntTree = intTree;
    cout << "Iterating through Const Int Tree:" << endl;
    for (auto it = constIntTree.begin(); it != constIntTree.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Тестирование оператора []
    intTree[22] = 22;
    cout << "Int Tree after inserting 22 using operator[]:" << endl;
    intTree.print();

    // Тестирование метода at
    try {
        cout << "Value at key 22: " << intTree.at(22) << endl;
    } catch (const out_of_range& e) {
        cout << "Key 22 not found: " << e.what() << endl;
    }

    // Тестирование метода empty
    cout << "Is Int Tree empty? " << (intTree.empty() ? "Yes" : "No") << endl;

    // Тестирование метода size
    cout << "Size of Int Tree: " << intTree.size() << endl;

    // Тестирование метода max_size
    cout << "Max size of Int Tree: " << intTree.max_size() << endl;

    // Тестирование метода swap
    rb_tree::RB_Tree<int> swappedTree = {100, 200};
    cout << "Swapped Tree before swap:" << endl;
    swappedTree.print();

    intTree.swap(swappedTree);
    cout << "Int Tree after swap:" << endl;
    intTree.print();
    cout << "Swapped Tree after swap:" << endl;
    swappedTree.print();

    return 0;
}
