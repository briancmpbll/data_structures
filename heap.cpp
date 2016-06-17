#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

template <class T>
class MinHeap {
public:
  explicit MinHeap(int size = 0) : _arr(size)
  {};

  void insert(T value) {
    _arr.push_back(value);
    shiftUp(_arr.size() - 1);
  }

  int size() const {
    return _arr.size();
  }

  T peek() const {
    if (_arr.size() == 0) {
      throw "No data.";
    }

    return _arr[0];
  }

  void pop() {
    if (_arr.size() == 0) {
      return;
    }

    _arr[0] = _arr[_arr.size() - 1];
    _arr.pop_back();

    shiftDown(0);
  }

protected:
  void shiftUp(int index) {
    if (index == 0) {
      return;
    }

    int parentIndex = parent(index);

    if (_arr[index] < _arr[parentIndex]) {
      swap(index, parentIndex);
      shiftUp(parentIndex);
    }
  }

  void shiftDown(int index) {
    unsigned int leftChildIndex = leftChild(index);
    unsigned int rightChildIndex = rightChild(index);

    if (leftChildIndex >= _arr.size()) {
      return;
    }

    bool leftSmaller = _arr[leftChildIndex] < _arr[index];
    bool rightSmaller = rightChildIndex < _arr.size()
      && _arr[rightChildIndex] < _arr[index];
    int swapIndex = -1;

    if (leftSmaller && rightSmaller) {
      swapIndex = _arr[leftChildIndex] < _arr[rightChildIndex]
        ? leftChildIndex
        : rightChildIndex;
    }
    else if (leftSmaller) {
      swapIndex = leftChildIndex;
    }
    else if (rightSmaller) {
      swapIndex = rightChildIndex;
    }

    if (swapIndex != -1) {
      swap(index, swapIndex);
      shiftDown(swapIndex);
    }
  }

  void swap(int index1, int index2) {
    T temp = _arr[index1];
    _arr[index1] = _arr[index2];
    _arr[index2] = temp;
  }

  static unsigned int leftChild(int index) {
    return 2 * index + 1;
  }

  static unsigned int rightChild(int index) {
    return 2 * index + 2;
  }

  static unsigned int parent(int index) {
    return (index - 1) / 2;
  }

  vector<T> _arr;
};

int main(int argc, char **argv) {
  vector<int> numbers = {9, 5, 4, 10, 16, 8, 21, 46, 5};
  MinHeap<int> heap;

  for (int &number : numbers) {
    heap.insert(number);
  }

  cout << heap.peek() << endl;
  heap.pop();

  cout << heap.peek() << endl;
  heap.pop();

  cout << heap.peek() << endl;
  heap.pop();

  for (int &number : numbers) {
    heap.insert(number);
  }

  while (heap.size() > 0) {
    cout << heap.peek() << endl;
    heap.pop();
  }
}
