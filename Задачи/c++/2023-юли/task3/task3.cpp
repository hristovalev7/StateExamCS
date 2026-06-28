#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

struct Node {
  int x;
  int y;

  Node *left = nullptr, *mid = nullptr, *right = nullptr;
};

struct Tree {
  Node* root = nullptr;
};

void insert(Node*& root, int value) {
  if (root == nullptr) {
    root = new Node();
    root->x = root->y = value;
    return;
  }

  if (value < root->x)
    insert(root->left, value);
  else if (value == root->x)
    insert(root->mid, value);
  else if (root->x == root->y)
    root->y = value;
  else if (value < root->y)
    insert(root->mid, value);
  else
    insert(root->right, value);
}

void insert(Tree& tree, int value) {
  insert(tree.root, value);
}

bool find(Node* root, int value) {
  if (root == nullptr) {
    return false;
  }

  if (value == root->x || value == root->y)
    return true;
  else if (value < root->x)
    return find(root->left, value);
  else if (value < root->y)
    return find(root->mid, value);
  return find(root->right, value);
}

bool find(const Tree& tree, int value) {
  return find(tree.root, value);
}

void clear(Node* root) {
  if (root == nullptr) {
    return;
  }

  clear(root->left);
  clear(root->mid);
  clear(root->right);
  delete root;
}

void clear(Tree& t) {
  clear(t.root);
  t.root = nullptr;
}

int main() {
  Tree t;
  int N;
  do {
    std::cout << "N = ";
    std::cin >> N;
  } while (N <= 0);

  for (int i = 0; i < N; ++i) {
    int value;
    std::cin >> value;
    insert(t, value);
  }

  int X;
  std::cin >> X;
  std::cout << "The tree " << (find(t, X) ? "contains " : "does not contain ")
            << X << "\n";

  clear(t);
  return 0;
}
