#include <iostream>
#include <vector>
using namespace std;

// А)
struct TreeNode {
  int data;
  vector<TreeNode*> children;
  TreeNode(int d) : data(d) {}
};

// Б)
int findLevel(const TreeNode* root, const vector<int>& numbers) {
  if (root == nullptr) {
    return -1;
  }

  vector<const TreeNode*> current = {root};
  int lvl = 0;

  while (!current.empty()) {
    vector<int> values;
    for (const TreeNode* node : current) {
      values.push_back(node->data);
    }

    if (values == numbers) {
      return lvl;
    }

    vector<const TreeNode*> next;
    for (const TreeNode* node : current) {
      for (const TreeNode* child : node->children) {
        next.push_back(child);
      }
    }

    current = next;
    lvl++;
  }

  return -1;
}

// В)
void removeAllLevels(TreeNode* root, const vector<int>& numbers) {
  if (root == nullptr) {
    return;
  }

  vector<TreeNode*> current = {root};

  while (!current.empty()) {
    vector<TreeNode*> next;
    for (TreeNode* node : current) {
      for (TreeNode* child : node->children) {
        next.push_back(child);
      }
    }

    if (next.empty()) {
      break;
    }

    vector<int> values;
    for (TreeNode* node : next) {
      values.push_back(node->data);
    }

    if (values == numbers) {
      for (TreeNode* node : current) {
        vector<TreeNode*> new_successors;

        for (TreeNode* child : node->children) {
          for (TreeNode* grandchild : child->children) {
            new_successors.push_back(grandchild);
          }
          delete child;
        }
        node->children = new_successors;
      }
    } else {
      current = next;
    }
  }
}
