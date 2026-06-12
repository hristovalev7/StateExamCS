# Задача 2

Задачата да се реши на езика C++.

## а) Елементите на едносвързан списък представяме чрез следната структура:

```cpp
struct node {
  int value;
  node* next;
};
```

Елементите на списък заделяме с `new`, празния списък представяме като `nullptr`.

Да се реализират следните функции:

### 1. `void removeIf(node*& from, const node* what);`

Премахва от списъка с начало `from` всички елементи, които се срещат в списъка с начало `what`. След изпълнението `from` трябва да сочи началото на резултатния списък.

```cpp
bool contains(const node* what, int fromVal) {
  while (what) {
    if (what->value == fromVal) {
      return true;
    }
    what = what->next;
  }

  return false;
}

void removeIf(node*& from, const node* what) {
  // remove matches from begining
  while (from && contains(what, from->value)) {
    node* toDel = from;
    from = from->next;
    delete toDel;
  }

  // remove the rest
  node* iter = from;

  while (iter && iter->next) {
    if (contains(what, iter->next->value)) {
      node* toDel = iter->next;
      iter->next = toDel->next;
      delete toDel;
    } else {
      iter = iter->next;
    }
  }
}
```

---

### 2. `node* merge(node* first, node* second);`

Слива сортираните във възходящ ред списъци с начало `first` и `second` в резултатен, сортиран по същия начин списък. Подадените списъци могат да имат повторения, но в резултата не трябва да има повтарящи се стойности. Елементите да се преизползват (не трябва да се създават нови елементи). Функцията да връща указател към началото на резултатния списък.

```cpp
node* merge(node* first, node* second) {
  node* head = nullptr;
  node* tail = nullptr;

  while (first && second) {
    node* chosen = nullptr;

    if (first->value <= second->value) {
      chosen = first;
      first = first->next;
    } else {
      chosen = second;
      second = second->next;
    }

    if (head == nullptr) {
      head = chosen;
    } else {
      tail->next = chosen;
    }

    tail = chosen;
  }

  node* rest = first ? first : second;

  if (head == nullptr) {
    head = rest;
  } else {
    tail->next = rest;
  }

  return head;
}

node* removeDuplicates(node* head) {
  node* iter = head;

  while (iter && iter->next) {
    if (iter->value == iter->next->value) {
      node* toDel = iter->next;
      iter->next = toDel->next;
      delete toDel;
    } else {
      iter = iter->next;
    }
  }

  return head;
}
```
