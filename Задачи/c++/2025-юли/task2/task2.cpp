#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

// А.3) Коригиран базов клас
class base {
public:
    virtual void print() {}
    virtual ~base() {}
};

class derived : public base {
    int* data;
public:
    derived() { data = new int; }
    ~derived() { delete data; }
    void print() { std::cout << "123"; }
};

void run() {
    base* b = new derived();
    b->print();  // Сега извежда "123"
    delete b;    // Сега няма memory leak
}

// Б.1) Абстрактен базов клас item
class item {
public:
    virtual int value() const = 0;
    virtual ~item() {}
};

// Б.2) Клас num
class num : public item {
    int K;
public:
    num(int value) : K(value) {}
    
    virtual int value() const override {
        return K;
    }
};

// Б.3) Клас seq
class seq : public item {
    int* data;
    int size;
public:
    // Конструктор
    seq(int N) : size(N) {
        if (N <= 0)
            throw std::invalid_argument("Incorrect size");
        
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = std::rand();
    }
    
    // Копиращ конструктор
    seq(const seq& s) : size(s.size) {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = s.data[i];
    }
    
    // Копиращо присвояване
    seq& operator=(seq const& s) {
        if (this != &s) {
            seq temp(s);
            std::swap(data, temp.data);
            std::swap(size, temp.size);
        }
        return *this;
    }
    
    // Деструктор
    ~seq() { delete[] data; }
    
    // Виртуална функция value()
    virtual int value() const override {
        return data[0];
    }
};