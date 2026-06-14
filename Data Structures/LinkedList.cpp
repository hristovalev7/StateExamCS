class LinkedList {
private:
    struct Node {
        int value;
        Node* next;

        Node(int value, Node* next) : value(value), next(next) {}
    };

    Node* first;
    Node* last;

    void copy(Node* node) {
        for (Node* current = node; current != nullptr; current = current->next) {
            insertLast(current->value);
        }
    }

    void deallocate() {
        while (first) {
            Node* current = first;
            first = first->next;
            delete current;
        }
        first = nullptr;
        last = nullptr;
    }

    void emptyInsert(int x) {
        Node* newNode = new Node(x, nullptr);
        first = newNode;
        last = newNode;
    }

    void removeSingleElement() {
        delete first;
        first = nullptr;
        last = nullptr;
    }

public:
    LinkedList() : first(nullptr), last(nullptr) {}

    LinkedList(const LinkedList& other) : first(nullptr), last(nullptr) {
        copy(other.first);
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            deallocate();
            copy(other.first);
        }
        return *this;
    }

    ~LinkedList() {
        deallocate();
    }

    void insertLast(int x) { // O(1)
        if (isEmpty()) {
            emptyInsert(x);
            return;
        }
        Node* newLast = new Node(x, nullptr);
        last->next = newLast;
        last = newLast;
    }

    void insertFirst(int x) { // O(1)
        if (isEmpty()) {
            emptyInsert(x);
            return;
        }
        Node* newFirst = new Node(x, first);
        first = newFirst;
    }

    void removeFirst() { // O(1)
        if (isEmpty()) {
            return;
        }
        if (first == last) {
            removeSingleElement();
            return;
        }
        Node* newFirst = first->next;
        delete first;
        first = newFirst;
    }

    void removeLast() { // O(n), но ако е doubly linked може за O(1)
        if (isEmpty()) {
            return;
        }
        if (first == last) {
            removeSingleElement();
            return;
        }
        Node* current = first;
        while (current->next != last) {
            current = current->next;
        }
        current->next = nullptr;
        delete last;
        last = current;
    }

    bool contains(int x) const { // O(n)
        for (Node* current = first; current != nullptr; current = current->next) {
            if (current->value == x) {
                return true;
            }
        }
        return false;
    }

    bool isEmpty() const { // O(1)
        return first == nullptr;
    }
};
