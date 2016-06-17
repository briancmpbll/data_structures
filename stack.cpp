#include <iostream>
#include <vector>

#include "common.h"

using namespace std;

template <class T>
class Stack {
public:
  Stack() : _size(0) {}

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

  int peek() const {
    if (_head == nullptr) {
      throw string("No data.");
    }

    return _head->data;
  }

  void push(T data) {
    NodePtr<T> newNode(new LinkedListNode<T>(data));

    newNode->next = _head;
    _head = newNode;
    ++_size;
  }

  void pop() {
    if (_head == nullptr) {
      return;
    }

    _head = _head->next;
    --_size;
  }

protected:
  NodePtr<T> _head;
  int _size;
};

int main(int argc, char **argv) {
  vector<int> numbers = {9, 5, 4, 10, 16, 8, 21, 46, 5};
  Stack<int> stack;

  try {
    stack.peek();
  }
  catch (const string &e) {
    cout << e << endl;
  }

  cout << "///// push" << endl;
  for (const int &x : numbers) {
    stack.push(x);
    cout << stack.peek() << endl;
    stack.print();
  }

  for (int i = 0; i < 3; ++i) {
    stack.pop();
    cout << stack.peek() << std::endl;
    stack.print();
  }

  for (const int &x : numbers) {
    stack.push(x);
    cout << stack.peek() << endl;
    stack.print();
  }

  while (stack.size() > 0) {
    cout << stack.peek() << std::endl;
    stack.pop();
    stack.print();
  }
}
