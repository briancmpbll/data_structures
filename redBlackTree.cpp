#include <memory>
#include <iostream>

using namespace std;

template <class T>
struct TreeNode;

template <class T>
using NodePtr = shared_ptr<TreeNode<T>>;

template <class T>
struct TreeNode {
  explicit TreeNode(const T &value) : _value(value), _black(false)
  {}

  NodePtr<T> grandparent() const {
    if (_parent != nullptr) {
      return _parent->_parent;
    }

    return nullptr;
  }

  NodePtr<T> uncle() const {
    NodePtr<T> gparent = grandparent();

    if (gparent != nullptr) {
      if (gparent->_left == _parent) {
        return gparent->_right;
      }
      return gparent->_left;
    }

    return nullptr;
  }

  T _value;
  bool _black;
  NodePtr<T> _left;
  NodePtr<T> _right;
  NodePtr<T> _parent;
};

template <class T>
class RedBlackTree {
public:
  bool contains(const T &value) const {
    NodePtr<T> current = _root;
    while (current != nullptr) {
      if (current->_value == value) {
        return true;
      }

      if (value < current->_value) {
        current = current->_left;
      }
      else {
        current = current->_right;
      }
    }

    return false;
  }

  void insert(const T &value) {
    NodePtr<T> newNode = binaryTreeInsert(value);
    rebalance(newNode);
  }

protected:
  NodePtr<T> binaryTreeInsert(const T &value) {
    NodePtr<T> newNode(new TreeNode<T>(value));

    if (_root == nullptr) {
      _root = newNode;
    }
    else {
      NodePtr<T> current = _root;
      bool done = false;

      while (current != nullptr && !done) {
        if (value < current->_value) {
          if (current->_left == nullptr) {
            current->_left = newNode;
            newNode->_parent = current;
            done = true;
          }
          current = current->_left;
        }
        else {
          if (current->_right == nullptr) {
            current->_right = newNode;
            newNode->_parent = current;
            done = true;
          }
          current = current->_right;
        }
      }
    }

    return newNode;
  }

  void rebalance(NodePtr<T> node) {
    NodePtr<T> parent = node->_parent;

    // Insert case 1 (node is root)
    if (parent == nullptr) {
      cout << "Case 1" << endl;
      node->_black = true;
      return;
    }

    // Insert case 2 (node's parent is black)
    if (parent->_black) {
      cout << "Case 2" << endl;
      return;
    }

    NodePtr<T> uncle = node->uncle();
    NodePtr<T> grandparent = node->grandparent();

    // Insert case 3 (node's parent and uncle are red)
    if (uncle != nullptr && !uncle->_black) {
      cout << "Case 3" << endl;
      parent->_black = true;
      uncle->_black = true;
      grandparent->_black = false;
      rebalance(grandparent);
      return;
    }

    // Insert case 4 (parent is red, uncle is black, parent is a left child,
    // node is a right child or vice versa)
    if (node == parent->_right
      && parent == grandparent->_left) {
      cout << "Case 4 left right" << endl;
      rotateLeft(parent);
      node = node->_left;
    }
    else if (node == parent->_left
      && parent == grandparent->_right) {
      cout << "Case 4 right left" << endl;
      rotateRight(parent);
      node = node->_right;
    }

    // Node's parent and grandparent may have changed, so update it.
    parent = node->_parent;
    grandparent = node->grandparent();

    // Insert case 5 (parent is red, uncle is black, parent and node are both
    // left children, or both right children)
    // Case 4 becomes case 5 after rotation
    parent->_black = true;
    grandparent->_black = false;
    if (node == parent->_left) {
      cout << "Case 5 left left" << endl;
      rotateRight(grandparent);
    }
    else {
      cout << "Case 5 right right" << endl;
      rotateLeft(grandparent);
    }
  }

  void rotateLeft(NodePtr<T> node) {
    NodePtr<T> child = node->_right;
    NodePtr<T> childLeft = child->_left;
    if (node == node->_parent->_left) {
      node->_parent->_left = child;
    }
    else {
      node->_parent->_right = child;
    }
    child->_left = node;
    child->_parent = node->_parent;
    node->_right = childLeft;
    node->_parent = child;
  }

  void rotateRight(NodePtr<T> node) {
    NodePtr<T> child = node->_left;
    NodePtr<T> childRight = child->_right;
    if (node == node->_parent->_left) {
      node->_parent->_left = child;
    }
    else {
      node->_parent->_right = child;
    }
    child->_right = node;
    child->_parent = node->_parent;
    node->_left = childRight;
    node->_parent = child;
  }

  NodePtr<T> _root;
};

int main(int argc, char **argv) {
  RedBlackTree<int> tree;

  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(2);
  tree.insert(20);
  tree.insert(18);
  tree.insert(11);
  tree.insert(25);
  tree.insert(7);
  tree.insert(16);
}
