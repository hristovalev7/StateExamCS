class Queue {
    struct Node {
        int value;
        Node* next;

        Node(int value, Node* next) :
            value(value), next(next) {
        }
    };

    Node* first;
    Node* last;

    void deallocate() {
        while (first) {
            Node* newFirst = first->next;
            delete first;
            first = newFirst;
        }
        first = nullptr;
        last = nullptr;
    }

    void copy(Node* start) {
        for (Node* current = start; current != nullptr; current = current->next) {
            enqueue(current->value);
        }
    }

public:
    Queue() :
        first(nullptr), last(nullptr) {
    }

    Queue(const Queue& other) :
        first(nullptr), last(nullptr) {
        copy(other.first);
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            deallocate();
            copy(other.first);
        }
        return *this;
    }

    ~Queue() {
        deallocate();
    }

    bool isEmpty() const {
        return first == nullptr;
    }

    int getHead() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot get the first element of an empty queue");
        }
        return first->value;
    }

    void enqueue(int x) {
        Node* newNode = new Node(x, nullptr);
        if (isEmpty()) {
            first = newNode;
            last = newNode;
            return;
        }
        last->next = newNode;
        last = newNode;
    }

    int dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot dequeue from an empty queue");
        }
        Node* newFirst = first->next;
        int value = first->value;
        delete first;
        first = newFirst;
        return value;
    }
};
