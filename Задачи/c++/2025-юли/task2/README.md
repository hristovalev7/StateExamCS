# Задача 2

Задачата да се реши на езика **C++**.

---

## А) Анализ на код с полиморфизъм

Разгледайте дадения фрагмент:

```cpp
class base {
public:
    void print() {}
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
    b->print();
    delete b;
}
```

### А.1) Защо НЕ СЕ извежда "123"

**Въпрос:** Обяснете защо, въпреки че `run()` извиква `print()`, на изхода НЕ СЕ извежда "123".

**Отговор:**

`print()` НЕ Е виртуална функция. Свързването е статично и затова `b->print()` е обръщение към `base::print()`, а не на `derived::print()`.

---

### А.2) Къде има изтичане на памет

**Въпрос:** Посочете къде в кода има изтичане на памет (memory leak) и обяснете защо (какво се случва).

**Отговор:**

Аналогично, деструкторът на `base` НЕ Е виртуален. `delete b` води до обръщение към деструктора на `base`, а НЕ този на `derived`. Паметта заделена с `new int` в конструктора на `derived` никога не се освобождава.

---

### А.3) Коригиран код

**Въпрос:** Пренапишете кода на класа `base` така, че да НЕ изтича памет и `run()` да извежда на стандартния изход текста "123".

**Решение:**

```cpp
class base {
public:
    virtual void print() {}
    virtual ~base() {}
};
```

---

## Б) Реализация на йерархия от класове

### Б.1) Абстрактен базов клас `item`

**Условие:** Абстрактен базов клас `item` с единствен член – публична константна чисто виртуална (pure virtual) функция `value`, която няма аргументи и връща стойност от тип `int`.

**Решение:**

```cpp
class item {
public:
    virtual int value() const = 0;
    virtual ~item() {}
};
```

---

### Б.2) Клас `num`

**Условие:** Клас `num`, който наследява `item` и:

- пази в себе си число K от тип `int`;
- има конструктор, който получава число и инициализира с него K;
- реализира функцията `value()` да връща числото K.

**Решение:**

```cpp
class num : public item {
    int K;
public:
    num(int value) : K(value) {}

    virtual int value() const override {
        return K;
    }
};
```

---

### Б.3) Клас `seq`

**Условие:** Клас `seq`, който наследява `item` и:

- има член-данна `private` динамично заделен с `new` масив от N числа от тип `int`;
- има конструктор, който получава число N, заделя масива и го запълва с псевдослучайни числа (използвайте `std::rand()`), като ако N не е положително число да се хвърля изключение;
- има всички функции от rule of 3 (копиращ конструктор, копиращо присвояване, деструктор) и управлява коректно паметта;
- реализира функцията `value()` да връща първия елемент на масива.

**Решение:**

```cpp
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
```

---

## Пълно решение

Вижте файла [task2.cpp](task2.cpp) за цялостната програма.
