# Задача 3

Задачата да се реши на езика C++.

Свързан списък ще представяме с верига от обекти от следната структура, динамично заделени с `new`. За последния елемент на списъка указателят `next` има стойност `nullptr`. Приемаме, че за типа `Type` са дефинирани нужните конструктори и оператори.

```cpp
template <typename Type>
struct node
{
  const Type data;
  node<Type>* next;
};
```

Да се реализират следните функции, получаващи като аргумент указател към първия елемент на списък и връщащи указател към началото на резултатния списък.

**Не се позволява използване на алгоритми и структури от данни от стандартната библиотека.**

---

## а) Обръщане на списък

Функция, която обръща свързан списък. Тя трябва да използва константно количество допълнителна памет и да е с линейна сложност.

```cpp
template <typename Type>
node<Type>* reverse(node<Type>* first);
```

### Решение:

```cpp
template <typename Type>
node<Type>* reverse(node<Type>* first) {
  if (first == nullptr) {
    cout << "Empty List" << endl;
    return first;
  }

  if (first && first->next == nullptr) {
    cout << "Single Element list" << endl;
    return first;
  }

  node<Type>* toRev = nullptr;
  node<Type>* prev = nullptr;

  while (first) {
    toRev = first;
    first = first->next;
    toRev->next = prev;
    prev = toRev;
  }

  return prev;
}
```

---

## б) Филтриране на елементи

Функция, която премахва от списъка всички елементи, равни на първия при сравнение с `==`, но без него. Тя трябва да използва константно количество допълнителна памет и да е с линейна сложност.

```cpp
template <typename Type>
node<Type>* filter(node<Type>* first);
```

### Решение:

```cpp
template <typename Type>
node<Type>* filter(node<Type>* first) {
  node<Type>* iter = first;
  node<Type>* toDel = nullptr;

  while (iter && iter->next) {
    if (iter->next->data == first->data) {
      toDel = iter->next;
      iter->next = toDel->next;
      delete toDel;
    } else {
      iter = iter->next;
    }
  }

  return first;
}
```

---

## в) Сортиране на списък

Функция, която подрежда елементите на списъка във възходящ ред. Тя трябва да има асимптотична времева сложност в средния случай по-добра от O(n²).

Опишете накратко с текст какъв алгоритъм сте реализирали, каква е неговата времева сложност и каква е сложността му по памет.

```cpp
template <typename Type>
node<Type>* sort(node<Type>* first);
```

### Решение:

```cpp
// Намиране на средата на списъка (за разделяне)
template <typename Type>
node<Type>* findMiddle(node<Type>* first) {
  node<Type>* slow = first;
  node<Type>* fast = first->next;

  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }

  return slow;
}

// Сливане на два сортирани списъка
template <typename Type>
node<Type>* merge(node<Type>* l1, node<Type>* l2) {
  node<Type> dummy{Type{}, nullptr};
  node<Type>* tail = &dummy;

  while (l1 != nullptr && l2 != nullptr) {
    if (l1->data <= l2->data) {
      tail->next = l1;
      l1 = l1->next;
    } else {
      tail->next = l2;
      l2 = l2->next;
    }
    tail = tail->next;
  }

  tail->next = (l1 != nullptr) ? l1 : l2;
  return dummy.next;
}

// Merge Sort за свързан списък
template <typename Type>
node<Type>* sort(node<Type>* first) {
  if (first == nullptr || first->next == nullptr) {
    return first;  // 0 or 1 elements already sorted
  }

  // split the list into two parts
  node<Type>* middle = findMiddle(first);
  node<Type>* secondHalf = middle->next;
  middle->next = nullptr;

  node<Type>* left = sort(first);
  node<Type>* right = sort(secondHalf);

  return merge(left, right);
}
```

### Описание на алгоритъма за сортиране

**Алгоритъм:** Merge Sort (сортиране чрез сливане)

**Времева сложност:**

- Най-лош случай: O(n log n)
- Среден случай: O(n log n)
- Най-добър случай: O(n log n)

**Сложност по памет:** O(log n) - заради рекурсивните извиквания (дълбочина на стека)

**Описание на имплементацията:**

1. **findMiddle()** - използва "бавен и бърз указател" за намиране на средата на списъка
2. **merge()** - слива два сортирани списъка в един сортиран
3. **sort()** - рекурсивно разделя списъка на две половини, сортира ги и ги слива

Merge Sort отговаря на изискването за асимптотична сложност по-добра от O(n²).
