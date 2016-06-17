#include <iostream>
#include <vector>

#include "common.h"

using namespace std;

template <class T>
class LinkedList {
public:
  LinkedList() : _size(0) {}

  int size() const {
    return _size;
  }

  void print() const {
    NodePtr<T> current = _head;
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }

    cout << endl;
  }

  void print_reverse() const {
    NodePtr<T> current = _tail;
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->prev;
    }

    cout << endl;
  }

  int front() const {
    if (_head == nullptr) {
      throw string("No data");
    }

    return _head->data;
  }

  void push_front(T data) {
    NodePtr<T> newNode(new LinkedListNode<T>(data));

    if (_head != nullptr) {
      _head->prev = newNode;
    }

    newNode->next = _head;
    _head = newNode;
    ++_size;

    if (_size == 1) {
      _tail = newNode;
    }
  }

  void pop_front() {
    if (_head == nullptr) {
      return;
    }

    _head = _head->next;
    --_size;

    if (_head != nullptr) {
      _head->prev = nullptr;
    }

    if (_size <= 1) {
      _tail = _head;
    }
  }

  int back() {
    if (_tail == nullptr) {
      throw string("No data");
    }

    return _tail->data;
  }

  void push_back(T data) {
    NodePtr<T> newNode(new LinkedListNode<T>(data));

    if (_tail != nullptr) {
      _tail->next = newNode;
    }

    newNode->prev = _tail;
    _tail = newNode;
    ++_size;

    if (_size == 1) {
      _head = newNode;
    }
  }

  void pop_back() {
    if (_tail == nullptr) {
      return;
    }

    _tail = _tail->prev;
    --_size;

    if (_tail != nullptr) {
      _tail->next = nullptr;
    }

    if (_size <= 1) {
      _head = _tail;
    }
  }

  void insert(T data, int index) {
    if (index < 0 || index > _size) {
      return;
    }

    if (index == 0) {
      push_front(data);
    }
    else if (index == _size) {
      push_back(data);
    }
    else {
      NodePtr<T> newNode(new LinkedListNode<T>(data));

      int count = 0;
      NodePtr<T> current = _head;
      while (count < index) {
        current = current->next;
        ++count;
      }

      newNode->prev = current->prev;
      newNode->next = current;

      current->prev->next = newNode;
      current->prev = newNode;

      ++_size;
    }
  }

  void remove(int index) {
    if (index < 0 || index >= _size) {
      return;
    }

    if (index == 0) {
      pop_front();
    }
    else if (index == _size - 1) {
      pop_back();
    }
    else {
      int count = 0;
      NodePtr<T> current = _head;
      while (count < index) {
        current = current->next;
        ++count;
      }

      current->prev->next = current->next;
      current->next->prev = current->prev;
      --_size;
    }
  }

protected:
  NodePtr<T> _head;
  NodePtr<T> _tail;
  int _size;
};

int main(int argc, char **argv) {
  vector<int> numbers = {9, 5, 4, 10, 16, 8, 21, 46, 5};
  LinkedList<int> list;

  try {
    list.front();
  }
  catch (const string &e) {
    cout << e << endl;
  }

  try {
    list.back();
  }
  catch (const string &e) {
    cout << e << endl;
  }

  cout << "///// push_back" << endl;
  for (const int &x : numbers) {
    list.push_back(x);
    list.print();
    list.print_reverse();
  }

  cout << "///// insert" << endl;
  list.insert(110000, 4);
  list.print();
  list.print_reverse();

  cout << "///// pop_back" << endl;
  while (list.size() > 0) {
    list.pop_back();
    list.print();
    list.print_reverse();
  }

  cout << "///// push_front" << endl;
  for (const int &x : numbers) {
    list.push_front(x);
    list.print();
    list.print_reverse();
  }

  cout << "///// remove" << endl;
  list.remove(5);
  list.print();
  list.print_reverse();

  cout << "///// pop_front" << endl;
  while (list.size() > 0) {
    list.pop_front();
    list.print();
    list.print_reverse();
  }

  return 0;
}
