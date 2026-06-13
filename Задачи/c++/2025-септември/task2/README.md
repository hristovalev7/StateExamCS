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

## б) Открийте, обяснете и поправете грешките в следния код, който трябва да прочете елементите на пълно двоично дърво от текстов файл. Елементите са записани последователно по нива.

### Оригинален код (с грешки)

```cpp
struct tree_node
{
    int data;
    tree_node* children[2];
    tree_node(int d = 0) : data(d) {}
};

tree_node* read_tree(const std::istream& input)
{
    if (!input) return NULL;
    std::queue<tree_node*> front;
    tree_node* root = new tree_node;
    input >> root->data;
    front.push(root);
    while (input)
    {
        tree_node* current = front.pop();
        for (int i = 0; i < 2; ++i) {
            int x;
            input >> x;
            current->children[i] = new tree_node(x);
            front.push(current->children[i]);
        }
    }
    return root;
}
```

---

### Грешки и обяснения

**Ред 4.** Няма инициализация на масива с децата. Възможна корекция е:

```cpp
tree_node* children[2]{};
```

**Ред 8.** Некоректно използване на `const` за параметъра. Обектът трябва да се променя във функцията (операторът `>>` мести вътрешния указател на потока и променя състоянието му — затова е non-const метод). Корекция:

```cpp
tree_node* read_tree(std::istream& input)
```

**Ред 12.** Създаването на елемент преди прочитането на данни за него е проблем при липса на данни. Ако например няма елементи във файла и трябва да се създаде празно дърво, написаният код няма да работи коректно. Възможна корекция е редове 12 и 13 да се заменят с редовете:

```cpp
int data;
input >> data;
if (!input) return nullptr;
tree_node* root = new tree_node(data);
```

**Ред 17.** Некоректно използване на стандартният контейнер `std::queue`. Методът `pop` не връща премахнатия елемент. Примерна корекция е ред 17 да се замени с:

```cpp
tree_node* current = front.front(); front.pop();
```

**Ред 20.** След четене на елемент трябва да се провери дали има данни (т.е. дали четенето е успешно). Възможна корекция е добавянето на проверка след четенето и обработка на повреден поток. Например, да се вмъкне следния код между редове 20 и 21:

```cpp
if (!input) break;
```

**В цикъла трябва да се прихваще проблем със заделянето на паметта и да се освободи вече заделената памет.** Примерна корекция е ограждане на целия `while` цикъл в `try-catch` блок, който прихваща или всичко или `std::bad_alloc` и в `catch` секцията се извика функция за изтриване на паметта за дървото. Реализация на такава функция не се изисква, но тя би могла да изглежда така:

```cpp
void clear(tree_node* root)
{
    if (root){
        clear(root->children[0]);
        clear(root->children[1]);
        delete root;
    }
}
```

Може да се добави и каскаден деструктор на елемента на дървото и в `catch` секцията да се извика само `delete root;`.

---

### Поправен код (обединени корекции)

```cpp
struct tree_node
{
    int data;
    tree_node* children[2]{};
    tree_node(int d = 0) : data(d) {}
};

tree_node* read_tree(std::istream& input)
{
    int data;
    input >> data;
    if (!input) return nullptr;

    tree_node* root = new tree_node(data);
    std::queue<tree_node*> front;
    front.push(root);

    try {
        while (input)
        {
            tree_node* current = front.front();
            front.pop();

            for (int i = 0; i < 2; ++i) {
                int x;
                input >> x;
                if (!input) break;

                current->children[i] = new tree_node(x);
                front.push(current->children[i]);
            }
        }
    } catch (...) {
        clear(root);
        throw;
    }

    return root;
}
```
