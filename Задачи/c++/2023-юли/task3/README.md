# Задача 3 - Троично дърво

## Описание

**Троично дърво** ще наричаме наредено дърво, за което всеки възел съхранява една или две стойности и има не повече от три наследника. 

Ако за произволен възел означим стойностите на двата елемента в него с **X** и **Y**, а трите негови потенциални поддървета с **STleft**, **STmid** и **STright**, то за да е валидно такова дърво, трябва да са в сила следните свойства:

- Стойността **X** трябва да е строго по-малка от стойността **Y**
- Стойността на всеки елемент от поддървото **STleft** трябва да е строго по-малка от **X**
- Стойността на всеки елемент от поддървото **STmid** трябва да е по-голяма или равна на **X** и строго по-малка от **Y**
- Стойността на всеки елемент от поддървото **STright** трябва да е по-голяма или равна на **Y**
- Ако в даден възел няма втора стойност (**Y**), то тогава поддървото **STright** задължително трябва да е празно
- Ако в поддървото **STmid** на даден възел има поне един елемент по-голям от **X**, то във възела задължително трябва да има две стойности (**X** и **Y**)
- Всяко от **STleft**, **STmid** и **STright** или е празно, или е валидно троично дърво

**Неравенство:**
```
STleft < X ≤ STmid < Y ≤ STright
```

**Пример за такова дърво:**
```
          5 10
        /   |   \
      2 3   5   7 12
     /  |       |
   0 1  3 4    
        |
        1
```

---

## 1) Структура на троично дърво

### Условие

Да се опише структура, с която може да се представи такова троично дърво с елементи цели числа и да се напише нейната дефиниция на C++.

### Решение

```cpp
struct Node {
  int x;
  int y;

  Node *left = nullptr, *mid = nullptr, *right = nullptr;
};

struct Tree {
  Node* root = nullptr;
};
```

---

## 2) Функция insert - добавяне на елемент

### Условие

Да се дефинира функция `insert` с аргументи троично дърво от цели числа и цяло число, която добавя това число в дървото, съблюдавайки изискванията за валидност. При добавяне на нова стойност не трябва да се променят или преместват съществуващите в дървото стойности.

### Решение

```cpp
void insert(Node*& root, int value) {
  if (root == nullptr) {
    root = new Node();
    root->x = root->y = value;
    return;
  }

  if (value < root->x)
    insert(root->left, value);
  else if (value == root->x)
    insert(root->mid, value);
  else if (root->x == root->y)
    root->y = value;
  else if (value < root->y)
    insert(root->mid, value);
  else
    insert(root->right, value);
}

void insert(Tree& tree, int value) {
  insert(tree.root, value);
}
```

---

## 3) Функция find - търсене на елемент

### Условие

Да се дефинира функция `find` с аргументи троично дърво от цели числа и цяло число, която проверява дали подаденото число се съдържа в дървото.

### Решение

```cpp
bool find(Node* root, int value) {
  if (root == nullptr) {
    return false;
  }

  if (value == root->x || value == root->y)
    return true;
  else if (value < root->x)
    return find(root->left, value);
  else if (value < root->y)
    return find(root->mid, value);
  return find(root->right, value);
}

bool find(const Tree& tree, int value) {
  return find(tree.root, value);
}
```

---

## 4) Демонстрационна програма

### Условие

Да се реализира кратка програма, която демонстрира описаните функции, като за целта:

**а)** Създава празно дърво

**б)** Въвежда от стандартния вход естествено число **N**, последвано от **N** цели числа, които добавя в дървото

**в)** Прочита от стандартния вход едно число и извежда на стандартния изход подходящ текст, указващ дали това число се среща или не в дървото

**г)** Подсигурява коректна работа с паметта

### Решение

```cpp
void clear(Node* root) {
  if (root == nullptr) {
    return;
  }

  clear(root->left);
  clear(root->mid);
  clear(root->right);
  delete root;
}

void clear(Tree& t) {
  clear(t.root);
  t.root = nullptr;
}

int main() {
  Tree t;
  int N;
  do {
    std::cout << "N = ";
    std::cin >> N;
  } while (N <= 0);

  for (int i = 0; i < N; ++i) {
    int value;
    std::cin >> value;
    insert(t, value);
  }

  int X;
  std::cin >> X;
  std::cout << "The tree " << (find(t, X) ? "contains " : "does not contain ")
            << X << "\n";

  clear(t);
  return 0;
}
```
