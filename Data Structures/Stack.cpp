#include <stdexcept>

class Stack {
private:
    struct Node {
        int value;
        Node* next;

        Node(int value, Node* next) : value(value), next(next) {}
    };

    Node* first;

    static Node* copy(Node* other) {
        if (other == nullptr) {
            return nullptr;
        }
        return new Node(other->value, copy(other->next));
    }

    static Node* alternativeCopy(Node* other) {
        if (other == nullptr) {
            return nullptr;
        }

        Node* head = new Node(other->value, nullptr);
        Node* tail = head;

        for (Node* current = other->next; current != nullptr; current = current->next) {
            tail->next = new Node(current->value, nullptr);
            tail = tail->next;
        }

        return head;
    }

    void deallocate() {
        while (first != nullptr) {
            Node* newFirst = first->next;
            delete first;
            first = newFirst;
        }
    }

public:
    Stack() : first(nullptr) {}

    Stack(const Stack& other) : first(copy(other.first)) {}

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            deallocate();
            first = copy(other.first);
        }
        return *this;
    }

    ~Stack() {
        deallocate();
    }

    // O(1)
    void push(int x) {
        Node* newFirst = new Node(x, first);
        first = newFirst;
    }

    // O(1)
    int pop() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from an empty stack");
        }

        Node* newFirst = first->next;
        int poppedValue = first->value;
        delete first;
        first = newFirst;
        return poppedValue;
    }

    // O(1)
    int peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot peek in an empty stack");
        }

        return first->value;
    }

    // O(1)
    bool isEmpty() const {
        return first == nullptr;
    }
};
