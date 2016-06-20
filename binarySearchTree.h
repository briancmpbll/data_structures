#include <iostream>
#include <memory>

template <class Key, class Value>
struct TreeNode;

template <class Key, class Value>
using NodePtr = std::shared_ptr<TreeNode<Key, Value>>;

template <class Key, class Value>
struct TreeNode {
  explicit TreeNode(const Key &key, const Value &value) :
  _key(key), _value(value)
  {}

  ~TreeNode() {
    std::cout << "Deleting node " << _key << std::endl;
  }

  void replaceNodeInParent(const NodePtr<Key, Value> &newNode) {
    if (_parent != nullptr) {
      if (this == _parent->_left.get()) {
        _parent->_left = newNode;
      }
      else {
        _parent->_right = newNode;
      }
    }

    if (newNode != nullptr) {
      newNode->_parent = _parent;
    }
  }

  Key _key;
  Value _value;
  NodePtr<Key, Value> _parent;
  NodePtr<Key, Value> _left;
  NodePtr<Key, Value> _right;
};

template <class Key, class Value>
class BinarySearchTree {
public:
  void printInOrder() const {
    printInOrder(_root);
    std::cout << "\n";
  }

  bool find(const Key &key, Value *value) const {
    NodePtr<Key, Value> current = _root;

    while (current != nullptr) {
      if (current->_key == key) {
        *value = current->_value;
        return true;
      }
      if (key < current->_key) {
        current = current->_left;
      }
      else {
        current = current->_right;
      }
    }

    return false;
  }

  void insert(const Key &key, const Value &value) {
    insert(_root, nullptr, key, value);
  }

  bool erase(const Key &key) {
    NodePtr<Key, Value> current = _root;

    while (current != nullptr && key != current->_key) {
      if (key < current->_key) {
        current = current->_left;
      }
      else {
        current = current->_right;
      }
    }

    if (current == nullptr) {
      return false;
    }

    if (current->_left != nullptr && current->_right != nullptr) {
      std::cout << "Node has both children" << std::endl;
    }
    else if (current->_left != nullptr) {
      std::cout << "Node has a left child" << std::endl;
      current->replaceNodeInParent(current->_left);
    }
    else if (current->_right != nullptr) {
      std::cout << "Node has a right child" << std::endl;
      current->replaceNodeInParent(current->_right);
    }
    else {
      std::cout << "Node has no children" << std::endl;
      current->replaceNodeInParent(nullptr);
    }

    return true;
  }

protected:
  void printInOrder(const NodePtr<Key, Value> &node) const {
    if (node == nullptr) {
      return;
    }
    printInOrder(node->_left);
    std::cout << node->_key << " ";
    printInOrder(node->_right);
  }

  void insert(NodePtr<Key, Value> &node, const NodePtr<Key, Value> &parent,
              const Key &key, const Value &value) {
    if (node == nullptr) {
      node.reset(new TreeNode<Key, Value>(key, value));
      node->_parent = parent;
    }
    else if (key < node->_key) {
      insert(node->_left, node, key, value);
    }
    else {
      insert(node->_right, node, key, value);
    }
  }

  NodePtr<Key, Value> _root;
};
