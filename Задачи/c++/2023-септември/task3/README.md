# Задача 3 - Дърво на директории

## Описание

Разглеждаме дърво на директориите на файлова система. Всяка директория може да има произволен брой наследници. Не се допускат две директории с едно и също име и общ пряк родител (в една директория не може да има две директории с едно и също име).

**Характеристики:**

- Всички възли имат име – символен низ с дължина не по-голяма от 12 символа
- Името е съставено от малки или главни латински букви, цифри, както и символа точка
- Корен на дървото винаги е главната директория с празно име
- Главната директория е единственият елемент с празно име

---

## 1. Структура на дървото

### Условие

Да се опише структура, с която можете да се представи такова дърво и да се напише нейната дефиниция на C++.

### Решение

```cpp
struct Node {
  string name;
  vector<Node*> children;

  Node(const string& dirName) : name(dirName) {}
};

struct Tree {
  Node* root;

  Tree() { root = new Node(""); }
};
```

---

## 2. Функция insert - добавяне на директория

### Условие

Да се дефинира функция `insert`, която получава като аргументи дърво на файлова система и символен низ, описващ пълен път към директория, като за разделител се използва символът `'/'`.

Функцията трябва да добави тази директория в дървото, като при нужда създава всички липсващи родителски директории от пълния път до нея.

**Пример:** Ако е зададен пълен път `"/home/user/src"`, след приключване на работата на функцията в дървото със сигурност трябва да има:

- Елемент с име "home", който е наследник на корена
- Елемент с име "user", който е наследник на елемента "home"
- Елемент с име "src", който е наследник на елемента "user"

### Решение

```cpp
Node* findChild(const Node* child, const string& childName) {
  for (Node* child : child->children) {
    if (child->name == childName) {
      return child;
    }
  }

  return nullptr;
}

void insert(Tree& tree, const string& fullPath) {
  Node* current = tree.root;

  size_t i = 0;
  size_t pathLength = fullPath.length();

  while (i < pathLength) {
    if (fullPath[i] == '/') {
      i++;
      continue;
    }

    size_t start = i;

    while (i < pathLength && fullPath[i] != '/') {
      i++;
    }

    string dirName = fullPath.substr(start, i - start);

    Node* child = findChild(current, dirName);

    if (child == nullptr) {
      child = new Node(dirName);
      current->children.push_back(child);
    }

    current = child;
  }
}
```

---

## 3. Функция flatten - преобразуване на поддърво

### Условие

Да се дефинира функция `flatten`, която получава като аргумент дърво на файловата система и пълен път към елемент в него.

Функцията трябва да преобразува всички непреки наследници на този елемент в негови преки наследници, т.е. всички елементи на поддървото на елемента трябва да станат преки наследници на корена му.

Ако има повтарящи се имена, функцията трябва да остави само един пряк наследник с това име.

### Решение

```cpp
Node* findNode(Tree& tree, const string& fullPath) {
  Node* current = tree.root;

  size_t i = 0;
  size_t pathLength = fullPath.length();

  while (i < pathLength) {
    if (fullPath[i] == '/') {
      i++;
      continue;
    }

    size_t start = i;
    while (i < pathLength && fullPath[i] != '/') {
      i++;
    }

    string dirName = fullPath.substr(start, i - start);

    Node* child = findChild(current, dirName);
    if (child == nullptr) {
      return nullptr;
    }

    current = child;
  }

  return current;
}

void flatten(Tree& tree, const string& fullPath) {
  Node* target = findNode(tree, fullPath);

  if (target == nullptr) {
    return;
  }

  vector<Node*> allDescendants;

  vector<Node*> queue;
  for (Node* child : target->children) {
    queue.push_back(child);
  }

  size_t idx = 0;
  while (idx < queue.size()) {
    Node* node = queue[idx];
    idx++;
    allDescendants.push_back(node);
    for (Node* grandchild : node->children) {
      queue.push_back(grandchild);
    }
  }

  vector<Node*> newChildren;
  unordered_set<string> seenNames;

  for (Node* node : allDescendants) {
    if (seenNames.find(node->name) == seenNames.end()) {
      seenNames.insert(node->name);
      node->children.clear();
      newChildren.push_back(node);
    }
  }

  target->children = newChildren;
}
```
