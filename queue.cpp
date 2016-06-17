#include <iostream>
#include <vector>

#include "common.h"

using namespace std;

template <class T>
class Queue {
public:
  Queue() : _size(0) {}

  int size() const {
    return _size;
  }

  void print() const {
    NodePtr<T> current = _head;
    while(current != nullptr) {
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

  int peek() const {
    if (_tail == nullptr) {
      throw string("No data.");
    }

    return _tail->data;
  }

  void enqueue(T data) {
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

  void dequeue() {
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

protected:
  NodePtr<T> _head;
  NodePtr<T> _tail;
  int _size;
};

int main(int argc, char **argv) {
  vector<int> numbers = {9, 5, 4, 10, 16, 8, 21, 46, 5};
  Queue<int> queue;

  try {
    queue.peek();
  }
  catch (const string &e) {
    cout << e << endl;
  }

  cout << "///// push" << endl;
  for (const int &x : numbers) {
    queue.enqueue(x);
    cout << queue.peek() << endl;
    queue.print();
    queue.print_reverse();
  }

  for (int i = 0; i < 3; ++i) {
    queue.dequeue();
    cout << queue.peek() << std::endl;
    queue.print();
    queue.print_reverse();
  }

  for (const int &x : numbers) {
    queue.enqueue(x);
    cout << queue.peek() << endl;
    queue.print();
    queue.print_reverse();
  }

  while (queue.size() > 0) {
    cout << queue.peek() << std::endl;
    queue.dequeue();
    queue.print();
    queue.print_reverse();
  }
}
