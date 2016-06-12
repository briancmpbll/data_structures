#include <memory>

template <class T>
struct LinkedListNode;

template <class T>
using NodePtr = std::shared_ptr<LinkedListNode<T>>;

template <class T>
struct LinkedListNode {
  LinkedListNode(T _data) : data(_data) {};

  T data;
  NodePtr<T> next;
  NodePtr<T> prev;
};
