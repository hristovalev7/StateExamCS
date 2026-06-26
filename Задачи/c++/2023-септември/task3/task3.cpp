#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct Node {
  string name;
  vector<Node*> children;

  Node(const string& dirName) : name(dirName) {}
};

struct Tree {
  Node* root;

  Tree() { root = new Node(""); }
};

Node* findChild(const Node* child, const string& childName) {
  for (Node* child : child->children) {
    if (child->name == childName) {
      return child;
    }
  }

  return nullptr;
}

void insert(Tree& tree, const string& fullPath) {
  Node* current = tree.root;

  size_t i = 0;
  size_t pathLength = fullPath.length();

  while (i < pathLength) {
    if (fullPath[i] == '/') {
      i++;
      continue;
    }

    size_t start = i;

    while (i < pathLength && fullPath[i] != '/') {
      i++;
    }

    string dirName = fullPath.substr(start, i - start);

    Node* child = findChild(current, dirName);

    if (child == nullptr) {
      child = new Node(dirName);
      current->children.push_back(child);
    }

    current = child;
  }
}

Node* findNode(Tree& tree, const string& fullPath) {
  Node* current = tree.root;

  size_t i = 0;
  size_t pathLength = fullPath.length();

  while (i < pathLength) {
    if (fullPath[i] == '/') {
      i++;
      continue;
    }

    size_t start = i;
    while (i < pathLength && fullPath[i] != '/') {
      i++;
    }

    string dirName = fullPath.substr(start, i - start);

    Node* child = findChild(current, dirName);
    if (child == nullptr) {
      return nullptr;
    }

    current = child;
  }

  return current;
}

void flatten(Tree& tree, const string& fullPath) {
  Node* target = findNode(tree, fullPath);

  if (target == nullptr) {
    return;
  }

  vector<Node*> allDescendants;

  vector<Node*> queue;
  for (Node* child : target->children) {
    queue.push_back(child);
  }

  size_t idx = 0;
  while (idx < queue.size()) {
    Node* node = queue[idx];
    idx++;
    allDescendants.push_back(node);
    for (Node* grandchild : node->children) {
      queue.push_back(grandchild);
    }
  }

  vector<Node*> newChildren;
  unordered_set<string> seenNames;

  for (Node* node : allDescendants) {
    if (seenNames.find(node->name) == seenNames.end()) {
      seenNames.insert(node->name);
      node->children.clear();
      newChildren.push_back(node);
    }
  }

  target->children = newChildren;
}
