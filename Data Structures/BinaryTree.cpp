#include <stdexcept>

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
    void deallocate(Node* root) {
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
            root = copy(other.root);
        }
        return *this;
    }

    ~BinaryTree() {
        deallocate(root);
    }

    // O(1)
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
};
