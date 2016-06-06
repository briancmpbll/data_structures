#include <memory>
#include <iostream>

using namespace std;

class LinkedListNode;
typedef shared_ptr<LinkedListNode> NodePtr;

class LinkedListNode {
public:
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
  NodePtr newNode(new LinkedListNode);
  newNode->data = data;

  if (current == nullptr) {
    return newNode;
  }

  while (current->next != nullptr) {
    current = current->next;
  }

  current->next = newNode;

  return head;
}

int main(int argc, char **argv) {
  int numbers[] = {9, 5, 4, 10, 16, 8, 21, 46, 5};
  NodePtr head;

  for (const int &x : numbers) {
    head = push_back(head, x);
    printLinkedList(head);
  }

  return 0;
}
