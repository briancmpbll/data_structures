#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

class TrieNode;
using NodePtr = shared_ptr<TrieNode>;

using NodeMap = unordered_map<char, NodePtr>;

class TrieNode {
public:
  explicit TrieNode(char value) :
    _value(value),
    _terminates(false)
  {}

  char value() {
    return _value;
  }

  bool terminates() const {
    return _terminates;
  }

  void insert(const string &str, unsigned int start) {
    if (start >= str.size()) {
      _terminates = true;
      return;
    }

    char nextChar = str[start];
    auto itr = _children.find(nextChar);
    if (itr == _children.end()) {
      NodePtr newNode(new TrieNode(nextChar));
      _children.insert(make_pair(nextChar, newNode));
      cout << "Adding child: " << nextChar << endl;
      itr = _children.find(nextChar);
    }

    itr->second->insert(str, start + 1);
  }

  vector<string> getWords(const string &prefix = "") {
    vector<string> words;

    if (_terminates) {
      words.push_back(prefix + _value);
    }

    for (auto &child : _children) {
      vector<string> childWords = child.second->getWords(prefix + _value);
      words.insert(words.begin(), childWords.begin(), childWords.end());
    }

    return words;
  }

protected:
  char _value;
  bool _terminates;
  NodeMap _children;
};

class Trie {
public:
  Trie() : _root('\0')
  {}

  void insert(const string &str) {
    _root.insert(str, 0);
  }

  vector<string> getWords() {
    return _root.getWords();
  }

  void printWords() {
    vector<string> words = getWords();

    for (string &word : words) {
      cout << word << endl;
    }
  }

protected:
  TrieNode _root;
};

int main(int argc, char **argv) {
  Trie trie;

  trie.insert("hello");
  trie.insert("hell");
  trie.insert("hella");
  trie.insert("my");
  trie.insert("memory");
  trie.printWords();
}
