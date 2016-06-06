#include <memory>
#include <iostream>

using namespace std;

class LinkedListNode;
typedef shared_ptr<LinkedListNode> NodePtr;

class LinkedListNode {
public:
  LinkedListNode(int _data) : data(_data) {};

  int data;
  shared_ptr<LinkedListNode> next;
};

void printLinkedList(NodePtr head) {
  while (head != nullptr) {
    cout << head->data << " ";
    head = head->next;
  }

  cout << endl;
}

NodePtr push_back(NodePtr head, int data) {
  NodePtr current = head;
  NodePtr newNode(new LinkedListNode(data));

  if (current == nullptr) {
    return newNode;
  }

  while (current->next != nullptr) {
    current = current->next;
  }

  current->next = newNode;
  return head;
}

NodePtr pop_back(NodePtr head) {
  if (head == nullptr || head->next == nullptr) {
    return nullptr;
  }

  NodePtr current = head;

  while (current->next->next != nullptr) {
    current = current->next;
  }

  current->next = nullptr;
  return head;
}

NodePtr push_front(NodePtr head, int data) {
  NodePtr newNode(new LinkedListNode(data));

  newNode->next = head;

  return newNode;
}

NodePtr pop_front(NodePtr head) {
  if (head == nullptr) {
    return head;
  }

  return head->next;
}

NodePtr delete_node(NodePtr head, int index) {
  if (index < 0 || head == nullptr) {
    return head;
  }

  // TODO
  return nullptr;
}

int main(int argc, char **argv) {
  int numbers[] = {9, 5, 4, 10, 16, 8, 21, 46, 5};
  NodePtr headBack;
  NodePtr headFront;

  for (const int &x : numbers) {
    headBack = push_back(headBack, x);
    printLinkedList(headBack);
  }

  while (headBack != nullptr) {
    headBack = pop_back(headBack);
    printLinkedList(headBack);
  }

  for (const int &x : numbers) {
    headFront = push_front(headFront, x);
    printLinkedList(headFront);
  }

  while (headFront != nullptr) {
    headFront = pop_front(headFront);
    printLinkedList(headFront);
  }

  return 0;
}
