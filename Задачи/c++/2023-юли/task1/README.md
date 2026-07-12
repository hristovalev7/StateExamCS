# Задача 1 - Анализ на C++ код

Задачата да се реши на езика C++.

---

## 1) Функция removeWhitespace

### Условие

Да се попълнят празните места в кода на функцията `removeWhitespace` така, че тя да премахва от непразния низ `str` всички whitespace символи.

```cpp
bool isWhitespace(char c)
{
    return c == ' ' || c == '\t' ||
           c == '\r' || c == '\n';
}

________ removeWhitespace(char* str)
{
    size_t read=0, write=0;
    while(str[read]){
        if (isWhitespace(_________________))
            read_____________________________;
        else
            str[write++] = __________________;
    }
    str[____________________] = '\0';
    return str;
}
```

### Решение

```cpp
bool isWhitespace(char c)
{
    return c == ' ' || c == '\r' ||
           c == '\t' || c == '\n';
}

char* removeWhitespace(char* str)
{
    size_t read=0, write=0;
    while(str[read]){
        if (isWhitespace(str[read]))
            read++;
        else
            str[write++] = str[read++];
    }
    str[write] = '\0';
    return str;
}
```

---

## 2) Анализ на фрагменти

### Условие

Под всеки от фрагментите да се посочи какво ще изведе той на стандартния изход.

**Фрагмент 1:**

```cpp
for (int i = 0; i < 10; ++i) {
    if (i % 2) continue;
    cout << i;
}
```

**Фрагмент 2:**

```cpp
int i = 0x10;
cout << i;
```

**Фрагмент 3:**

```cpp
int a=1,b=2,c=3;
cout << (a ? b : c);
```

**Фрагмент 4:**

```cpp
char str[] = "abc";
char* p = str;
++p;
++*p;
cout << str;
```

### Решение

**Фрагмент 1:** `02468`

**Фрагмент 2:** `16`

**Фрагмент 3:** `2`

**Фрагмент 4:** `acc`

---

## 3) Функция pass за сортиране

### Условие

Да се попълнят празните места в кода на функцията `pass` така, че функцията `bubbleSort` да сортира в нарастващ ред елементите на масива `arr` с размер `size`. Абстрахирайте се от това, че алгоритъмът, разписан по този начин, работи неефикасно.

```cpp
void pass(int* arr,
          size_t size,
          bool& swappedAtLeastOnce)
{
    if (size _____ 1)
        return;
    if (arr[0] ________________) {
        std::swap(arr[0], arr[1]);
        swappedAtLeastOnce = _________;
    }
    pass(__________________________,
         __________________________,
         __________________________);
}

void bubbleSort(int* arr, size_t size)
{
    bool swappedAtLeastOnce = false;
    pass(arr, size, swappedAtLeastOnce);
    if (swappedAtLeastOnce)
        bubbleSort(arr, size);
}
```

### Решение

```cpp
void pass(int* arr,
          size_t size,
          bool& swappedAtLeastOnce)
{
    if (size <= 1)
        return;
    if (arr[0] > arr[1]) {
        std::swap(arr[0], arr[1]);
        swappedAtLeastOnce = true;
    }
    pass(arr + 1, size - 1, swappedAtLeastOnce);
}

void bubbleSort(int* arr, size_t size)
{
    bool swappedAtLeastOnce = false;
    pass(arr, size, swappedAtLeastOnce);
    if (swappedAtLeastOnce)
        bubbleSort(arr, size);
}
```

---

## 4) Анализ на изрази

### Условие

Да се посочи какво ще изведе на стандартния изход следният фрагмент.

```cpp
int x = 2;
int arr[] = {10, 20, 30};
cout << "\nA: " << 5./x;
cout << "\nB: " << (x << 4);
cout << "\nC: " << arr[!x];
cout << "\nD: " << *(arr+x);
cout << "\nE: " << (2 + x++);
```

```
A: _______________________
B: _______________________
C: _______________________
D: _______________________
E: _______________________
```

### Решение

```
A: 2.5
B: 32
C: 10
D: 30
E: 4
```

### Обяснение

**A: `5./x` → `2.5`**

- `5.` е литерал от тип `double` (реално число)
- `5./x` → `5.0 / 2` → `2.5`
- Делението на `double` с `int` връща `double`

**B: `(x << 4)` → `32`**

- `<<` е **битов изместване наляво** (left shift)
- `x << 4` → `2 << 4` → битовете на 2 се изместват 4 позиции наляво
- В двоична бройна система: `10` (2) → `100000` (32)
- Математически еквивалентно на: 2 × 2⁴ = 2 × 16 = 32

**C: `arr[!x]` → `10`**

- `!x` е **логическо отрицание** на `x`
- `x = 2`, което е ненулево → true
- `!2` → `!true` → `false` → `0`
- `arr[0]` → `10` (първият елемент на масива)

**D: `*(arr+x)` → `30`**

- **Pointer arithmetic:** `arr+x` сочи към елемент на позиция `x`
- `arr+2` → сочи към третия елемент (индекс 2)
- `*(arr+2)` → дереференция → `arr[2]` → `30`
- `*(arr+i)` е еквивалентно на `arr[i]`

**E: `(2 + x++)` → `4`**

- `x++` е **постфиксен инкремент** - връща старата стойност, после увеличава
- `2 + x++` → `2 + 2` → `4` (x се използва със стойност 2)
- След изпълнение на израза: `x` става `3`
- Разлика с `++x` (префиксен): той първо увеличава, после връща новата стойност
