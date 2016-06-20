#include <vector>
#include "binarySearchTree.h"

using namespace std;

int main(int argc, char **argv) {
  BinarySearchTree<int, int> tree;
  vector<int> numbers = {9, 5, 4, 10, 16, 8, 21, 46, 7};

  for (const int &n : numbers) {
    tree.insert(n, n);
    tree.printInOrder();
  }

  int value;
  cout << tree.find(10, &value) << endl;
  cout << tree.find(22, &value) << endl;

  tree.erase(21);
  tree.printInOrder();

  tree.erase(8);
  tree.printInOrder();

  tree.erase(46);
  tree.printInOrder();

  tree.erase(9);
  tree.printInOrder();
}
