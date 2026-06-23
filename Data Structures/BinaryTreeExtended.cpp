#include <stdexcept>
#include <vector>

enum Direction {
    Left,
    Right
};

class BinaryTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
    };

    Node* root;

    // left -> right -> root
    static void deallocate(Node* root) {
        if (root == nullptr) {
            return;
        }

        deallocate(root->left);
        deallocate(root->right);
        delete root;
    }

    static Node* copy(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        return new Node(root->value, copy(root->left), copy(root->right));
    }

public:
    BinaryTree() : root(nullptr) {}
    BinaryTree(Node* root) : root(copy(root)) {}

    BinaryTree(const BinaryTree& other) : root(copy(other.root)) {}

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            deallocate(root);
            root = nullptr;
            root = copy(other.root);
        }
        return *this;
    }

    ~BinaryTree() {
        deallocate(root);
        root = nullptr;
    }

    // О(1)
    bool isEmpty() const {
        return root == nullptr;
    }

    // O(1)
    int getRootValue() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot take the root of an empty tree");
        }

        return root->value;
    }

    // O(n)
    BinaryTree getLeftSubtree() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot take the left subtree of an empty tree");
        }

        return BinaryTree(root->left);
    }

    // O(n)
    BinaryTree getRightSubtree() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot take the right subtree of an empty tree");
        }

        return BinaryTree(root->right);
    }

    // От тук надолу само ако остане време
    // O(n)
    bool insert(int value, const std::vector<Direction>& path) {
        if (path.empty()) {
            return false;
        }

        Node* current = root;
        size_t pathLength = path.size();
        for (int i = 0; i < pathLength - 1; ++i) {
            if (current == nullptr) {
                return false;
            }
            if (path[i] == Left) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            return false;
        }

        if (path[pathLength - 1] == Left) {
            return addLeftChild(current, value);
        }
        return addRightChild(current, value);
    }

private:
    // O(1)
    bool addLeftChild(Node* parent, int value) {
        if (parent->left != nullptr) {
            return false;
        }

        return addChild(parent, value, Left);
    }

    // O(1)
    bool addRightChild(Node* parent, int value) {
        if (parent->right != nullptr) {
            return false;
        }

        return addChild(parent, value, Right);
    }

    // O(1)
    bool addChild(Node* parent, int value, Direction direction) {
        if (direction == Left) {
            parent->left = new Node(value, nullptr, nullptr);
        } else {
            parent->right = new Node(value, nullptr, nullptr);
        }
        return true;
    }
};
