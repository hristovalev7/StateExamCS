# Задача 2 - Композиция на функции с шаблони

## Описание

Дадена е следната програмата на езика за програмиране C++, от която липсват части.

Класовете и шаблоните `Inc`, `Square`, `Sum` и `Max` описват **едноместни функции** от тип f: T → T. Видът на конкретната функция се дефинира от метода `value` в съответния клас.

**Описание на класовете:**

- **Inc** представя функцията f: double → double, f(x) = x + 1
- **Square** представя функцията f: double → double, f(x) = x²
- **Sum<T>** представя функцията f: T → T, f(x) = f₁(x) + ... + fₖ(x), където f₁(x), ..., fₖ(x), k ≥ 0 е списък от функции от тип fᵢ: T → T. Дадена функция се добавя към списъка с метода `addFunction`
- **Max<T>** представя функцията f: T → T, f(x) = max{f₁(x), ..., fₖ(x)}, където f₁(x), ..., fₖ(x), k > 0 е списък от функции от тип fᵢ: T → T. Дадена функция се добавя към списъка с метода `addFunction`

**Function** е шаблон на абстрактен клас, който е базов за `Inc`, `Square`, `Sum` и `Max`.

**Функцията main** въвежда от стандартния вход числото x и извежда най-голямата измежду стойностите x + 1, x² и x² + x + 1.

Да се попълнят липсващите части в програмата. Да се приеме, че класовете `Sum` и `Max` не е нужно да правят копие на подадените им функции.

---

## 1) Абстрактен клас Function

### Условие

```cpp
template <typename T>
class Function
{ public:
    T value(T) const
};
```

### Решение

```cpp
template<typename T>
class Function
{ public:
    virtual T value(T) const = 0;
};
```

---

## 2) Клас Inc

### Условие

```cpp
class Inc :
{ public:
    double value(double x) const { return x+1; }
};
```

### Решение

```cpp
class Inc : public Function<double>
{ public:
    double value(double x) const { return x+1; }
};
```

---

## 3) Клас Square

### Условие

```cpp
class Square :
{ public:
    double value(double x) const { return x*x; }
};
```

### Решение

```cpp
class Square : public Function<double>
{ public:
    double value(double x) const { return x*x; }
};
```

---

## 4) Шаблон Max

### Условие

```cpp
class Max :
{ private:
    std::vector< > functions;
public:
    void addFunction( f)
    { functions.push_back(f); }
    T value(T x) const
    {
        if( )
            throw "Function list is empty!";
        return ;
    }
};
```

### Решение

```cpp
template<typename T>
class Max : public Function<T>
{ private:
    std::vector<Function<T>*> functions;
public:
    void addFunction(Function<T> *f) { functions.push_back(f); }
    T value(T x) const
    {
        if(functions.size()<1)
            throw "Function list is empty!";
        T result = functions[0]->value(x);
        for(Function<T> *f : functions)
            result = std::max(result,f->value(x));
        return result;
    }
};
```

---

## 5) Шаблон Sum

### Условие

```cpp
class Sum:
{ private:
    std::vector< > functions;
public:
    void addFunction( f)
    { functions.push_back(f); }
    T value(T x) const
    {
        return ;
    }
};
```

### Решение

```cpp
template<typename T>
class Sum : public Function<T>
{ private:
    std::vector<Function<T>*> functions;
public:
    void addFunction(Function<T> *f) { functions.push_back(f); }
    T value(T x) const
    {
        T result = 0;
        for(Function<T> *f : functions)
            result += f->value(x);
        return result;
    }
};
```

---

## Пълна програма

```cpp
#include <vector>
#include <iostream>

template<typename T>
class Function
{ public:
    virtual T value(T) const = 0;
};

class Inc : public Function<double>
{ public:
    double value(double x) const { return x+1; }
};

class Square : public Function<double>
{ public:
    double value(double x) const { return x*x; }
};

template<typename T>
class Max : public Function<T>
{ private:
    std::vector<Function<T>*> functions;
public:
    void addFunction(Function<T> *f) { functions.push_back(f); }
    T value(T x) const
    {
        if(functions.size()<1)
            throw "Function list is empty!";
        T result = functions[0]->value(x);
        for(Function<T> *f : functions)
            result = std::max(result,f->value(x));
        return result;
    }
};

template<typename T>
class Sum : public Function<T>
{ private:
    std::vector<Function<T>*> functions;
public:
    void addFunction(Function<T> *f) { functions.push_back(f); }
    T value(T x) const
    {
        T result = 0;
        for(Function<T> *f : functions)
            result += f->value(x);
        return result;
    }
};

int main()
{
    Inc i; Square sq;
    Sum<double> s; Max<double> m;

    // s представя (x+1)+(x*x)
    s.addFunction(&i); s.addFunction(&sq);

    // m представя max{x+1, x*x, (x+1)+(x*x)}
    m.addFunction(&i); m.addFunction(&sq);
    m.addFunction(&s);

    double x; std::cin >> x;
    std::cout << m.value(x) << std::endl;
}
```

---

## Обяснение

### 1. Абстрактен клас Function

```cpp
virtual T value(T) const = 0;
```

- **virtual** прави метода виртуален - позволява полиморфизъм
- **= 0** прави метода **pure virtual** - класът става абстрактен и не може да се инстанцира
- Всички наследници трябва да имплементират този метод

### 2-3. Класове Inc и Square

```cpp
class Inc : public Function<double>
class Square : public Function<double>
```

- Наследяват публично `Function<double>`
- Имплементират `value()` метода за конкретни функции

### 4. Шаблон Max

```cpp
std::vector<Function<T>*> functions;
```

- Съхранява указатели към функции от тип `Function<T>*`
- Не прави копие - пази само адресите

```cpp
void addFunction(Function<T> *f)
```

- Приема указател към функция и го добавя към вектора

```cpp
if(functions.size()<1)
```

- Проверява дали има поне една функция (условието k > 0 от описанието)

```cpp
T result = functions[0]->value(x);
for(Function<T> *f : functions)
    result = std::max(result, f->value(x));
```

- Инициализира резултата с първата функция
- Обхожда всички функции и намира максимума
- Използва `std::max` за сравнение

### 5. Шаблон Sum

```cpp
T result = 0;
for(Function<T> *f : functions)
    result += f->value(x);
```

- Инициализира резултата с 0 (неутрален елемент за събиране)
- Обхожда всички функции и сумира стойностите
- Работи дори за празен списък (k ≥ 0) - връща 0

### 6. Main функция

```cpp
s.addFunction(&i); s.addFunction(&sq);
```

- `s` представя (x+1) + x² = x² + x + 1

```cpp
m.addFunction(&i); m.addFunction(&sq); m.addFunction(&s);
```

- `m` представя max{x+1, x², x²+x+1}
- За x ≥ 1: x²+x+1 е най-голямото
- За x ∈ [0, 1): зависи от конкретната стойност

---

## Ключови концепции

1. **Шаблони (Templates)** - позволяват генериране на код за различни типове
2. **Абстрактни класове** - класове с поне един pure virtual метод
3. **Полиморфизъм** - извикване на правилната функция според типа на обекта
4. **Виртуални функции** - позволяват override в наследниците
5. **Указатели към базови класове** - могат да сочат към обекти от наследници
6. **Range-based for loop** - `for(Function<T> *f : functions)` обхожда вектора
7. **Композиция на функции** - комбиниране на прости функции в по-сложни
