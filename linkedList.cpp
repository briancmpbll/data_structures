#include <memory>
#include <iostream>

using namespace std;

template <class T>
struct LinkedListNode;

template <class T>
using NodePtr = shared_ptr<LinkedListNode<T>>;

template <class T>
struct LinkedListNode {
  LinkedListNode(T _data) : data(_data) {};

  T data;
  NodePtr<T> next;
  NodePtr<T> prev;
};

template <class T>
class LinkedList {
public:
  LinkedList() : _size(0) {}

  int size()  const {
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

  void remove(int index) {
    // TODO
  }

protected:
  NodePtr<T> _head;
  NodePtr<T> _tail;
  int _size;
};

int main(int argc, char **argv) {
  int numbers[] = {9, 5, 4, 10, 16, 8, 21, 46, 5};
  LinkedList<int> list;

  for (const int &x : numbers) {
    list.push_back(x);
    list.print();
    list.print_reverse();
  }

  while (list.size() > 0) {
    list.pop_back();
    list.print();
    list.print_reverse();
  }

  for (const int &x : numbers) {
    list.push_front(x);
    list.print();
    list.print_reverse();
  }

  while (list.size() > 0) {
    list.pop_front();
    list.print();
    list.print_reverse();
  }

  return 0;
}
